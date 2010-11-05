#include "Mensaje.h"
#include "MensajesUtil.h"
#include "Color.h"
#include "Ventana.h"
#include "RecursosCliente.h"

Mensaje::Mensaje(string mensaje) {

	this->etiqueta = new Etiqueta(mensaje);
	this->etiqueta->setAlineacionHorizontal(ALINEACION_HORIZ_CENTRO);
	this->etiqueta->setAlineacionVertical(ALINEACION_VERT_CENTRO);

	this->etiqueta->setFondo(new Color(RecursosCliente::getConfig()->get(
		"cliente.tema.default.mensaje.fondo")));
	this->etiqueta->setBorde(new Color(RecursosCliente::getConfig()->get(
		"cliente.tema.default.mensaje.borde")));

	this->setPosX(ServiciosGraficos::getBordeDerecho() 
		+ (int)(ServiciosGraficos::getTamanioCeldaHoriz() * 1.5));
	this->setPosY(ServiciosGraficos::getBordeSuperior() + (int)(ServiciosGraficos::getTamanioCeldaVert() * 1.7));
	this->setAncho(ServiciosGraficos::getTamanioCeldaHoriz() * 2);
	this->setAlto((int)(ServiciosGraficos::getTamanioCeldaVert() / 4));

	this->etiqueta->setPosX(this->getPosX());
	this->etiqueta->setPosY(this->getPosY());
	this->etiqueta->setAncho(this->getAncho());
	this->etiqueta->setAlto(this->getAlto());
}

Mensaje::~Mensaje(void) {
	if (this->etiqueta != NULL) {
		delete(this->etiqueta);
	}
}

void Mensaje::dibujarSobreSup(SDL_Surface* superficie){
	this->etiqueta->dibujar(superficie);
}

string Mensaje::getTexto(){
	return this->etiqueta->getMensaje();
}

void Mensaje::setTexto(string texto){
	if (!MensajesUtil::sonIguales(this->etiqueta->getMensaje(), texto)) {
		this->etiqueta->setMensaje(texto);
		this->hayCambios = true;
	}
}


void Mensaje::setVisible(bool visible){
	if (this->visible != visible) {
		this->visible = visible;
		this->hayCambios = true;

		if (!visible) {
			this->getVentana()->borrarElemento(this);
			this->getVentana()->forzarRefresh(this);
			this->hayCambios = false;
		}
	}
}

