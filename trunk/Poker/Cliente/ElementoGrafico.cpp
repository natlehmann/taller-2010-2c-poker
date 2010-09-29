#include "ElementoGrafico.h"

ElementoGrafico::ElementoGrafico(void) {
	this->superficie = NULL;
	this->posX = 0;
	this->posY = 0;
	this->offset = new SDL_Rect();
}

ElementoGrafico::~ElementoGrafico(void){
	if (this->superficie != NULL) {
		SDL_FreeSurface(this->superficie); 
	}
	delete (this->offset);
}

SDL_Surface* ElementoGrafico::getSuperficie() {
	return this->superficie;
}

SDL_Rect* ElementoGrafico::getOffsetRect() {
	this->offset->x = this->getPosX();
	this->offset->y = this->getPosY();
	this->offset->w = this->getAncho();
	this->offset->h = this->getAlto();

	return this->offset;
}

int ElementoGrafico::getPosX() {
	return this->posX;
}
void ElementoGrafico::setPosX(int posX) {
	this->posX = posX;
}
int ElementoGrafico::getPosY() {
	return this->posY;
}
void ElementoGrafico::setPosY(int posY) {
	this->posY = posY;
}
int ElementoGrafico::getAncho() {
	return this->ancho;
}
void ElementoGrafico::setAncho(int ancho) {
	this->ancho = ancho;
}
int ElementoGrafico::getAlto() {
	return this->alto;
}
void ElementoGrafico::setAlto(int alto) {
	this->alto = alto;
}