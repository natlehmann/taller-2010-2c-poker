#include "Mesa.h"

Mesa::Mesa(void) {
	this->imagen = NULL;
}

Mesa::~Mesa(void) {
	if (this->imagen != NULL) {
		delete(this->imagen);
	}
}

void Mesa::dibujar(){
	this->imagen->dibujar();
}

void Mesa::setFondo(string nombreImagen){
	if (this->imagen != NULL) {
		delete (this->imagen);
	}

	// TODO: VER SI PRIMERO TENEMOS QUE CALCULAR EL RESIZING DE LA IMAGEN
	this->imagen = new Imagen(nombreImagen);
	this->imagen->setAlto(this->getAlto());
	this->imagen->setAncho(this->getAncho());
}

SDL_Surface* Mesa::getSuperficie() {
	if (this->imagen != NULL) {
		return this->imagen->getSuperficie();
	} else {
		return this->superficie;
	}
}