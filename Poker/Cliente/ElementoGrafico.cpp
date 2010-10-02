#include "ElementoGrafico.h"
#include "ServiciosGraficos.h"

ElementoGrafico::ElementoGrafico(void) {
	this->superficie = NULL;
	this->posX = 0;
	this->posY = 0;
	this->offset = new SDL_Rect();
	this->contorno = new SDL_Rect();
}

ElementoGrafico::~ElementoGrafico(void){
	if (this->superficie != NULL) {
		SDL_FreeSurface(this->superficie);
		this->superficie = NULL;
	}
	delete (this->offset);
	delete (this->contorno);
}

SDL_Surface* ElementoGrafico::getSuperficie() {
	return this->superficie;
}

SDL_Rect* ElementoGrafico::getOffsetRect() {
	this->offset->x = this->getPosX();
	this->offset->y = this->getPosY();

	return this->offset;
}

SDL_Rect* ElementoGrafico::getContornoRect() {
	this->contorno->x = 0;
	this->contorno->y = 0;
	this->contorno->w = this->getAncho();
	this->contorno->h = this->getAlto();

	return this->contorno;
}

void ElementoGrafico::dibujar(SDL_Surface* superficie){
	if (superficie != NULL) {
		this->dibujarSobreSup(superficie);

	} else {
		this->dibujarSobreSup(this->superficie);
	}
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