#include "IteradorRonda.h"

IteradorRonda::IteradorRonda(JugadorModelo** jugadores, int indiceInicial)
{
	this->jugadores = jugadores;
	this->reset(indiceInicial);
}

IteradorRonda::~IteradorRonda(void)
{
}

void IteradorRonda::reset(int indiceInicial){
	this->indiceInicial = indiceInicial;
	this->indiceCorriente = indiceInicial;
	this->indiceAnterior = indiceInicial;
	this->iniciado = false;
}

JugadorModelo* IteradorRonda::getSiguiente(){

	this->iniciado = true;
	this->indiceAnterior = this->indiceCorriente;

	JugadorModelo* retorno = this->jugadores[this->indiceCorriente];

	this->indiceCorriente++;

	if (this->indiceCorriente >= MAX_CANTIDAD_JUGADORES){
		this->indiceCorriente = 0;
	}

	return retorno;
}

bool IteradorRonda::esUltimo(){
	return (this->indiceCorriente == this->indiceInicial) && this->iniciado;
}

