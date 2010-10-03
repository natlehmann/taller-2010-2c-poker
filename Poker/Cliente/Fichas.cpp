#include "Fichas.h"
#include "RecursosAplicacion.h"

Fichas::Fichas(string cantidad) {
	this->imagen = NULL;
	this->cantidad = cantidad;
	this->etiqueta = NULL;
}

Fichas::~Fichas(void) {
	if (this->imagen != NULL) {
		delete(this->imagen);
	}
	if (this->etiqueta != NULL) {
		delete(this->etiqueta);
	}
}

void Fichas::dibujarSobreSup(SDL_Surface* superficie){

	if (this->imagen == NULL) {
		this->imagen = new Imagen(
			RecursosAplicacion::getClienteConfigProperties()->get(
			"cliente.tema.default.imagen.fichas"));
	}

	int altoEtiqueta = (int)(this->getAlto() * FICHAS_ALTO_ETIQUETA);

	this->imagen->setPosX(this->getPosX());
	this->imagen->setPosY(this->getPosY());
	this->imagen->setAncho(this->getAncho());
	this->imagen->setAlto(this->getAlto() - altoEtiqueta);

	if (this->etiqueta == NULL) {
		this->etiqueta = new Etiqueta();
	}

	this->etiqueta->setPosX(this->getPosX());
	this->etiqueta->setPosY(this->getPosY() + this->getAlto() - altoEtiqueta);
	this->etiqueta->setAncho(this->getAncho());
	this->etiqueta->setAlto(altoEtiqueta);

	this->etiqueta->setMensaje(this->getCantidad());

	this->imagen->dibujar(superficie);
	this->etiqueta->dibujar(superficie);

}

string Fichas::getCantidad() {
	return this->cantidad;
}

void Fichas::setCantidad(string cantidad) {
	this->cantidad = cantidad;
}
