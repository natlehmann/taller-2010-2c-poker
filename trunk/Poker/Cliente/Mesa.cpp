#include "Mesa.h"
#include "ServiciosGraficos.h"

Mesa::Mesa(void) {
	this->imagen = NULL;
}

Mesa::~Mesa(void) {
	if (this->imagen != NULL) {
		delete(this->imagen);
	}
}

void Mesa::dibujarSobreSup(SDL_Surface* superficie){

	this->imagen->dibujar(superficie);
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