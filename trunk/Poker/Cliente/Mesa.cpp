#include "Mesa.h"
#include "ServiciosGraficos.h"
#include "MensajesUtil.h"

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

	if (this->imagen == NULL || !MensajesUtil::sonIguales(this->imagen->getNombreSinPath(), nombreImagen)) {

		if (this->imagen != NULL) {
			delete (this->imagen);
		}

		this->imagen = new Imagen(nombreImagen);
		this->imagen->setAlto(this->getAlto());
		this->imagen->setAncho(this->getAncho());
		this->hayCambios = true;
	}
}

Imagen* Mesa::getFondo(){
	return this->imagen;
}