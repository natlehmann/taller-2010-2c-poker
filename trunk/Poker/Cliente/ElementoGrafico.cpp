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
	this->contornoConOffset = new SDL_Rect();
	this->hayCambios = true;
	this->id = "";
	this->posicion = -1;
	this->ventana = NULL;
	this->visible = true;
}

ElementoGrafico::~ElementoGrafico(void){
	if (this->superficie != NULL) {
		SDL_FreeSurface(this->superficie);
		this->superficie = NULL;
	}
	delete (this->offset);
	delete (this->contorno);
	delete (this->contornoConOffset);
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

SDL_Rect* ElementoGrafico::getContornoConOffset() {
	this->contornoConOffset->x = this->getPosX();
	this->contornoConOffset->y = this->getPosY();
	this->contornoConOffset->w = this->getAncho();
	this->contornoConOffset->h = this->getAlto();

	return this->contornoConOffset;
}

void ElementoGrafico::dibujar(SDL_Surface* superficie){

	if (this->hayCambios) {

		if (this->visible) {

			if (superficie != NULL) {
				this->dibujarSobreSup(superficie);

			} else {
				this->dibujarSobreSup(this->superficie);
			}

		} else {
			this->getVentana()->borrarElemento(this);
		}

		this->hayCambios = false;
	}
}


void ElementoGrafico::borrar(){
	this->setVisible(false);
}


bool ElementoGrafico::hayInterseccion(ElementoGrafico* otro){
	bool hayInterseccion = false;

	SDL_Rect* miPos = this->getContornoConOffset();
	SDL_Rect* otraPos = otro->getContornoConOffset();

	if ( ( estaEntre(miPos->x, otraPos->x, otraPos->x + otraPos->w) 
			|| estaEntre(miPos->x + miPos->w, otraPos->x, otraPos->x + otraPos->w) )
		&& ( estaEntre(miPos->y, otraPos->y, otraPos->y + otraPos->h) 
			|| estaEntre(miPos->y + miPos->h, otraPos->y, otraPos->y + otraPos->h) )
		) {
			hayInterseccion = true;
		}

	return hayInterseccion;
}

bool ElementoGrafico::estaEntre(int numero, int limiteUno, int limiteDos) {
	return (limiteUno != limiteDos) && (numero >= limiteUno && numero <= limiteDos);
}


bool ElementoGrafico::getVisible() {
	return this->visible;
}

void ElementoGrafico::setVisible(bool visible) {
	if (this->visible != visible) {
		this->visible = visible;
		this->hayCambios = true;
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