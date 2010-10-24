#include "Mensaje.h"
#include "MensajesUtil.h"
#include "Color.h"
#include "Ventana.h"

Mensaje::Mensaje(string mensaje) {
	this->visible = false;
	this->etiqueta = new Etiqueta(mensaje);
	//this->etiqueta->setVentana(this->getVentana());
	this->etiqueta->setAlineacionHorizontal(ALINEACION_HORIZ_CENTRO);
	this->etiqueta->setAlineacionVertical(ALINEACION_VERT_CENTRO);

	this->etiqueta->setFondo(new Color(RecursosAplicacion::getClienteConfigProperties()->get(
		"cliente.tema.default.mensaje.fondo")));
	this->etiqueta->setBorde(new Color(RecursosAplicacion::getClienteConfigProperties()->get(
		"cliente.tema.default.mensaje.borde")));

	this->etiqueta->setPosX(ServiciosGraficos::getBordeDerecho() 
		+ (int)(ServiciosGraficos::getTamanioCeldaHoriz() * 1.5));
	this->etiqueta->setPosY(ServiciosGraficos::getBordeSuperior() + ServiciosGraficos::getTamanioCeldaVert());
	this->etiqueta->setAncho(ServiciosGraficos::getTamanioCeldaHoriz() * 2);
	this->etiqueta->setAlto((int)(ServiciosGraficos::getTamanioCeldaVert() / 2));
}

Mensaje::~Mensaje(void) {
	if (this->etiqueta != NULL) {
		delete(this->etiqueta);
	}
}

void Mensaje::dibujarSobreSup(SDL_Surface* superficie){
	if (this->isVisible()) {
		this->etiqueta->dibujar(superficie);
	} 
}

string Mensaje::getTexto(){
	return this->etiqueta->getMensaje();
}

void Mensaje::setTexto(string texto){
	this->etiqueta->setMensaje(texto);
}

bool Mensaje::isVisible(){
	return this->visible;
}

void Mensaje::setVisible(bool visible){
	if (this->visible != visible) {
		this->visible = visible;
		this->hayCambios = true;

		if (!visible) {
			this->getVentana()->forzarRefresh();
		}
	}
}
