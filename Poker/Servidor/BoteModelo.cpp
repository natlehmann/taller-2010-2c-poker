#include "BoteModelo.h"

BoteModelo::BoteModelo(int id, string nombreImagen)
{
	this->id = id;
	this->nombreImagen = nombreImagen;
	this->cantidad = 0;
}

BoteModelo::~BoteModelo(void)
{
}

int BoteModelo::getId(){
	return this->id;
}

string BoteModelo::getNombreImagen(){
	return this->nombreImagen;
}

int BoteModelo::getCantidad(){
	return this->cantidad;
}

void BoteModelo::incrementar(int cantidad){
	this->cantidad += cantidad;
}

int BoteModelo::vaciar(){
	int total = this->cantidad;
	this->cantidad = 0;
	return total;
}
