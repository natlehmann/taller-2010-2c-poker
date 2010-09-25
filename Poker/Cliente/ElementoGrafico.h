#ifndef _ELEMENTOGRAFICO_H__
#define _ELEMENTOGRAFICO_H__

#include "SDL.h" 
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

using namespace std;

class ElementoGrafico {
private:
	int posX;
	int posY;
	int ancho;
	int alto;

public:
	ElementoGrafico(void);
	virtual ~ElementoGrafico(void);

	virtual void dibujar() = 0;

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
