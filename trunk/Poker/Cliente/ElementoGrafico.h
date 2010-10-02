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
	SDL_Rect* offset;
	SDL_Rect* contorno;

	virtual void dibujarSobreSup(SDL_Surface* superficie) = 0;

public:
	ElementoGrafico(void);
	virtual ~ElementoGrafico(void);

	/**
	* Plasmar en una superficie el dibujo que representa este elemento.
	* Cada elemento puede definir si dibuja sobre la superficie que recibe
	* por parametro o sobre su propia superficie.
	* El parametro puede ser nulo. En ese caso, se fuerza que el dibujar() se ejecute
	* sobre la propia superficie del elemento.
	*/
	virtual void dibujar(SDL_Surface* superficie);

	virtual SDL_Surface* getSuperficie();

	/**
	* Representa la posicion de la esquina superior izquierda de este elemento grafico
	* en relacion a la superfice total de la ventana.
	* Los atributos h y w de este SDL_Rect no tienen sentido y podrían no estar seteados.
	*/
	virtual SDL_Rect* getOffsetRect();

	/**
	* Representa el recuadro que se forma por el ancho y el alto de este elemento grafico
	*/
	virtual SDL_Rect* getContornoRect();

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
