#include "Carta.h"
#include "ServiciosGraficos.h"
#include "RecursosCliente.h"
#include "MensajesUtil.h"
#include "UIException.h"
#include "Ventana.h"
#include <typeinfo.h>



Carta::Carta(void)
{
	this->imagen = NULL;
	this->numero = "";
	this->palo = "";
	this->posicion = 0;
}

Carta::~Carta(void)
{
	if (this->imagen != NULL) {
		delete(this->imagen);
	}
}

void Carta::dibujarSobreSup(SDL_Surface* superficie){

	if (this->imagen != NULL) {
		delete (this->imagen);
		this->imagen = NULL;
	}

	string subDir = RecursosCliente::getConfig()->get(
		"cliente.configuracion.imagenes.cartas.dir");

	string nombreImagen;

	if (!this->isMostrandoReverso()) {
		nombreImagen = subDir + this->getNumero() + this->getIdPalo() + ".bmp";

	} else {
		nombreImagen = subDir + "reverso.bmp";
	}

	this->imagen = new Imagen(nombreImagen);
	this->imagen->setPosX(this->getPosX());
	this->imagen->setPosY(this->getPosY());
	this->imagen->setAlto(this->getAlto());
	this->imagen->setAncho(this->getAncho());

	this->imagen->dibujar(superficie);

}

string Carta::getIdPalo(){
	if (MensajesUtil::esVacio(this->getPalo())) {
		throw UIException("El palo de la carta no fue seteado.","E");
	}

	if (MensajesUtil::sonIguales(this->getPalo(), "Corazon")) {
		return "c";
	}

	if (MensajesUtil::sonIguales(this->getPalo(), "Pica")) {
		return "p";
	}

	if (MensajesUtil::sonIguales(this->getPalo(), "Trebol")) {
		return "t";
	}

	if (MensajesUtil::sonIguales(this->getPalo(), "Diamante")) {
		return "d";
	}

	throw UIException("La carta tiene un palo invalido.","E");
}




string Carta::getNumero() 
{
	return this->numero;
}

void Carta::setNumero(string numero) 
{
	if (!MensajesUtil::sonIguales(this->getNumero(), numero)) {
		this->numero = numero;
		this->hayCambios = true;
	}
}

string Carta::getPalo() 
{
	return this->palo;
}

void Carta::setPalo(string palo)
{
	if (!MensajesUtil::sonIguales(this->getPalo(), palo)) {
		this->palo = palo;
		this->hayCambios = true;
	}
}

bool Carta::isMostrandoReverso(){
	return this->mostrandoReverso;
}
void Carta::setMostrandoReverso(bool mostrandoReverso){
	if (this->mostrandoReverso != mostrandoReverso) {
		this->mostrandoReverso = mostrandoReverso;
		this->hayCambios = true;
	}
}

bool Carta::equals(ElementoGrafico* otro){

	bool iguales = false;
	if (otro != NULL && MensajesUtil::sonIguales(typeid(*otro).name(), "class Carta")) {
		Carta* otraCarta = (Carta*)otro;

		if (MensajesUtil::sonIguales(this->getPalo(), otraCarta->getPalo()) 
			&& MensajesUtil::sonIguales(this->getNumero(), otraCarta->getNumero()) 
			&& this->getVisible() == otraCarta->getVisible() 
			&& MensajesUtil::sonIguales(this->getId(), otraCarta->getId()) ){
				iguales = true;
		}
	}

	return iguales;
}