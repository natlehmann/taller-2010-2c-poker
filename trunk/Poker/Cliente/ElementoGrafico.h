#ifndef _ELEMENTOGRAFICO_H__
#define _ELEMENTOGRAFICO_H__

#include "SDL.h" 
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

using namespace std;

class ElementoGrafico {
protected:
	int posX;
	int posY;
	int ancho;
	int alto;

	SDL_Surface* superficie;

public:
	ElementoGrafico(void);
	virtual ~ElementoGrafico(void);

	virtual void dibujar() = 0;

	SDL_Surface* getSuperficie();
	SDL_Rect* getOffsetRect();

	int getPosX();
	void setPosX(int posX);
	int getPosY();
	void setPosY(int posY);
	int getAncho();
	void setAncho(int ancho);
	int getAlto();
	void setAlto(int alto);
};

#endif //_ELEMENTOGRAFICO_H__
