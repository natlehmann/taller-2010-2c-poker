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

#define ANCHO_PANTALLA_LIMITE	1200
#define ALTO_PANTALLA_LIMITE	768
#define CORRECCION_BORDE_VERTICAL	10

class ServiciosGraficos {
private:
	static const SDL_VideoInfo* videoInfo;

	static int bordeSuperior;
	static int bordeInferior;
	static int bordeIzquierdo;
	static int bordeDerecho;

	static int altoVentana;
	static int anchoVentana;

	static Uint32 Rmask;
	static Uint32 Gmask;
	static Uint32 Bmask;
	static Uint32 Amask;
	static Uint8 bytesPerPixel;
	static Uint8 bitsPerPixel;
	static int current_w;
	static int current_h;

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

	static SDL_Surface* crearSuperficie(int ancho, int alto);

	static const SDL_VideoInfo* initVideoInfo();
	static Uint32 getRmask();
	static Uint32 getGmask();
	static Uint32 getBmask();
	static Uint32 getAmask();
	static Uint8 getBytesPerPixel();
	static Uint8 getBitsPerPixel();
	static int getCurrent_w();
	static int getCurrent_h();

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

	/**
	* Dibuja un borde a una superficie rectangular dada por el parametro 'offset'.
	* Este parametro debe tener seteados ancho (w) y alto (h) ya que estas seran
	* las medidas del rectangulo.
	*/
	static void ServiciosGraficos::dibujarContorno(SDL_Surface* superficie, 
			SDL_Rect* offset, Color* color);

	static int getAltoFilaVentanaSegundaria();
	static int getAnchoColVentanaSegundaria();
	
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
