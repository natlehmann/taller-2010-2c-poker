#include "Imagen.h"
#include "UIException.h"

Imagen::Imagen(string nombre) {
	// TODO: VER SI ACA VERIFICAMOS QUE LA IMAGEN EXISTA O SE LA PEDIMOS AL SERVIDOR
	this->nombre = nombre;

}

Imagen::~Imagen(void)
{
}

void Imagen::dibujarSobreSup(SDL_Surface* superficie, SDL_Rect* posicionEnSup){

	// TODO: ATENCION!!!! REEMPLAZAR ESTO POR EL RESIZING PROPIO
	SDL_Surface* imagenInicial = SDL_LoadBMP(this->nombre.c_str()); 

	// ESTO TAMBIEN SE VA !!!!
	if(imagenInicial != NULL) {
		this->superficie = SDL_DisplayFormat(imagenInicial);

		SDL_BlitSurface(this->getSuperficie(), this->getContornoRect(), 
				superficie, posicionEnSup); 
		//Free the old image 
		SDL_FreeSurface(imagenInicial); 
		SDL_FreeSurface(this->getSuperficie()); 
		this->superficie = NULL;
	
	} else {
		throw UIException("No se pudo cargar la imagen " + this->nombre, "E");
	}
}

void Imagen::dibujarSobreSup(SDL_Surface* superficie) {
	this->dibujarSobreSup(superficie, this->getOffsetRect());
}


string Imagen::getNombre(){
	return this->nombre;
}

void Imagen::setTamanio(long tamanio){
	this->tamanio = tamanio;
}

long Imagen::getTamanio() {
	return this->tamanio;
}
