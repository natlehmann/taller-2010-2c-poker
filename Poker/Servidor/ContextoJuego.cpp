#include "ContextoJuego.h"
#include "PokerException.h"
#include "Repartidor.h"
#include "Jugada.h"
#include "RecursosServidor.h"
#include "UtilTiposDatos.h"
#include "IteradorRonda.h"
#include "IteradorRondaActivos.h"

ContextoJuego ContextoJuego::instancia;

ContextoJuego::ContextoJuego(void)
{
	this->mutex = CreateMutexA(NULL, false, "MutexContexto");

	this->admJugadores = new AdministradorJugadores();

	this->mesa = new MesaModelo(10, 
		UtilTiposDatos::getEntero(
			RecursosServidor::getConfig()->get("servidor.mesa.smallBlind")), 
		RecursosServidor::getConfig()->get("servidor.mesa.fondo"));
		
	this->bote = new BoteModelo(11);
	this->mensaje = new MensajeModelo(12);
	this->cartasComunitarias = new CartasComunitariasModelo(13);

	this->montoAIgualar = 0;
	this->cantidadJugadoresRonda = 0;
	this->posicionJugadorTurno = 0;
	this->posicionJugadorQueAbre = 0;
	this->posicionJugadorQueCierra = 0;
	this->repartidor = new Repartidor();
	this->rondaTerminada = false;
	this->mostrandoCartas = false;

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
	delete (this->rondaTurn);
	delete (this->rondaRiver);
	delete (this->evaluandoGanador);

	CloseHandle(this->mutex);
}

HANDLE ContextoJuego::getMutex(){
	return this->mutex;
}

ContextoJuego* ContextoJuego::getInstancia(){
	return &ContextoJuego::instancia;
}

int ContextoJuego::getTiempoEsperandoJugadores(){
	return this->timerEsperandoJugadores.getSegundos();
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

int ContextoJuego::getCantidadJugadoresJugandoRonda()
{
	return this->cantidadJugadoresRonda;
}


void ContextoJuego::igualarApuesta(int idCliente)
{
	JugadorModelo* jugador = this->admJugadores->getJugador(idCliente);
	int montoApuesta = this->montoAIgualar - jugador->getApuesta();
	jugador->apostar(montoApuesta);
	this->bote->incrementar(montoApuesta);
	//calcularPosicionJugadorTurno();
	this->admJugadores->incrementarTurno();
	chequearRondaTerminada();
}

void ContextoJuego::subirApuesta(int idCliente, int fichas)
{
	JugadorModelo* jugador = this->admJugadores->getJugador(idCliente);
	jugador->apostar(fichas);
	this->bote->incrementar(fichas);
	this->montoAIgualar = jugador->getApuesta();
	//this->posicionJugadorQueCierra = jugador->getPosicion();
	//calcularPosicionJugadorTurno();
	this->admJugadores->incrementarTurno();
	chequearRondaTerminada();
}

void ContextoJuego::noIr(int idCliente)
{
	JugadorModelo* jugador = this->admJugadores->getJugador(idCliente);
	jugador->setJugandoRonda(false);
	jugador->setApuesta(0);
	jugador->setCarta1(NULL);
	jugador->setCarta2(NULL);
	this->cantidadJugadoresRonda--;
	/*
	if (this->cantidadJugadoresRonda > 1 && jugador->getPosicion() == this->posicionJugadorQueAbre) {
		calcularPosicionJugadorQueAbre();
	}
	*/
	//calcularPosicionJugadorTurno();
	this->admJugadores->incrementarTurno();
	chequearRondaTerminada();
}

void ContextoJuego::chequearRondaTerminada() {

	bool terminada = true;

	if (this->cantidadJugadoresRonda > 1) {
		for (int i = 0; i < MAX_CANTIDAD_JUGADORES; i++) { 

			if (this->admJugadores->getJugadores()[i]->isJugandoRonda() 
				&& this->admJugadores->getJugadores()[i]->getApuesta() != this->montoAIgualar) {
				terminada = false;
			}
		}
	}

	this->rondaTerminada = terminada;
}

bool ContextoJuego::isRondaTerminada(){
	return this->rondaTerminada;
}

void ContextoJuego::iniciarJuego() {

	int cantidadJugadoresActivos = getCantidadJugadoresActivos();
	if (cantidadJugadoresActivos < 2) {
		throw PokerException("No hay suficientes jugadores para iniciar la ronda.");
	}

	repartidor->mezclar();
	this->bote->vaciar();
	this->mostrandoCartas = false;

	// TODO: VER SI SACAMOS A LOS NO ACTIVOS DE LA MESA
	for (int i = 0; i < MAX_CANTIDAD_JUGADORES; i++) {
		if (this->admJugadores->getJugadores()[i]->isActivo()) {
			this->admJugadores->getJugadores()[i]->setJugandoRonda(true);
		}
		this->admJugadores->getJugadores()[i]->setApuesta(0);
	}

	this->admJugadores->incrementarDealer();
	this->admJugadores->resetearJugadorTurno();


	int blind = 1;
	IteradorRondaActivos* it = this->admJugadores->getIteradorRondaActivos();
	while (!it->esUltimo()) {

		JugadorModelo* jugador = it->getSiguiente();
		jugador->setCarta1(repartidor->getCarta());
		jugador->setCarta2(repartidor->getCarta());

		if (blind <= 2) {

			if (!this->admJugadores->isDealerJugador(jugador->getId())) {
				jugador->apostar(mesa->getSmallBlind() * blind);
				this->bote->incrementar(mesa->getSmallBlind() * blind);
				this->admJugadores->incrementarTurno();
				blind++;
			}
		}
	}

	
	if (blind >= 2) {
		blind--;
		this->montoAIgualar = mesa->getSmallBlind() * blind;
	}
	
	this->cantidadJugadoresRonda = cantidadJugadoresActivos;
	this->rondaTerminada = false;

	delete(it);
}

void ContextoJuego::iniciarRonda() {

	this->admJugadores->resetearJugadorTurno();
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

/*
void ContextoJuego::calcularPosicionJugadorTurno()
{
	if (this->cantidadJugadoresRonda < 2) {
		this->posicionJugadorTurno = 0;
		return;
	}

	int posicionJugadorTurnoAnterior = this->posicionJugadorTurno;
	int inicio;
	if (this->posicionJugadorTurno == MAX_CANTIDAD_JUGADORES) {
		inicio = 0;
	} else {
		inicio = this->posicionJugadorTurno;
	}
	for (int i = 0; i < MAX_CANTIDAD_JUGADORES; i++) {
		if (this->admJugadores->getJugadores()[i]->isJugandoRonda()) {
			if (this->admJugadores->getJugadores()[i]->getPosicion() == this->posicionJugadorQueCierra) {
				this->posicionJugadorTurno = 0;
			} else {
				this->posicionJugadorTurno = this->admJugadores->getJugadores()[i]->getPosicion();
			}
			break;
		}
	}

	if (this->posicionJugadorTurno == posicionJugadorTurnoAnterior) {
		if (inicio == 0) {
			throw PokerException("Ocurrio un error en la asignacion de turnos.");
		}

		for (int i = 0; i < MAX_CANTIDAD_JUGADORES; i++) {
			if (this->admJugadores->getJugadores()[i]->isJugandoRonda()) {
				if (this->admJugadores->getJugadores()[i]->getPosicion() == this->posicionJugadorQueCierra) {
					this->posicionJugadorTurno = 0;
				} else {
					this->posicionJugadorTurno = this->admJugadores->getJugadores()[i]->getPosicion();
				}
				break;
			}
		}

		if (this->posicionJugadorTurno == posicionJugadorTurnoAnterior) {
			throw PokerException("Ocurrio un error en la asignacion de turnos.");
		}
	}
}

void ContextoJuego::calcularPosicionJugadorQueAbre()
{
	int posicionJugadorQueAbreAnterior = this->posicionJugadorQueAbre;
	int inicio;
	if (this->posicionJugadorQueAbre == MAX_CANTIDAD_JUGADORES) {
		inicio = 0;
	} else {
		inicio = this->posicionJugadorQueAbre;
	}
	for (int i = 0; i < MAX_CANTIDAD_JUGADORES; i++) {
		if (this->admJugadores->getJugadores()[i]->isJugandoRonda()) {
			this->posicionJugadorQueAbre = this->admJugadores->getJugadores()[i]->getPosicion();
			break;
		}
	}

	if (this->posicionJugadorQueAbre == posicionJugadorQueAbreAnterior) {
		if (inicio == 0) {
			throw PokerException("Ocurrio un error buscando el jugador que abre ronda.");
		}

		for (int i = 0; i < MAX_CANTIDAD_JUGADORES; i++) {
			if (this->admJugadores->getJugadores()[i]->isJugandoRonda()) {
				this->posicionJugadorQueAbre = this->admJugadores->getJugadores()[i]->getPosicion();
				break;
			}
		}

		if (this->posicionJugadorQueAbre == posicionJugadorQueAbreAnterior) {
			throw PokerException("Ocurrio un error buscando el jugador que abre ronda.");
		}
	}
}
*/

// TODO: Deberia devolver id de CLiente o de Jugador ??
int ContextoJuego::evaluarGanador()
{
	JugadorModelo* ganador;
	if (this->cantidadJugadoresRonda < 2) {
		for (int i = 0; i < MAX_CANTIDAD_JUGADORES; i++) {
			JugadorModelo* jugador = this->admJugadores->getJugadores()[i];
			if (jugador->isJugandoRonda()) {
				ganador = jugador;
				break;
			}
		}
	} else {
		double valorJugadaMasAlta = 0;
		JugadorModelo* ganador = NULL;
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
					ganador = jugador;
				}
			}
		}
	}
	if (!ganador) {
		throw PokerException("Ocurrio un error evaluando al ganador.");
	}
	ganador->incrementarFichas(this->bote->vaciar());
	ganador->setApuesta(0);
	return ganador->getId();
}

void ContextoJuego::finalizarRonda()
{
	for (int i = 0; i < MAX_CANTIDAD_JUGADORES; i++) {
		JugadorModelo* jugador = this->admJugadores->getJugadores()[i];
		jugador->setApuesta(0);
		jugador->setCarta1(NULL);
		jugador->setCarta2(NULL);
		jugador->setJugandoRonda(false);
	}
	//this->cartasComunitarias->limpiar();
	this->bote->vaciar();
	this->montoAIgualar = 0;
	this->cantidadJugadoresRonda = 0;
	this->posicionJugadorTurno = 0;
	this->posicionJugadorQueAbre = 0;
	this->posicionJugadorQueCierra = 0;
}

string ContextoJuego::getEscenarioJuego(int idCliente){

	int idJugador = this->admJugadores->idClienteToIdJugador(idCliente);
	this->estado = this->estado->getSiguienteEstado();
	return this->estado->getEscenarioJuego(idJugador);
}

JugadorModelo** ContextoJuego::getJugadores() {
	return this->admJugadores->getJugadores();
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

void ContextoJuego::agregarJugador(int idCliente){
	this->admJugadores->agregarJugador(idCliente);
}

int ContextoJuego::getCantidadJugadoresActivos(){
	return this->admJugadores->getCantidadJugadoresActivos();
}

bool ContextoJuego::isTurnoJugador(int idJugador){
	return this->admJugadores->isTurnoJugador(idJugador);
}

bool ContextoJuego::isTurnoCliente(int idCliente){
	return this->admJugadores->isTurnoCliente(idCliente);
}