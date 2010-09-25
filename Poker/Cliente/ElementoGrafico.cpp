#include "ElementoGrafico.h"

ElementoGrafico::ElementoGrafico(void)
{
}

ElementoGrafico::~ElementoGrafico(void)
{
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