#include "Mensaje.h"
#include "MensajesUtil.h"
#include "Color.h"
#include "Ventana.h"

Mensaje::Mensaje(string mensaje) {

	this->etiqueta = new Etiqueta(mensaje);
	this->etiqueta->setAlineacionHorizontal(ALINEACION_HORIZ_CENTRO);
	this->etiqueta->setAlineacionVertical(ALINEACION_VERT_CENTRO);

	this->etiqueta->setFondo(new Color(RecursosAplicacion::getClienteConfigProperties()->get(
		"cliente.tema.default.mensaje.fondo")));
	this->etiqueta->setBorde(new Color(RecursosAplicacion::getClienteConfigProperties()->get(
		"cliente.tema.default.mensaje.borde")));

	this->setPosX(ServiciosGraficos::getBordeDerecho() 
		+ (int)(ServiciosGraficos::getTamanioCeldaHoriz() * 1.5));
	this->setPosY(ServiciosGraficos::getBordeSuperior() + ServiciosGraficos::getTamanioCeldaVert());
	this->setAncho(ServiciosGraficos::getTamanioCeldaHoriz() * 2);
	this->setAlto((int)(ServiciosGraficos::getTamanioCeldaVert() / 2));

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
	this->etiqueta->setMensaje(texto);
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

