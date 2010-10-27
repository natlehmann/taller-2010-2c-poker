#include "CartaModelo.h"
#include "MensajesUtil.h"
#include "UtilTiposDatos.h"

CartaModelo::CartaModelo(string numero, string palo)
{
	this->numero = numero;
	this->palo = palo;
	this->visible = false;
	this->posicion = 0;
}

CartaModelo::~CartaModelo(void)
{
}

string CartaModelo::getId(){
	return this->getIdPalo() + this->getNumero();
}

string CartaModelo::getIdPalo(){
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
	return "";
}

int CartaModelo::getValorNumerico()
{
	if (MensajesUtil::sonIguales(this->getNumero(), "a")) {
		return 14;
	}
	if (MensajesUtil::sonIguales(this->getNumero(), "k")) {
		return 13;
	}
	if (MensajesUtil::sonIguales(this->getNumero(), "q")) {
		return 12;
	}
	if (MensajesUtil::sonIguales(this->getNumero(), "j")) {
		return 11;
	}
	int valorNumerico = UtilTiposDatos::stringAEntero(this->getNumero());
	if (valorNumerico > 1 && valorNumerico < 11) {
		return valorNumerico;
	}
	return 0;
}

string CartaModelo::getNumero() 
{
	return this->numero;
}

void CartaModelo::setNumero(string numero) 
{
	this->numero = numero;
}

string CartaModelo::getPalo() 
{
	return this->palo;
}

void CartaModelo::setPalo(string palo)
{
	this->palo = palo;
}

bool CartaModelo::getVisible() 
{
	return this->visible;
}

void CartaModelo::setVisible(bool visible) 
{
	this->visible = visible;
}

int CartaModelo::getPosicion()
{
	return this->posicion;
}

void CartaModelo::setPosicion(int posicion) 
{
	this->posicion = posicion;
}
