#include "AdministradorJugadores.h"
#include "PokerException.h"
#include "IteradorRondaJugando.h"
#include "JugadorModelo.h"

AdministradorJugadores::AdministradorJugadores(void)
{
	for (int i = 0; i < MAX_CANTIDAD_JUGADORES; i++) {
		// inicialmente los jugadores no tienen ningun cliente asociado
		this->idsJugadores[i] = -1;
	}

	for (int i = 0; i < MAX_CANTIDAD_JUGADORES; i++) {
		this->agregarJugadorAusente(i);
	}

	this->jugadorTurno = -1;
	this->dealer = -1;
	this->dealerAnterior = -1;
	this->jugadorQueCierra = -1;
}

AdministradorJugadores::~AdministradorJugadores(void)
{
	for (int i = 0; i < MAX_CANTIDAD_JUGADORES; i++) {
		delete this->jugadores[i];
	}
}

int AdministradorJugadores::idClienteToIdJugador(int idCliente){
	int idJugador = -1;
	int i = 0;

	while (i < MAX_CANTIDAD_JUGADORES && idJugador < 0){
		if (this->idsJugadores[i] == idCliente){
			idJugador = i;
		}
		i++;
	}

	return idJugador;
}

int AdministradorJugadores::idJugadorToIdCliente(int idJugador){
	return this->idsJugadores[idJugador];
}

JugadorModelo* AdministradorJugadores::getPrimerJugadorAusente() {

	int i = 0;
	JugadorModelo* jugador = NULL;

	while (i < MAX_CANTIDAD_JUGADORES && jugador == NULL) {
		if (this->jugadores[i]->isAusente()) {
			jugador = this->jugadores[i];
		}
		i++;
	}

	return jugador;
}

JugadorModelo* AdministradorJugadores::agregarJugador(int idCliente, 
		string nombreJugador, string nombreImagen, int fichas, bool esVirtual, bool esObservador)
{
	JugadorModelo* jugador = this->getPrimerJugadorAusente();

	if (jugador == NULL) {
		throw PokerException("Mesa completa.");
	}

	this->idsJugadores[jugador->getId()] = idCliente;

	jugador->setNombre(nombreJugador);
	jugador->setFichas(fichas);
	jugador->setApuesta(0);
	jugador->setNombreImagen(nombreImagen);
	jugador->setVirtual(esVirtual);
	jugador->setObservador(esObservador);

	jugador->setAusente(false);
	jugador->setActivo(true);

	return jugador;
}

void AdministradorJugadores::agregarJugadorAusente(int idJugador)
{
	int posicion = idJugador + 1;
	JugadorModelo* jugador = new JugadorModelo(idJugador, posicion);
	this->jugadores[idJugador] = jugador;
}

void AdministradorJugadores::quitarJugador(int idCliente)
{
	int idJugador = this->idClienteToIdJugador(idCliente);
	if (idJugador >= 0) {
		JugadorModelo* jugador = this->jugadores[idJugador];
		delete jugador;
		int posicion = idJugador + 1;
		jugador = new JugadorModelo(idJugador, posicion);
		this->jugadores[idJugador] = jugador;
		this->idsJugadores[idJugador] = -1;
	} else {
		// nada. podría tratarse de un jugador que no pudo entrar
	}
}

JugadorModelo* AdministradorJugadores::getJugadorPorPosicion(int posicion){

	if (posicion <= MAX_CANTIDAD_JUGADORES && posicion > 0) {

		return this->jugadores[posicion - 1];
	
	} else {
		// nada. podría tratarse de un jugador que ya salio del juego por inactivo
	}
}

JugadorModelo* AdministradorJugadores::getJugador(int idCliente)
{
	int idJugador = this->idClienteToIdJugador(idCliente);

	if (idJugador >= 0) {
		return this->jugadores[idJugador];

	} else {
		return NULL;
	}
}

int AdministradorJugadores::getCantidadJugadoresActivos()
{
	int jugadoresActivos = 0;
	for (int i = 0; i < MAX_CANTIDAD_JUGADORES; i++) {
		if (this->jugadores[i]->isActivo()) {
			jugadoresActivos++;
		}
	}
	return jugadoresActivos;
}

bool AdministradorJugadores::isTurnoCliente(int idCliente){

	int idJugador = this->idClienteToIdJugador(idCliente);
	return this->isTurnoJugador(idJugador);
}

bool AdministradorJugadores::isTurnoJugador(int idJugador)
{
	if (this->jugadorTurno >= 0) {
		return (this->jugadorTurno == idJugador); // los ids de los jugadores son iguales a sus posiciones en el array
	}

	return false;
}

bool AdministradorJugadores::isDealerJugador(int idJugador) {
	if (this->dealer >= 0) {
		return (this->dealer == idJugador);
	}
	return false;
}

bool AdministradorJugadores::isJugadorQueCierra(int idJugador){
	if (this->jugadorQueCierra >= 0) {
		return (this->jugadorQueCierra == idJugador);
	}
	return false;
}

bool AdministradorJugadores::hayLugar(){
	return this->getPrimerJugadorAusente() != NULL;
}

JugadorModelo** AdministradorJugadores::getJugadores() {
	return this->jugadores;
}

void AdministradorJugadores::resetearJugadorTurno(){
	this->jugadorTurno = this->getIndiceJugadorMano();
	this->jugadorQueCierra = this->getIndiceJugadorMano();
}

int AdministradorJugadores::getIndiceJugadorMano() {

	int indiceTurno = this->dealer;

	bool encontrado = false;

	while (!encontrado) {

		indiceTurno++;

		if (indiceTurno >= MAX_CANTIDAD_JUGADORES) {
			indiceTurno = 0;
		}

		if ((this->jugadores[indiceTurno]->isActivo() && this->jugadores[indiceTurno]->isJugandoRonda())
			|| indiceTurno == this->dealer ){
			encontrado = true;

			this->jugadores[indiceTurno]->resetTimer();
		}
	}

	return indiceTurno;

}

void AdministradorJugadores::incrementarTurno(){

	IteradorRondaJugando* it = this->getIteradorRondaJugando(this->jugadorTurno);
	it->getSiguiente(); // descarto al jugador del turno actual

	JugadorModelo* jugador = it->getSiguiente();
	this->jugadorTurno = jugador->getPosicion() - 1;
	delete (it); 
	jugador->resetTimer();
}

IteradorRonda* AdministradorJugadores::getIteradorRonda(){
	return new IteradorRonda(this->jugadores, this->getIndiceJugadorMano());
}

IteradorRondaActivos* AdministradorJugadores::getIteradorRondaActivos(){
	return new IteradorRondaActivos(this->jugadores, this->getIndiceJugadorMano());
}

IteradorRondaJugando* AdministradorJugadores::getIteradorRondaJugando(){
	return new IteradorRondaJugando(this->jugadores, this->getIndiceJugadorMano());
}

IteradorRondaJugando* AdministradorJugadores::getIteradorRondaJugando(int indiceInicial){
	return new IteradorRondaJugando(this->jugadores, indiceInicial);
}

void AdministradorJugadores::incrementarDealerTemp(){
	this->dealerAnterior = this->dealer;
	this->incrementarDealer();
}

void AdministradorJugadores::resetearDealer() {
	if (this->dealerAnterior >= 0) {
		this->dealer = this->dealerAnterior;
	}
	this->dealerAnterior = -1;
}

void AdministradorJugadores::incrementarDealer(){

	if (this->dealer >= 0) {
		this->jugadores[this->dealer]->setDealer(false);
	}

	bool encontrado = false;

	while (!encontrado) {

		this->dealer++;

		if (this->dealer >= MAX_CANTIDAD_JUGADORES) {
			this->dealer = 0;
		}

		if (this->jugadores[this->dealer]->isActivo()) {
			encontrado = true;
			this->jugadores[this->dealer]->setDealer(true);
		}
	}

}

void AdministradorJugadores::decrementarJugadorQueCierra(){

	if (this->jugadorQueCierra >= 0) {

		bool encontrado = false;

		while (!encontrado) {

			this->jugadorQueCierra--;

			if (this->jugadorQueCierra < 0) {
				this->jugadorQueCierra = MAX_CANTIDAD_JUGADORES - 1;
			}

			if (this->jugadores[this->jugadorQueCierra]->isActivo()
				&& this->jugadores[this->jugadorQueCierra]->isJugandoRonda()) {
				encontrado = true;
			}
		}

	} else {
		throw PokerException("Se solicito decrementar el jugador que cierra en un contexto invalido.");
	}
}

void AdministradorJugadores::setJugadorQueCierra(int idJugador) {
	this->jugadorQueCierra = idJugador;
}

void AdministradorJugadores::setJugadorQueCierraActual() {
	this->jugadorQueCierra = this->jugadorTurno;
}

bool AdministradorJugadores::isRondaTerminada() {
	if (this->jugadorTurno < 0) {
		return false;
	}
	return this->jugadorTurno == this->jugadorQueCierra;
}