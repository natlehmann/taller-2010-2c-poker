#include "Color.h"
#include "MensajesUtil.h"
#include "UtilTiposDatos.h"
#include "UIException.h"
#include <list>

Color::Color(Uint8 red, Uint8 green, Uint8 blue) {
	this->red = red;
	this->green = green;
	this->blue = blue;
}

Color::Color(string redgreenblue){
	list<string> colores = MensajesUtil::split(redgreenblue);
	if (colores.size() != 3) {
		throw UIException("Argumentos invalidos al construir un color.","E");
	}
	list<string>::iterator it = colores.begin();
	this->red = UtilTiposDatos::getEntero(*it);
	it++;
	this->green = UtilTiposDatos::getEntero(*it);
	it++;
	this->blue = UtilTiposDatos::getEntero(*it);
}

Color::~Color(void)
{
}

Uint32 Color::toUint32(SDL_Surface* superficie){
	return SDL_MapRGB(superficie->format, this->red, this->green, this->blue);
}

SDL_Color Color::toSDL_Color(){
	SDL_Color color;

	color.b = this->blue;
	color.r = this->red;
	color.g = this->green;

	return color;
}

void Color::setRed(Uint8 red){
	this->red = red;
}

void Color::setGreen(Uint8 green){
	this->green = green;
}

void Color::setBlue(Uint8 blue){
	this->blue = blue;
}

Uint8 Color::getRed(){
	return this->red;
}

Uint8 Color::getGreen(){
	return this->green;
}

Uint8 Color::getBlue(){
	return this->blue;
}
