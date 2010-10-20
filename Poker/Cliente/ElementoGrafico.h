#ifndef _ELEMENTOGRAFICO_H__
#define _ELEMENTOGRAFICO_H__

#include "SDL.h" 
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

using namespace std;

class Ventana;

class ElementoGrafico {
protected:
	int posX;
	int posY;
	int ancho;
	int alto;
	bool hayCambios;

	string id;
	int posicion;

	SDL_Surface* superficie;
	SDL_Rect* offset;
	SDL_Rect* contorno;

	Ventana* ventana;

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

	void setHayCambios(bool hayCambios);

	int getPosX();
	virtual void setPosX(int posX);
	int getPosY();
	virtual void setPosY(int posY);
	virtual int getAncho();
	virtual void setAncho(int ancho);
	virtual int getAlto();
	virtual void setAlto(int alto);

	string getId();
	void setId(string id);

	int getPosicion();
	void setPosicion(int posicion);

	Ventana* getVentana();
	void setVentana(Ventana* ventana);

	/**
	* Devuelve true si este elemento grafico tiene el mismo id que "otro".
	*/
	virtual bool equals(ElementoGrafico* otro);
};

#endif //_ELEMENTOGRAFICO_H__
