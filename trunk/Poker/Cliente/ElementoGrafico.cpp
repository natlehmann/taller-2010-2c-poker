#include "ElementoGrafico.h"

ElementoGrafico::ElementoGrafico(void) {
	this->superficie = NULL;
	this->posX = 0;
	this->posY = 0;
}

ElementoGrafico::~ElementoGrafico(void){
	SDL_FreeSurface(this->superficie); 
}

SDL_Surface* ElementoGrafico::getSuperficie() {
	return this->superficie;
}

SDL_Rect* ElementoGrafico::getOffsetRect() {
	SDL_Rect offset;
	offset.x = this->getPosX();
	offset.y = this->getPosY();
	offset.w = this->getAncho();
	offset.h = this->getAlto();

	return &offset;
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