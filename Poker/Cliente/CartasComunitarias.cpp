#include "CartasComunitarias.h"
#include "MensajesUtil.h"
#include "Ventana.h"

CartasComunitarias::CartasComunitarias(void)
{
	int altoCartas = (int)(ServiciosGraficos::getTamanioCeldaVert() * ALTO_PROPORCIONAL_CARTAS);

	this->setAncho(ServiciosGraficos::getTamanioCeldaHoriz() 
		+ (int)(ServiciosGraficos::getTamanioCeldaHoriz() * EXCEDENTE_HORIZ_PROPORCIONAL * 2));
	this->setAlto(altoCartas);
	this->posX = ServiciosGraficos::getBordeIzquierdo() + ServiciosGraficos::getTamanioCeldaHoriz() * 2
		- (int)(ServiciosGraficos::getTamanioCeldaHoriz() * EXCEDENTE_HORIZ_PROPORCIONAL);
	this->posY = ServiciosGraficos::getTamanioCeldaVert() + ServiciosGraficos::getBordeSuperior()
		+ (int)(ServiciosGraficos::getTamanioCeldaVert() * SEPARACION_CON_BORDE_SUP);

	this->carta1 = NULL;
	this->carta2 = NULL;
	this->carta3 = NULL;
	this->carta4 = NULL;
	this->carta5 = NULL;
}

CartasComunitarias::~CartasComunitarias(void)
{
	if (this->carta1 != NULL) {
		delete(this->carta1);
	}
	if (this->carta2 != NULL) {
		delete(this->carta2);
	}
	if (this->carta3 != NULL) {
		delete(this->carta3);
	}
	if (this->carta4 != NULL) {
		delete(this->carta4);
	}
	if (this->carta5 != NULL) {
		delete(this->carta5);
	}
}

void CartasComunitarias::dibujarSobreSup(SDL_Surface* superficie)
{
	this->setearPosicionCartas();
	if (this->carta1 != NULL){
		if (this->carta1->getVisible()) {
			this->carta1->dibujar(superficie);
		} else {
			this->getVentana()->borrarElemento(this->carta1);
		}
	}

	if (this->carta2 != NULL){
		if (this->carta2->getVisible()) {
			this->carta2->dibujar(superficie);
		} else {
			this->getVentana()->borrarElemento(this->carta2);
		}
	}

	if (this->carta3 != NULL){
		if (this->carta3->getVisible()) {
			this->carta3->dibujar(superficie);
		} else {
			this->getVentana()->borrarElemento(this->carta3);
		}
	}

	if (this->carta4 != NULL){
		if (this->carta4->getVisible()) {
			this->carta4->dibujar(superficie);
		} else {
			this->getVentana()->borrarElemento(this->carta4);
		}
	}

	if (this->carta5 != NULL){
		if (this->carta5->getVisible()) {
			this->carta5->dibujar(superficie);
		} else {
			this->getVentana()->borrarElemento(this->carta5);
		}
	}
}

/**
* Solo setea la carta si no fue seteada anteriormente.
*/
void CartasComunitarias::setCarta(Carta* carta)
{
	if (carta)
	{
		switch(carta->getPosicion())
		{
			case 1:	
				if (this->carta1 == NULL) {
					this->carta1 = carta;
				}
				break;

			case 2:	
				if (this->carta2 == NULL) {
					this->carta2 = carta;
				}
				break;
			
			case 3:	
				if (this->carta3 == NULL) {
					this->carta3 = carta;
				}
				break;
			
			case 4:	
				if (this->carta4 == NULL) {
					this->carta4 = carta;
				}
				break;
			
			case 5:	
				if (this->carta5 == NULL) {
					this->carta5 = carta;
				}
				break;

			default: throw UIException("La posicion de la carta comunitaria es invalida.","V");
		}; 

		this->hayCambios = this->hayCambios || carta->getHayCambios();
	}
	else
	{
		throw UIException("No se pudo cargar una de las cartas comunitarias","E");
	}
}

void CartasComunitarias::setearPosicionCartas()
{
	int anchoCarta = (int)((this->getAncho() - SEPARACION_ENTRE_CARTAS_COM * 4) / 5);
	if (this->carta1 != NULL){
		this->carta1->setPosX(this->getPosX());
		this->carta1->setPosY(this->getPosY());
		this->carta1->setAncho(anchoCarta);
		this->carta1->setAlto(this->alto);
	}
	if (this->carta2 != NULL){
		this->carta2->setPosX(this->getPosX() + anchoCarta + SEPARACION_ENTRE_CARTAS_COM);
		this->carta2->setPosY(this->getPosY());
		this->carta2->setAncho(anchoCarta);
		this->carta2->setAlto(this->alto);
	}
	if (this->carta3 != NULL){
		this->carta3->setPosX(this->getPosX() + anchoCarta*2 + SEPARACION_ENTRE_CARTAS_COM*2);
		this->carta3->setPosY(this->getPosY());
		this->carta3->setAncho(anchoCarta);
		this->carta3->setAlto(this->alto);
	}
	if (this->carta4 != NULL){
		this->carta4->setPosX(this->getPosX() + anchoCarta*3 + SEPARACION_ENTRE_CARTAS_COM*3);
		this->carta4->setPosY(this->getPosY());
		this->carta4->setAncho(anchoCarta);
		this->carta4->setAlto(this->alto);
	}
	if (this->carta5 != NULL){
		this->carta5->setPosX(this->getPosX() + anchoCarta*4 + SEPARACION_ENTRE_CARTAS_COM*4);
		this->carta5->setPosY(this->getPosY());
		this->carta5->setAlto(this->alto);
		this->carta5->setAncho(anchoCarta);
	}
}

ElementoGrafico* CartasComunitarias::getElementoPorId(string id){
	if (this->carta1 != NULL && MensajesUtil::sonIguales(this->carta1->getId(), id)){
		return this->carta1;
	}
	if (this->carta2 != NULL && MensajesUtil::sonIguales(this->carta2->getId(), id)){
		return this->carta2;
	}
	if (this->carta3 != NULL && MensajesUtil::sonIguales(this->carta3->getId(), id)){
		return this->carta3;
	}
	if (this->carta4 != NULL && MensajesUtil::sonIguales(this->carta4->getId(), id)){
		return this->carta4;
	}
	if (this->carta5 != NULL && MensajesUtil::sonIguales(this->carta5->getId(), id)){
		return this->carta5;
	}

	return NULL;
}