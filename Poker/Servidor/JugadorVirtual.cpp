#include "JugadorVirtual.h"


JugadorVirtual::JugadorVirtual(int id, int posicion): JugadorModelo(id, posicion)
{
	this->apuestaPatron = APUESTA_PATRON;
	this->nivelDeConfianza = CONFIANZA;
}

JugadorVirtual::JugadorVirtual(int id, string nombre, int fichas, int posicion, string nombreImagen): JugadorModelo(id, nombre, fichas, posicion, nombreImagen)
{
	this->apuestaPatron = APUESTA_PATRON;
	this->nivelDeConfianza = CONFIANZA;
}

JugadorVirtual::~JugadorVirtual(void)
{
}


OpJugadorVirtual* JugadorVirtual::Jugar()
{
	return new OpNoIrJugadorVirtual(1);
}


