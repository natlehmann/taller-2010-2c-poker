#include "Carta.h"
#include "ServiciosGraficos.h"

Carta::Carta(void)
{
	this->imagen = NULL;
	this->setAncho(ServiciosGraficos::getTamanioCeldaHoriz());
	this->setAlto(ServiciosGraficos::getTamanioCeldaVert());
	this->numero = "";
	this->palo = "";
	this->visible = false;
}

Carta::~Carta(void)
{
	if (this->imagen != NULL) 
		delete(this->imagen);
}

void Carta::dibujarSobreSup(SDL_Surface* superficie)
{
}

string Carta::getNumero() 
{
	return this->numero;
}

void Carta::setNumero(string numero) 
{
	this->numero = numero;
}

string Carta::getPalo() 
{
	return this->palo;
}

void Carta::setPalo(string palo)
{
	this->palo = palo;
}

bool Carta::getVisible() 
{
	return this->visible;
}

void Carta::setVisible(bool visible) 
{
	this->visible = visible;
}