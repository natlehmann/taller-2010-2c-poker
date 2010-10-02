#include "Bote.h"

Bote::Bote(void)
{
	this->imagen = NULL;
	this->total = 0;
}

Bote::~Bote(void)
{
	if (this->imagen != NULL) 
		delete(this->imagen);
}

void Bote::dibujarSobreSup(SDL_Surface* superficie)
{
}

int Bote::getTotal() 
{
	return this->total;
}

void Bote::setTotal(int total) 
{
	this->total = total;
}
