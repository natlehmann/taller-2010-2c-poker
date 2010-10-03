#include "Etiqueta.h"
#include "RecursosAplicacion.h"

Etiqueta::Etiqueta(void) {
	this->fondo = new Color(
		RecursosAplicacion::getClienteConfigProperties()->get(
		"cliente.tema.default.etiquetas.fondo"));
}

Etiqueta::Etiqueta(string mensaje){
	this->fondo = new Color(
		RecursosAplicacion::getClienteConfigProperties()->get(
		"cliente.tema.default.etiquetas.fondo"));
	this->mensaje = mensaje;
}

Etiqueta::~Etiqueta(void) {
	if (this->fondo != NULL) {
		delete(this->fondo);
	}
}

void Etiqueta::dibujarSobreSup(SDL_Surface* superficie){ 

	SDL_Rect* offset = this->getOffsetRect();
	offset->w = this->getAncho();
	offset->h = this->getAlto();

	SDL_FillRect(superficie, offset, this->fondo->toUint32(superficie));

	//TODO: ACA VIENE LA PARTE DE IMPRIMIR EL TEXTO
}

void Etiqueta::setMensaje(string mensaje) {
	this->mensaje = mensaje;
}

string Etiqueta::getMensaje() {
	return this->mensaje;
}

void Etiqueta::setFondo(Color* color){
	this->fondo = color;
}

Color* Etiqueta::getFondo() {
	return this->fondo;
}
