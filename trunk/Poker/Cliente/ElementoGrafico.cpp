#include "ElementoGrafico.h"
#include "ServiciosGraficos.h"
#include "UIException.h"
#include "MensajesUtil.h"
#include "Ventana.h"

ElementoGrafico::ElementoGrafico(void) {
	this->superficie = NULL;
	this->posX = 0;
	this->posY = 0;
	this->offset = new SDL_Rect();
	this->contorno = new SDL_Rect();
	this->hayCambios = true;
	this->id = "";
	this->posicion = -1;
	this->ventana = NULL;
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

	if (this->hayCambios) {
		if (superficie != NULL) {
			this->dibujarSobreSup(superficie);

		} else {
			this->dibujarSobreSup(this->superficie);
		}
		this->hayCambios = false;
	}
}


int ElementoGrafico::getPosX() {
	return this->posX;
}
void ElementoGrafico::setPosX(int posX) {
	if (this->getPosX() != posX) {
		this->posX = posX;
		this->hayCambios = true;
	}
}
int ElementoGrafico::getPosY() {
	return this->posY;
}
void ElementoGrafico::setPosY(int posY) {
	if (this->getPosY() != posY) {
		this->posY = posY;
		this->hayCambios = true;
	}
}
int ElementoGrafico::getAncho() {
	return this->ancho;
}
void ElementoGrafico::setAncho(int ancho) {
	if (this->getAncho() != ancho) {
		this->ancho = ancho;
		this->hayCambios = true;
	}
}
int ElementoGrafico::getAlto() {
	return this->alto;
}
void ElementoGrafico::setAlto(int alto) {
	if (this->getAlto() != alto) {
		this->alto = alto;
		this->hayCambios = true;
	}
}

void ElementoGrafico::setHayCambios(bool hayCambios){
	this->hayCambios = hayCambios;
}

bool ElementoGrafico::getHayCambios(){
	return this->hayCambios;
}

string ElementoGrafico::getId(){
	return this->id;
}

void ElementoGrafico::setId(string id){
	if (!MensajesUtil::sonIguales(this->getId(), id)) {
		this->id = id;
		this->hayCambios = true;
	}
}

bool ElementoGrafico::equals(ElementoGrafico* otro){
	return (otro != NULL && MensajesUtil::sonIguales(this->getId(), otro->getId()));
}

int ElementoGrafico::getPosicion() {
	return this->posicion;
}

void ElementoGrafico::setPosicion(int posicion) {
	if (this->getPosicion() != posicion){
		this->posicion = posicion;
		this->hayCambios = true;
	}
}

Ventana* ElementoGrafico::getVentana(){
	return this->ventana;
}

void ElementoGrafico::setVentana(Ventana* ventana){
	this->ventana = ventana;
}