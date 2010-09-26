#include "Imagen.h"
#include "UIException.h"

Imagen::Imagen(void)
{
}

Imagen::~Imagen(void)
{
}

void Imagen::dibujar(){

	// TODO: ATENCION!!!! REEMPLAZAR ESTO POR EL RESIZING PROPIO
	SDL_Surface* imagenInicial = SDL_LoadBMP(this->nombre.c_str()); 

	// ESTO TAMBIEN SE VA !!!!
	if(imagenInicial != NULL) {
		this->superficie = SDL_DisplayFormat(imagenInicial); 
		//Free the old image 
		SDL_FreeSurface(imagenInicial); 
	
	} else {
		throw UIException("No se pudo cargar la imagen " + this->nombre, "E");
	}

	// TODO: CALCULAR DONDE DEBERÍA DIBUJARSE

}

void Imagen::setNombre(string nombre){

	// TODO: VER SI ACA VERIFICAMOS QUE LA IMAGEN EXISTA O SE LA PEDIMOS AL SERVIDOR
	this->nombre = nombre;
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
