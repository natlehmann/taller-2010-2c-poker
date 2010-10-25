#include "ContextoJuego.h"
#include "PokerException.h"
#include "Repartidor.h"
#include "Jugada.h"

ContextoJuego ContextoJuego::instancia;

ContextoJuego::ContextoJuego(void)
{
	this->mesa = new MesaModelo(1);
	this->bote = new BoteModelo(2);
	this->mensaje = new MensajeModelo(3);
	this->cartasComunitarias = new CartasComunitariasModelo(4);

	this->montoAIgualar = 0;
	this->cantidadJugadoresRonda = 0;
	this->posicionJugadorTurno = 0;
	this->posicionJugadorQueAbre = 0;
	this->posicionJugadorQueCierra = 0;
	this->repartidor = new Repartidor();
}

ContextoJuego::~ContextoJuego(void)
{
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
	for (vector<JugadorModelo*>::iterator it = this->jugadores.begin(); it != this->jugadores.end(); ++it) {
		delete *it;
	}
	this->jugadores.clear();
}

ContextoJuego* ContextoJuego::getInstancia(){
	return &ContextoJuego::instancia;
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

void ContextoJuego::agregarJugador(int idJugador)
{
	if (this->jugadores.size() == 6)
		throw PokerException("Mesa completa.");

	// TODO: Aca habria que traer los datos del jugador de la base?
	int posicion = this->jugadores.size() + 1;
	JugadorModelo* jugador = new JugadorModelo(idJugador, "jugadorX", 1000, posicion, "");
	jugador->setActivo(true);
	this->jugadores.push_back(jugador);
}

JugadorModelo* ContextoJuego::getJugador(int idJugador)
{
	for (vector<JugadorModelo*>::iterator it = this->jugadores.begin(); it != this->jugadores.end(); ++it) {
		if ((*it)->getId() == idJugador) {
			return *it;
		}
	}
	return NULL;
}

int ContextoJuego::getCantidadJugadoresActivos()
{
	int jugadoresActivos = 0;
	for (vector<JugadorModelo*>::iterator it = this->jugadores.begin(); it != this->jugadores.end(); ++it) {
		if ((*it)->isActivo()) {
			jugadoresActivos++;
		}
	}
	return jugadoresActivos;
}

int ContextoJuego::getCantidadJugadoresJugandoRonda()
{
	return this->cantidadJugadoresRonda;
}

int ContextoJuego::getTurnoJugador()
{
	if (this->posicionJugadorTurno > 0)
		return this->jugadores.at(this->posicionJugadorTurno - 1)->getId();
	return 0;
}

bool ContextoJuego::isTurnoJugador(int idJugador)
{
	if (this->posicionJugadorTurno > 0)
		return (this->jugadores.at(this->posicionJugadorTurno - 1)->getId() == idJugador);
	return false;
}

void ContextoJuego::igualarApuesta(int idJugador)
{
	JugadorModelo* jugador = getJugador(idJugador);
	int montoApuesta = this->montoAIgualar - jugador->getApuesta();
	jugador->apostar(montoApuesta);
	this->bote->incrementar(montoApuesta);
	calcularPosicionJugadorTurno();
}

void ContextoJuego::subirApuesta(int idJugador, int fichas)
{
	JugadorModelo* jugador = getJugador(idJugador);
	jugador->apostar(fichas);
	this->bote->incrementar(fichas);
	this->montoAIgualar = jugador->getApuesta();
	this->posicionJugadorQueCierra = jugador->getPosicion();
	calcularPosicionJugadorTurno();
}

void ContextoJuego::noIr(int idJugador)
{
	JugadorModelo* jugador = getJugador(idJugador);
	jugador->setJugandoRonda(false);
	jugador->setApuesta(0);
	jugador->setCarta1(NULL);
	jugador->setCarta2(NULL);
	this->cantidadJugadoresRonda--;
	if (this->cantidadJugadoresRonda > 1 && jugador->getPosicion() == this->posicionJugadorQueAbre) {
		calcularPosicionJugadorQueAbre();
	}
	calcularPosicionJugadorTurno();
}

void ContextoJuego::iniciarJuego()
{
	int cantidadJugadoresActivos = getCantidadJugadoresActivos();
	if (cantidadJugadoresActivos < 2)
		throw PokerException("No hay suficientes jugadores para iniciar la ronda.");

	repartidor->mezclar();

	int numeroDeJugador = 1;
	for (vector<JugadorModelo*>::iterator it = this->jugadores.begin(); it != this->jugadores.end(); ++it) {
		JugadorModelo* jugador = *it;
		if (jugador->isActivo()) {
			jugador->setJugandoRonda(true);
			jugador->setCarta1(repartidor->getCarta());
			jugador->setCarta2(repartidor->getCarta());
			switch (numeroDeJugador) {
				case 1:
					if (cantidadJugadoresActivos == 2) {
						jugador->setApuesta(mesa->getSmallBlind());
						this->posicionJugadorTurno = jugador->getPosicion();
						this->posicionJugadorQueCierra = jugador->getPosicion();
					} else {
						if (cantidadJugadoresActivos == 3) {
							this->posicionJugadorTurno = jugador->getPosicion();
							this->posicionJugadorQueCierra = jugador->getPosicion();
						}
					}
					break;
				case 2:
					this->posicionJugadorQueAbre = jugador->getPosicion();
					if (cantidadJugadoresActivos == 2) {
						jugador->setApuesta(mesa->getSmallBlind() * 2);
					} else {
						jugador->setApuesta(mesa->getSmallBlind());
					}
					break;
				case 3:
					jugador->setApuesta(mesa->getSmallBlind() * 2);
					break;
				case 4:
					this->posicionJugadorTurno = jugador->getPosicion();
					this->posicionJugadorQueCierra = jugador->getPosicion();
					break;
			}
			numeroDeJugador++;
		}
	}
	this->bote->vaciar();
	this->bote->incrementar(mesa->getSmallBlind() * 3);
	this->montoAIgualar = mesa->getSmallBlind() * 2;
	this->cantidadJugadoresRonda = cantidadJugadoresActivos;
}

void ContextoJuego::mostrarFlop()
{
	for (int i=0 ; i<3 ; ++i) {
		this->cartasComunitarias->agregarCarta(repartidor->getCarta());
	}
	this->posicionJugadorTurno = this->posicionJugadorQueAbre;
	this->posicionJugadorQueCierra = this->posicionJugadorQueAbre;
}

void ContextoJuego::mostrarTurn()
{
	this->cartasComunitarias->agregarCarta(repartidor->getCarta());
	this->posicionJugadorTurno = this->posicionJugadorQueAbre;
	this->posicionJugadorQueCierra = this->posicionJugadorQueAbre;
}

void ContextoJuego::mostrarRiver()
{
	this->cartasComunitarias->agregarCarta(repartidor->getCarta());
	this->posicionJugadorTurno = this->posicionJugadorQueAbre;
	this->posicionJugadorQueCierra = this->posicionJugadorQueAbre;
}

void ContextoJuego::calcularPosicionJugadorTurno()
{
	if (this->cantidadJugadoresRonda < 2) {
		this->posicionJugadorTurno = 0;
		return;
	}

	int posicionJugadorTurnoAnterior = this->posicionJugadorTurno;
	int inicio;
	if (this->posicionJugadorTurno == jugadores.size()) {
		inicio = 0;
	} else {
		inicio = this->posicionJugadorTurno;
	}
	for (unsigned int i = inicio ; i < jugadores.size() ; ++i) {
		if (this->jugadores[i]->isJugandoRonda()) {
			if (this->jugadores[i]->getPosicion() == this->posicionJugadorQueCierra) {
				this->posicionJugadorTurno = 0;
			} else {
				this->posicionJugadorTurno = this->jugadores[i]->getPosicion();
			}
			break;
		}
	}

	if (this->posicionJugadorTurno == posicionJugadorTurnoAnterior) {
		if (inicio == 0) {
			throw PokerException("Ocurrio un error en la asignacion de turnos.");
		}

		for (unsigned int i = 0 ; i < jugadores.size() ; ++i) {
			if (this->jugadores[i]->isJugandoRonda()) {
				if (this->jugadores[i]->getPosicion() == this->posicionJugadorQueCierra) {
					this->posicionJugadorTurno = 0;
				} else {
					this->posicionJugadorTurno = this->jugadores[i]->getPosicion();
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
	if (this->posicionJugadorQueAbre == jugadores.size()) {
		inicio = 0;
	} else {
		inicio = this->posicionJugadorQueAbre;
	}
	for (unsigned int i = inicio ; i < jugadores.size() ; ++i) {
		if (this->jugadores[i]->isJugandoRonda()) {
			this->posicionJugadorQueAbre = this->jugadores[i]->getPosicion();
			break;
		}
	}

	if (this->posicionJugadorQueAbre == posicionJugadorQueAbreAnterior) {
		if (inicio == 0) {
			throw PokerException("Ocurrio un error buscando el jugador que abre ronda.");
		}

		for (unsigned int i = 0 ; i < jugadores.size() ; ++i) {
			if (this->jugadores[i]->isJugandoRonda()) {
				this->posicionJugadorQueAbre = this->jugadores[i]->getPosicion();
				break;
			}
		}

		if (this->posicionJugadorQueAbre == posicionJugadorQueAbreAnterior) {
			throw PokerException("Ocurrio un error buscando el jugador que abre ronda.");
		}
	}
}

int ContextoJuego::evaluarGanador()
{
	JugadorModelo* ganador;
	if (this->cantidadJugadoresRonda < 2) {
		for (vector<JugadorModelo*>::iterator it = this->jugadores.begin(); it != this->jugadores.end(); ++it) {
			JugadorModelo* jugador = *it;
			if (jugador->isJugandoRonda()) {
				ganador = jugador;
				break;
			}
		}
	} else {
		double valorJugadaMasAlta = 0;
		JugadorModelo* ganador = NULL;
		for (vector<JugadorModelo*>::iterator it = this->jugadores.begin(); it != this->jugadores.end(); ++it) {
			JugadorModelo* jugador = *it;
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
	for (vector<JugadorModelo*>::iterator it = this->jugadores.begin(); it != this->jugadores.end(); ++it) {
		JugadorModelo* jugador = *it;
		jugador->setApuesta(0);
		jugador->setCarta1(NULL);
		jugador->setCarta2(NULL);
		jugador->setJugandoRonda(false);
	}
	this->cartasComunitarias->limpiar();
	this->bote->vaciar();
	this->montoAIgualar = 0;
	this->cantidadJugadoresRonda = 0;
	this->posicionJugadorTurno = 0;
	this->posicionJugadorQueAbre = 0;
	this->posicionJugadorQueCierra = 0;
}
