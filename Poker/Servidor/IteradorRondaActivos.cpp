#include "IteradorRondaActivos.h"

IteradorRondaActivos::IteradorRondaActivos(JugadorModelo** jugadores, int indiceInicial) 
	: IteradorRonda(jugadores, indiceInicial) {

	this->setIndiceFinal();
}

IteradorRondaActivos::~IteradorRondaActivos(void)
{
}

void IteradorRondaActivos::reset(int indiceInicial){

	IteradorRonda::reset(indiceInicial);
	this->setIndiceFinal();
}

void IteradorRondaActivos::setIndiceFinal(){

	if (this->indiceInicial >= 0) {

		this->indiceFinal = this->indiceInicial;
		bool encontrado = false;

		while (!encontrado) {

			this->indiceFinal--;

			if (this->indiceFinal < 0) {
				this->indiceFinal = MAX_CANTIDAD_JUGADORES - 1;
			}

			if (this->jugadores[this->indiceFinal]->isActivo() || this->indiceFinal == this->indiceInicial) {
				encontrado = true;
			}
		}
	}
}


JugadorModelo* IteradorRondaActivos::getSiguiente(){

	this->iniciado = true;

	// primero buscamos al jugador
	JugadorModelo* jugador = this->jugadores[this->indiceCorriente];

	while (!jugador->isActivo() && this->indiceCorriente != this->indiceFinal) {
		this->indiceCorriente++;

		if (this->indiceCorriente >= MAX_CANTIDAD_JUGADORES){
			this->indiceCorriente = 0;
		}

		jugador = this->jugadores[this->indiceCorriente];
	}

	// ahora seteamos el puntero al proximo jugador activo
	if (jugador->isActivo()){

		this->indiceCorriente++;
		if (this->indiceCorriente >= MAX_CANTIDAD_JUGADORES){
			this->indiceCorriente = 0;
		}

		JugadorModelo* proximoJugador = this->jugadores[this->indiceCorriente];
		while (!proximoJugador->isActivo()) {

			this->indiceCorriente++;
			if (this->indiceCorriente >= MAX_CANTIDAD_JUGADORES){
				this->indiceCorriente = 0;
			}
			proximoJugador = this->jugadores[this->indiceCorriente];
		}

	} else {
		jugador = NULL;
		this->indiceCorriente = -1;
	}

	return jugador;

}

