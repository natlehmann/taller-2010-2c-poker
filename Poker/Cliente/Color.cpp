#include "Color.h"

Color::Color(Uint8 red, Uint8 green, Uint8 blue) {
	this->red = red;
	this->green = green;
	this->blue = blue;
}

Color::~Color(void)
{
}

Uint32 Color::toUint32(SDL_Surface* superficie){
	return SDL_MapRGB(superficie->format, this->red, this->green, this->blue);
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
