#ifndef _SERVICIOSGRAFICOS_H__
#define _SERVICIOSGRAFICOS_H__

#include "SDL.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

#include "Color.h"

#define CELDAS_HORIZ	5
#define CELDAS_VERT		3

class ServiciosGraficos {
private:
	static const SDL_VideoInfo* videoInfo;

	static int bordeSuperior;
	static int bordeInferior;
	static int bordeIzquierdo;
	static int bordeDerecho;

	static void lock(SDL_Surface* superficie);
	static void unlock(SDL_Surface* superficie);

	/**
	* Estos metodos requieren que previamente se bloquee la pantalla
	*/
	static void putPixel(SDL_Surface* superficie, int x, int y, Uint32 pixel);
	static Uint32 getPixel(SDL_Surface* surface, int x, int y);
	static int findFirstPorLinea(SDL_Surface* superficie, 
		int xDesde, int xHasta, int linea, Uint32 pixel);
	static int findLastPorLinea(SDL_Surface* superficie, 
		int xDesde, int xHasta, int linea, Uint32 pixel);

	

public:
	ServiciosGraficos(void);
	virtual ~ServiciosGraficos(void);

	/**
	* El parametro offset indica el punto superior izquierdo desde el cual se comienza a dibujar
	* el circulo. Este parametro debe tener seteados los atributos w y h, ya que estos
	* se evaluaran para fijar el tamaño de la elipse.
	*/
	static void dibujarElipse(SDL_Surface* superficie, 
		SDL_Rect* offset, Color* color);

	static const SDL_VideoInfo* getVideoInfo();

	static SDL_Surface* crearSuperficie(int ancho, int alto);

	/**
	* Copia origen a destino en la posicion indicada por offsetDestino,
	* para todos los pixels que sean distintos de colorMascara.
	*/
	static void merge(SDL_Surface* origen, SDL_Surface* destino, 
		SDL_Rect* offsetDestino, Uint32 colorMascara);

	/**
	* Copia origen a la superficie destino, en todos los pixels que encuentren
	* contenidos entre dos pixels de colorFigura.
	* Origen y destino deben ser del mismo tamaño.
	*/
	static void copiarDentro(SDL_Surface* origen, 
		SDL_Surface* destino, Color* colorFigura);

	static int getTamanioCeldaHoriz();
	static int getTamanioCeldaVert();

	static int getAnchoVentana();
	static int getAltoVentana();

	static int getBordeSuperior();
	static int getBordeInferior();
	static int getBordeDerecho();
	static int getBordeIzquierdo();

	static SDL_Surface* resizeSuperficie(SDL_Surface* superficie, int ancho, int alto);
};

#endif //_SERVICIOSGRAFICOS_H__
