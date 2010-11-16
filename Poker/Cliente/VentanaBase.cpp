#include "VentanaBase.h"

VentanaBase::VentanaBase(void) {
	this->imagenFondo = NULL;
}

VentanaBase::~VentanaBase(void)
{
}
SDL_Surface* VentanaBase::getSuperficie() {
	return this->pantalla;
}
SDL_Rect* VentanaBase::getOffsetRect() {
	this->offset->x = this->getPosX();
	this->offset->y = this->getPosY();

	return this->offset;
}

SDL_Rect* VentanaBase::getContornoRect() {
	this->contorno->x = 0;
	this->contorno->y = 0;
	this->contorno->w = this->getAncho();
	this->contorno->h = this->getAlto();

	return this->contorno;
}

int VentanaBase::getPosX() {
	return this->posX;
}
void VentanaBase::setPosX(int posX) {
	this->posX = posX;
	this->hayCambios = true;
}
int VentanaBase::getPosY() {
	return this->posY;
}
void VentanaBase::setPosY(int posY) {
	this->posY = posY;
	this->hayCambios = true;
}
int VentanaBase::getAncho() {
	return this->ancho;
}
void VentanaBase::setAncho(int ancho) {
	this->ancho = ancho;
	this->hayCambios = true;
}
int VentanaBase::getAlto() {
	return this->alto;
}
void VentanaBase::setAlto(int alto) {
	this->alto = alto;
	this->hayCambios = true;
}

string VentanaBase::getId(){
	return this->id;
}

void VentanaBase::setId(string id){
	this->id = id;
	this->hayCambios = true;
}

SDL_Rect* VentanaBase::getContornoConOffset() {
	this->contornoConOffset->x = this->getPosX();
	this->contornoConOffset->y = this->getPosY();
	this->contornoConOffset->w = this->getAncho();
	this->contornoConOffset->h = this->getAlto();

	return this->contornoConOffset;
}

