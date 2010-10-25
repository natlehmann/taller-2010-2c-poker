#include "MensajeModelo.h"

MensajeModelo::MensajeModelo(int id, string texto)
{
	this->id = id;
	this->texto = texto;
}

MensajeModelo::~MensajeModelo(void)
{
}

int MensajeModelo::getId(){
	return this->id;
}

string MensajeModelo::getTexto(){
	return this->texto;
}

void MensajeModelo::setTexto(string texto){
	this->texto = texto;
}
