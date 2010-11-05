#include "AdministradorJugadores.h"
#include "PokerException.h"
#include "IteradorRondaJugando.h"

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

void AdministradorJugadores::agregarJugador(int idCliente)
{
	JugadorModelo* jugador = this->getPrimerJugadorAusente();

	if (jugador == NULL) {
		throw PokerException("Mesa completa.");
	}

	this->idsJugadores[jugador->getId()] = idCliente;

	// TODO: Aca habria que traer los datos del jugador de la base?
	// TODO: REEMPLAZAR ESTO !
	jugador->setNombre("jugadorX");
	jugador->setFichas(1000);
	jugador->setApuesta(0);
	jugador->setNombreImagen("jugador2.bmp");

	jugador->setAusente(false);
	jugador->setActivo(true);
}

void AdministradorJugadores::agregarJugadorAusente(int idJugador)
{
	int posicion = idJugador + 1;
	JugadorModelo* jugador = new JugadorModelo(idJugador, posicion);
	this->jugadores[idJugador] = jugador;
}

JugadorModelo* AdministradorJugadores::getJugadorPorPosicion(int posicion){

	if (posicion <= MAX_CANTIDAD_JUGADORES && posicion > 0) {

		return this->jugadores[posicion - 1];
	
	} else {
		throw PokerException("Posicion de jugador invalida");
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

bool AdministradorJugadores::hayLugar(){
	return this->getPrimerJugadorAusente() != NULL;
}

JugadorModelo** AdministradorJugadores::getJugadores() {
	return this->jugadores;
}

void AdministradorJugadores::resetearJugadorTurno(){
	this->jugadorTurno = this->getIndiceJugadorMano();
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
		}
	}

	return indiceTurno;

}

void AdministradorJugadores::incrementarTurno(){

	IteradorRondaJugando* it = this->getIteradorRondaJugando(this->jugadorTurno);
	it->getSiguiente(); // descarto al jugador del turno actual
	this->jugadorTurno = it->getSiguiente()->getPosicion() - 1;
	delete (it);
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

void AdministradorJugadores::incrementarDealer(){
	bool encontrado = false;

	while (!encontrado) {

		this->dealer++;

		if (this->dealer >= MAX_CANTIDAD_JUGADORES) {
			this->dealer = 0;
		}

		if (this->jugadores[this->dealer]->isActivo()) {
			encontrado = true;
		}
	}

}
