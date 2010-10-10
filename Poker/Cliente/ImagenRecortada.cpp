#include "ImagenRecortada.h"
#include "ServiciosGraficos.h"

ImagenRecortada::ImagenRecortada(int ancho, int alto){
	this->setAncho(ancho);
	this->setAlto(alto);
	this->colorMascara = NULL;
	this->hayCambios = false;
}

ImagenRecortada::~ImagenRecortada(void){
	if (this->colorMascara != NULL) {
		delete (this->colorMascara);
	}
	this->superficie = NULL;
}

void ImagenRecortada::setAlto(int alto){
	this->hayCambios = true;
	ElementoGrafico::setAlto(alto);
}

void ImagenRecortada::setAncho(int ancho){
	this->hayCambios = true;
	ElementoGrafico::setAncho(ancho);
}

Color* ImagenRecortada::getColorMascara() {
	if (this->colorMascara == NULL) {
		this->colorMascara = new Color(0,255,0);
	}

	return this->colorMascara;
}

void ImagenRecortada::setColorMascara(Uint8 red, Uint8 green, Uint8 blue){
	this->getColorMascara()->setRed(red);
	this->getColorMascara()->setGreen(green);
	this->getColorMascara()->setBlue(blue);
	this->hayCambios = true;
}

void ImagenRecortada::setColorMascara(Color colorMascara){
	this->getColorMascara()->setRed(colorMascara.getRed());
	this->getColorMascara()->setGreen(colorMascara.getGreen());
	this->getColorMascara()->setBlue(colorMascara.getBlue());
	this->hayCambios = true;
}


SDL_Surface* ImagenRecortada::getSuperficie(){

	if (this->superficie != NULL && !this->hayCambios) {
		return this->superficie;

	} else {

		if (this->superficie != NULL) {
			SDL_FreeSurface(this->superficie);
			delete (this->superficie);
		}

		this->superficie = ServiciosGraficos::crearSuperficie(
				this->getAncho(), this->getAlto());

		// se rellena con el color de la mascara
		SDL_FillRect(this->superficie, NULL, 
			this->getColorMascara()->toUint32(this->superficie));

		this->hayCambios = false;
	}

	return this->superficie;
}


void ImagenRecortada::dibujarSobreSup(SDL_Surface* superficie) {

	if (this->superficie != NULL) {

		ServiciosGraficos::merge(this->getSuperficie(), superficie, this->getOffsetRect(), 
			this->getColorMascara()->toUint32(this->getSuperficie()));
	}
}

