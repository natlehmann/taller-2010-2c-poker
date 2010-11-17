#include "ContextoJuego.h"
#include "PokerException.h"
#include "Repartidor.h"
#include "Jugada.h"
#include "RecursosServidor.h"
#include "UtilTiposDatos.h"
#include "IteradorRonda.h"
#include "IteradorRondaActivos.h"
#include "AccesoDatos.h"

ContextoJuego* ContextoJuego::instancia = NULL;

int ContextoJuego::segsTimeoutJugadores = UtilTiposDatos::getEntero(
		RecursosServidor::getConfig()->get("servidor.logica.timeout.jugadorInactivo"));

ContextoJuego::ContextoJuego(void)
{
	this->mutex = CreateMutexA(NULL, false, "MutexContexto");

	this->admJugadores = new AdministradorJugadores();

	this->mesa = new MesaModelo(10, 
		UtilTiposDatos::getEntero(
			RecursosServidor::getConfig()->get("servidor.mesa.smallBlind")), 
		RecursosServidor::getConfig()->get("servidor.mesa.fondo"));
	this->mesa->setApuestaMaxima(UtilTiposDatos::getEntero(
			RecursosServidor::getConfig()->get("servidor.mesa.apuestaMaxima")));
		
	this->bote = new BoteModelo(11);
	this->mensaje = new MensajeModelo(12);
	this->cartasComunitarias = new CartasComunitariasModelo(13);

	this->montoAIgualar = 0;
	this->cantidadJugadoresRonda = 0;
	this->repartidor = new Repartidor();
	this->rondaTerminada = false;
	this->mostrandoCartas = false;
	this->sePuedePasar = false;
	this->rondaAllIn = false;

	this->esperandoJugadores = new EstadoEsperandoJugadores();
	this->evaluandoGanador = new EstadoEvaluandoGanador();
	this->rondaRiver = new EstadoRondaRiver(this->evaluandoGanador);
	this->rondaTurn = new EstadoRondaTurn(this->rondaRiver);
	this->rondaFlop = new EstadoRondaFlop(this->rondaTurn);
	this->rondaCiega = new EstadoRondaCiega(this->rondaFlop);	

	this->esperandoJugadores->setEstadoRondaCiega(this->rondaCiega);
	this->evaluandoGanador->setEstadoRondaCiega(this->rondaCiega);
	this->evaluandoGanador->setEstadoEsperandoJugadores(this->esperandoJugadores);

	this->estado = this->esperandoJugadores;
	this->timerEsperandoJugadores.iniciar();
}

ContextoJuego::~ContextoJuego(void)
{
	//if (instancia) {
	//	delete instancia;
	//	instancia = NULL;
	//}
}

void ContextoJuego::finalizar() {

	if(this->admJugadores != NULL) {
		delete (this->admJugadores);
		this->admJugadores = NULL;
	}

	if (this->mesa) {
		delete this->mesa;
		this->mesa = NULL;
	}
	if (this->bote) {
		delete this->bote;
		this->bote = NULL;
	}
	if (this->mensaje) {
		delete this->mensaje;
		this->mensaje = NULL;
	}
	if (this->cartasComunitarias) {
		delete this->cartasComunitarias;
		this->cartasComunitarias = NULL;
	}
	if (this->repartidor) {
		delete this->repartidor;
		this->repartidor = NULL;
	}

	delete(this->esperandoJugadores);
	delete(this->rondaCiega);
	delete(this->rondaFlop);
	delete(this->rondaTurn);
	delete(this->rondaRiver);
	delete(this->evaluandoGanador);

	CloseHandle(this->mutex);
}

HANDLE ContextoJuego::getMutex(){
	return this->mutex;
}

ContextoJuego* ContextoJuego::getInstancia(){
	if (instancia == NULL) {
		instancia = new ContextoJuego();
	}
	return instancia;
}

int ContextoJuego::getTiempoEsperandoJugadores(){
	return this->timerEsperandoJugadores.getSegundos();
}

void ContextoJuego::resetTimerEsperandoJugadores(){
	this->timerEsperandoJugadores.iniciar();
}

bool ContextoJuego::isTiempoMostrandoGanadorCumplido() {
	return (this->timerMostrandoGanador.getSegundos() >= UtilTiposDatos::getEntero( 
		RecursosServidor::getConfig()->get("servidor.logica.timeout.mostrandoGanador")));
}

MesaModelo* ContextoJuego::getMesa(){
	return this->mesa;
}

BoteModelo* ContextoJuego::getBote() {
	return this->bote;
}

MensajeModelo* ContextoJuego::getMensaje(){
	return this->mensaje;
}

CartasComunitariasModelo* ContextoJuego::getCartasComunitarias(){
	return this->cartasComunitarias;
}

int ContextoJuego::getCantidadJugadoresJugandoRonda(){
	return this->cantidadJugadoresRonda;
}


void ContextoJuego::igualarApuesta(int idCliente)
{
	JugadorModelo* jugador = this->admJugadores->getJugador(idCliente);
	int montoApuesta = this->montoAIgualar - jugador->getApuesta();
	if (jugador->getFichas() < montoApuesta) {
		montoApuesta = jugador->getFichas();
	}
	jugador->apostar(montoApuesta);
	this->bote->incrementar(montoApuesta);
	this->admJugadores->incrementarTurno();
	chequearRondaTerminada();
}

void ContextoJuego::pasar(int idCliente){

	if (this->sePuedePasar) {
		this->admJugadores->incrementarTurno();
		chequearRondaTerminada();
	} else {
		throw PokerException("Se solicito 'pasar' cuando esta no era una jugada permitida.");
	}
}

void ContextoJuego::subirApuesta(int idCliente, int fichas)
{
	JugadorModelo* jugador = this->admJugadores->getJugador(idCliente);
	jugador->apostar(fichas);
	this->bote->incrementar(fichas);
	this->montoAIgualar = jugador->getApuesta();
	this->admJugadores->setJugadorQueCierra(jugador->getId());
	this->admJugadores->incrementarTurno();
	this->sePuedePasar = false;
	chequearRondaTerminada();
}

bool ContextoJuego::puedeSubirApuesta(int idCliente, int fichas){
	JugadorModelo* jugador = this->admJugadores->getJugador(idCliente);
	return (fichas <= jugador->getFichas() && fichas <= this->mesa->getApuestaMaxima());
}

bool ContextoJuego::puedeSubirApuesta(int idJugador){
	int idCliente = this->idJugadorToIdCliente(idJugador);
	JugadorModelo* jugador = this->admJugadores->getJugador(idCliente);
	if (jugador) {
		return (jugador->getFichas() + jugador->getApuesta() > this->montoAIgualar);
	} else {
		return true;
	}
}

bool ContextoJuego::esApuestaValida(int idCliente, int fichas){
	JugadorModelo* jugador = this->admJugadores->getJugador(idCliente);
	return ((jugador->getApuesta() + fichas) >= this->montoAIgualar);
}

void ContextoJuego::noIr(int idCliente)
{
	JugadorModelo* jugador = this->admJugadores->getJugador(idCliente);
	jugador->setApuesta(0);
	jugador->setCarta1(NULL);
	jugador->setCarta2(NULL);
	this->cantidadJugadoresRonda--;

	if (this->cantidadJugadoresRonda > 1) {

		if (this->admJugadores->isDealerJugador(jugador->getId())) {
			this->admJugadores->incrementarDealerTemp();
		}

		if (this->admJugadores->isJugadorQueCierra(jugador->getId())){
			this->admJugadores->decrementarJugadorQueCierra();
		}

		this->admJugadores->incrementarTurno();
		jugador->setJugandoRonda(false);
		chequearRondaTerminada();
		if (!this->rondaTerminada) {
			chequearRondaAllIn();
		}

	} else {
		
		jugador->setJugandoRonda(false);
		this->finalizarRonda();
		this->estado = this->evaluandoGanador;
	}

}

void ContextoJuego::chequearRondaTerminada() {
	if (this->cantidadJugadoresRonda > 1) {
		this->rondaTerminada = this->admJugadores->isRondaTerminada();
	} else {
		this->rondaTerminada = false; // TODO: NO ES TRUE???
	}
}

void ContextoJuego::chequearRondaAllIn() {

	bool rondaAllIn = true;
	int jugadoresNoAllIn = 0;
	for (int i = 0; i < MAX_CANTIDAD_JUGADORES; i++) {
		JugadorModelo* jugador = this->admJugadores->getJugadores()[i];
		if (jugador->isJugandoRonda() && !jugador->isAllIn()) {
			jugadoresNoAllIn++;
			if (jugadoresNoAllIn > 1 || jugador->getApuesta() < this->montoAIgualar) {
				rondaAllIn = false;
				break;
			}
		}
	}
	this->rondaAllIn = rondaAllIn;
	if (this->rondaAllIn) {
		this->rondaTerminada = true;
	}
}

bool ContextoJuego::isRondaTerminada(){
	return this->rondaTerminada || this->rondaAllIn;
}

bool ContextoJuego::isRondaAllIn(){
	return this->rondaAllIn;
}

void ContextoJuego::iniciarJuego() {

	int cantidadJugadoresActivos = getCantidadJugadoresActivos();
	if (cantidadJugadoresActivos < 2) {
		throw PokerException("No hay suficientes jugadores para iniciar la ronda.");
	}

	this->cartasComunitarias->limpiar();
	repartidor->mezclar();
	this->bote->vaciar();
	this->mostrandoCartas = false;
	this->sePuedePasar = false;

	for (int i = 0; i < MAX_CANTIDAD_JUGADORES; i++) {
		if (this->admJugadores->getJugadores()[i]->isActivo()) {
			this->admJugadores->getJugadores()[i]->setJugandoRonda(true);
		}
		this->admJugadores->getJugadores()[i]->setApuesta(0);
		this->admJugadores->getJugadores()[i]->setDealer(false);
		this->admJugadores->getJugadores()[i]->setAllIn(false);
	}

	this->admJugadores->resetearDealer();
	this->admJugadores->incrementarDealer();
	this->admJugadores->resetearJugadorTurno();


	int blind = 1;
	IteradorRondaActivos* it = this->admJugadores->getIteradorRondaActivos();
	while (!it->esUltimo()) {

		JugadorModelo* jugador = it->getSiguiente();
		jugador->setCarta1(repartidor->getCarta());
		jugador->setCarta2(repartidor->getCarta());

		if (blind <= 2) {

			if (cantidadJugadoresActivos == 2) {
				if (blind == 1) {
					jugador->apostar(mesa->getSmallBlind() * 2);
				} else {
					jugador->apostar(mesa->getSmallBlind());
				}
			} else {
				jugador->apostar(mesa->getSmallBlind() * blind);
			}

			this->bote->incrementar(mesa->getSmallBlind() * blind);
			this->admJugadores->incrementarTurno();
			blind++;
		}
	}
	if (cantidadJugadoresActivos == 2) {
		this->admJugadores->incrementarTurno();
	}
	this->admJugadores->setJugadorQueCierraActual();

	
	if (blind >= 2) {
		blind--;
		this->montoAIgualar = mesa->getSmallBlind() * blind;
	}
	
	this->cantidadJugadoresRonda = cantidadJugadoresActivos;
	this->rondaTerminada = false;
	this->rondaAllIn = false;
	this->nombresGanadores.clear();

	delete(it);
}

void ContextoJuego::iniciarRonda() {

	if (!this->rondaAllIn) {
		this->admJugadores->resetearJugadorTurno();
		this->sePuedePasar = true;
		chequearRondaAllIn();
	}
}

void ContextoJuego::mostrarFlop()
{
	for (int i=0 ; i<3 ; ++i) {
		this->cartasComunitarias->agregarCarta(repartidor->getCarta());
	}
	this->rondaTerminada = false;
}

void ContextoJuego::mostrarTurn()
{
	this->cartasComunitarias->agregarCarta(repartidor->getCarta());
	this->rondaTerminada = false;
}

void ContextoJuego::mostrarRiver()
{
	this->cartasComunitarias->agregarCarta(repartidor->getCarta());
	this->rondaTerminada = false;
}


void ContextoJuego::evaluarGanador()
{
	list<JugadorModelo*> ganadores;

	if (this->cantidadJugadoresRonda < 2) {
		for (int i = 0; i < MAX_CANTIDAD_JUGADORES; i++) {
			JugadorModelo* jugador = this->admJugadores->getJugadores()[i];
			if (jugador->isJugandoRonda()) {
				ganadores.push_back(jugador);
				break;
			}
		}

	} else {

		double valorJugadaMasAlta = 0;
		
		for (int i = 0; i < MAX_CANTIDAD_JUGADORES; i++) {

			JugadorModelo* jugador = this->admJugadores->getJugadores()[i];
			if (jugador->isJugandoRonda()) {
				Jugada* jugada = new Jugada();
				jugada->agregarCartas(this->cartasComunitarias->getCartas());
				jugada->agregarCarta(jugador->getCarta1());
				jugada->agregarCarta(jugador->getCarta2());
				double valorJugada = jugada->getValorJugada();
				if (valorJugada > valorJugadaMasAlta) {
					valorJugadaMasAlta = valorJugada;
					ganadores.clear();
					ganadores.push_back(jugador);
				} else {
					if (valorJugada == valorJugadaMasAlta) {
						ganadores.push_back(jugador);
					}
				}
			}
		}
	}
	if (ganadores.size() == 0) {
		throw PokerException("Ocurrio un error evaluando al ganador.");
	}

	int fichasQueNoSeReparten = 0;
	int apuestaMaxGanador = 0;

	for (list<JugadorModelo*>::iterator it = ganadores.begin(); it != ganadores.end(); ++it) {
		JugadorModelo* ganador = *it;
		fichasQueNoSeReparten += ganador->getApuesta();
		if (ganador->getApuesta() > apuestaMaxGanador) {
			apuestaMaxGanador = ganador->getApuesta();
		}
	}

	for (int i = 0; i < MAX_CANTIDAD_JUGADORES; i++) {
		JugadorModelo* jugador = this->admJugadores->getJugadores()[i];
		if (jugador->isJugandoRonda() && jugador->getApuesta() > apuestaMaxGanador) {
			int diferencia = jugador->getApuesta() - apuestaMaxGanador;
			jugador->incrementarFichas(diferencia);
			bote->incrementar(-diferencia);
		}
	}

	for (list<JugadorModelo*>::iterator it = ganadores.begin(); it != ganadores.end(); ++it) {
		JugadorModelo* ganador = *it;
		ganador->incrementarFichas(bote->getCantidad() * ganador->getApuesta() / fichasQueNoSeReparten);
		nombresGanadores.push_back(ganador->getNombre());
	}

}

void ContextoJuego::finalizarRonda()
{
	if (this->cantidadJugadoresRonda > 1) {
		this->mostrandoCartas = true;
	}

	if (this->cantidadJugadoresRonda > 0) {
		this->evaluarGanador();
		this->timerMostrandoGanador.iniciar();
	}

	for (int i = 0; i < MAX_CANTIDAD_JUGADORES; i++) {
		JugadorModelo* jugador = this->admJugadores->getJugadores()[i];

		if (!jugador->isActivo()) {

			this->admJugadores->quitarJugador(this->idJugadorToIdCliente(jugador->getId()));

			if (this->admJugadores->isDealerJugador(jugador->getId())
				&& this->admJugadores->getCantidadJugadoresActivos() > 0) {
				this->admJugadores->resetearDealer();
				this->admJugadores->incrementarDealer();
			}
		}
	}

	AccesoDatos dao;
	for (int i = 0; i < MAX_CANTIDAD_JUGADORES; i++) {
		JugadorModelo* jugador = this->admJugadores->getJugadores()[i];
		jugador->setApuesta(0);		
		dao.actualizarFichas(jugador->getNombre(), jugador->getFichas());

		if (jugador->isJugandoRonda() && jugador->getFichas() <= this->mesa->getSmallBlind() * 2) {
			jugador->setJugandoRonda(false);
			jugador->setCarta1(NULL);
			jugador->setCarta2(NULL);
			jugador->setActivo(false);
		}
	}
}

string ContextoJuego::getEscenarioJuego(int idCliente){

	int idJugador = this->admJugadores->idClienteToIdJugador(idCliente);
	this->estado = this->estado->getSiguienteEstado();
	return this->estado->getEscenarioJuego(idJugador);
}

string ContextoJuego::getEscenarioJuego(int idCliente, string mensaje){

	int idJugador = this->admJugadores->idClienteToIdJugador(idCliente);
	this->estado = this->estado->getSiguienteEstado();
	return this->estado->getEscenarioJuego(idJugador, mensaje);
}

JugadorModelo** ContextoJuego::getJugadores() {
	return this->admJugadores->getJugadores();
}

JugadorModelo* ContextoJuego::getJugador(int idJugador){
	return this->admJugadores->getJugadorPorPosicion(idJugador + 1);
}

void ContextoJuego::setMostrandoCartas(bool mostrandoCartas){
	this->mostrandoCartas = mostrandoCartas;
}

bool ContextoJuego::getMostrandoCartas(){
	return this->mostrandoCartas;
}

bool ContextoJuego::hayLugar(){
	return this->admJugadores->hayLugar();
}

JugadorModelo* ContextoJuego::agregarJugador(int idCliente, string nombreJugador, 
			string nombreImagen, int fichas, bool esVirtual, bool esObservador){
	return this->admJugadores->agregarJugador(idCliente, nombreJugador, 
		nombreImagen, fichas, esVirtual, esObservador);
}

void ContextoJuego::quitarJugador(int idCliente){

	AccesoDatos dao;
	JugadorModelo* jugador = this->admJugadores->getJugador(idCliente);

	if (this->isTurnoCliente(idCliente) && !this->mostrandoCartas) {
		this->noIr(idCliente);
	
	} else {

		if (jugador != NULL && jugador->isJugandoRonda() && !this->mostrandoCartas) {

			if (this->cantidadJugadoresRonda > 0) {
				this->cantidadJugadoresRonda--;
			}

			if (this->cantidadJugadoresRonda > 1) {

				if (this->admJugadores->isDealerJugador(jugador->getId())) {
					this->admJugadores->incrementarDealerTemp();
				}

				if (this->admJugadores->isJugadorQueCierra(jugador->getId())){
					this->admJugadores->decrementarJugadorQueCierra();
				}
				jugador->setJugandoRonda(false);
				if (!(this->rondaAllIn || this->rondaTerminada)) {
					chequearRondaAllIn();
				}

			} else {

				jugador->setJugandoRonda(false);
				this->finalizarRonda();
				this->estado = this->evaluandoGanador;
			}
		}
	}

	if (jugador != NULL) {
		dao.actualizarFichas(jugador->getNombre(), jugador->getFichas());
	}

	this->admJugadores->quitarJugador(idCliente);
}

int ContextoJuego::getCantidadJugadoresActivos(){
	//return this->admJugadores->getCantidadJugadoresActivos();
	int jugadoresActivos = 0;
	for (int i = 0; i < MAX_CANTIDAD_JUGADORES; i++) {
		JugadorModelo* jugador = this->admJugadores->getJugadores()[i];
		if (jugador->isActivo() && jugador->getFichas() > this->mesa->getSmallBlind() * 2) {
			jugadoresActivos++;
		}
	}
	return jugadoresActivos;
}

bool ContextoJuego::isTurnoJugador(int idJugador){
	if (this->estado != this->esperandoJugadores && this->estado != this->evaluandoGanador) {
		this->chequearTimeoutJugador(idJugador);
	}

	return this->admJugadores->isTurnoJugador(idJugador);
}

void ContextoJuego::chequearTimeoutJugador(int idJugador) {

	JugadorModelo* jugador = this->admJugadores->getJugadorTurno();
	
	if (jugador != NULL && jugador->isActivo() && !jugador->isVirtual() 
		&& jugador->getSegundosTurno() > ContextoJuego::segsTimeoutJugadores) {

			this->noIr(this->idJugadorToIdCliente(jugador->getId()));		
			jugador->setActivo(false);
	}
}

bool ContextoJuego::isTurnoCliente(int idCliente){
	if (this->estado != this->esperandoJugadores && this->estado != this->evaluandoGanador) {
		this->chequearTimeoutJugador(this->idClienteToIdJugador(idCliente));
	}
	return this->admJugadores->isTurnoCliente(idCliente);
}

list<string> ContextoJuego::getNombresGanadores(){
	return this->nombresGanadores;
}

int ContextoJuego::idClienteToIdJugador(int idCliente){
	return this->admJugadores->idClienteToIdJugador(idCliente);
}

int ContextoJuego::idJugadorToIdCliente(int idJugador){
	return this->admJugadores->idJugadorToIdCliente(idJugador);
}

int ContextoJuego::getMontoAIgualar(){
	return this->montoAIgualar;
}

void ContextoJuego::chequearJugadorVirtual(int idCliente) {
	JugadorModelo* jugador = this->admJugadores->getJugador(idCliente);
	if (jugador != NULL && jugador->isVirtual() 
		&& this->estado != this->esperandoJugadores 
		&& this->estado != this->evaluandoGanador 
		&& this->isTurnoJugador(jugador->getId())) {

		jugador->jugar();	
	}
}

bool ContextoJuego::puedePasar(){
	return this->sePuedePasar;
}
