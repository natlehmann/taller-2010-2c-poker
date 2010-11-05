#include "MesaModelo.h"

MesaModelo::MesaModelo(int id, int smallBlind, string fondo)
{
	this->id = id;
	this->smallBlind = smallBlind;
	this->fondo = fondo;
	this->apuestaMaxima = 1000000;
}

MesaModelo::~MesaModelo(void)
{
}

int MesaModelo::getId(){
	return this->id;
}

int MesaModelo::getSmallBlind(){
	return this->smallBlind;
}

string MesaModelo::getFondo(){
	return this->fondo;
}

void MesaModelo::setApuestaMaxima(int apuestaMaxima){
	this->apuestaMaxima = apuestaMaxima;
}

int MesaModelo::getApuestaMaxima(){
	return this->apuestaMaxima;
}

