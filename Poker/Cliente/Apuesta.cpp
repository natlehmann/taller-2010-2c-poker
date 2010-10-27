#include "Apuesta.h"
#include "RecursosCliente.h"

Apuesta::Apuesta(string cantidad) {
	this->imagen = NULL;
	this->cantidad = cantidad;
	this->etiqueta = NULL;
}

Apuesta::~Apuesta(void) {
	if (this->imagen != NULL) {
		delete(this->imagen);
	}
	if (this->etiqueta != NULL) {
		delete(this->etiqueta);
	}
}

void Apuesta::dibujarSobreSup(SDL_Surface* superficie){

	if (this->imagen == NULL) {
		this->imagen = new Imagen(
			RecursosCliente::getConfig()->get(
			"cliente.tema.default.imagen.apuesta"));
	}

	int altoEtiqueta = (int)(this->getAlto() * APUESTA_ALTO_ETIQUETA);

	this->imagen->setPosX(this->getPosX());
	this->imagen->setPosY(this->getPosY());
	this->imagen->setAncho(this->getAncho());
	this->imagen->setAlto(this->getAlto() - altoEtiqueta);

	if (this->etiqueta == NULL) {
		this->etiqueta = new Etiqueta();
		this->etiqueta->setVentana(this->getVentana());
		this->etiqueta->setAlineacionHorizontal(ALINEACION_HORIZ_CENTRO);
		this->etiqueta->setFondo(NULL);
	}

	this->etiqueta->setPosX(this->getPosX());
	this->etiqueta->setPosY(this->getPosY() + this->getAlto() - altoEtiqueta);
	this->etiqueta->setAncho(this->getAncho());
	this->etiqueta->setAlto(altoEtiqueta);

	this->etiqueta->setMensaje(this->getCantidad());

	this->imagen->dibujar(superficie);
	this->etiqueta->dibujar(superficie);

}

string Apuesta::getCantidad() {
	return this->cantidad;
}

void Apuesta::setCantidad(string cantidad) {
	this->cantidad = cantidad;
	this->hayCambios = true;
}
