#include "Carta.h"
#include "ServiciosGraficos.h"
#include "RecursosAplicacion.h"
#include "MensajesUtil.h"
#include "UIException.h"

Carta::Carta(void)
{
	this->imagen = NULL;
	this->numero = "";
	this->palo = "";
	this->visible = false;
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
	}

	string subDir = RecursosAplicacion::getClienteConfigProperties()->get(
		"cliente.configuracion.imagenes.cartas.dir");

	string nombreImagen;

	if (this->getVisible()) {
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
	this->numero = numero;
}

string Carta::getPalo() 
{
	return this->palo;
}

void Carta::setPalo(string palo)
{
	this->palo = palo;
}

bool Carta::getVisible() 
{
	return this->visible;
}

void Carta::setVisible(bool visible) 
{
	this->visible = visible;
}