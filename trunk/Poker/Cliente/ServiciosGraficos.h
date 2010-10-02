#ifndef _SERVICIOSGRAFICOS_H__
#define _SERVICIOSGRAFICOS_H__

#include "SDL.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

#define CELDAS_HORIZ	6
#define CELDAS_VERT		3

class ServiciosGraficos {
private:
	static const SDL_VideoInfo* videoInfo;

	static int bordeSuperior;
	static int bordeInferior;
	static int bordeIzquierdo;
	static int bordeDerecho;

	/**
	* Este metodo requiere que previamente se bloquee la pantalla
	*/
	static void putPixel(SDL_Surface* superficie, int x, int y, Uint32 pixel);

public:
	ServiciosGraficos(void);
	virtual ~ServiciosGraficos(void);

	/**
	* El parametro offset indica el punto superior izquierdo desde el cual se comienza a dibujar
	* el circulo. Este parametro debe tener seteados los atributos w y h, ya que estos
	* se evaluaran para fijar el tamaño de la elipse.
	*/
	static void dibujarElipse(SDL_Surface* superficie, 
		SDL_Rect* offset, Uint8 red, Uint8 green, Uint8 blue);

	static const SDL_VideoInfo* getVideoInfo();

	static SDL_Surface* crearSuperficie(int ancho, int alto);

	static int getTamanioCeldaHoriz();
	static int getTamanioCeldaVert();

	static int getAnchoVentana();
	static int getAltoVentana();

	static int getBordeSuperior();
	static int getBordeInferior();
	static int getBordeDerecho();
	static int getBordeIzquierdo();
};

#endif //_SERVICIOSGRAFICOS_H__
