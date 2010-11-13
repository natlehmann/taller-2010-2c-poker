#ifndef _VENTANABASE_H__
#define _VENTANABASE_H__

#include "SDL.h" 
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <list>
#include "Panel.h"
#include "Mesa.h"
#include <windows.h>
#include "Ventana.h"
#include "Mensaje.h"

using namespace std;

class VentanaBase : public Ventana {

protected:
	SDL_Surface* pantalla;
	SDL_Rect* offset;
	SDL_Rect* contorno;
	SDL_Rect* contornoConOffset;
	Color* fondo;

	int altoFila;
	int anchoColumna;

	string id;	
	int posX;
	int posY;
	int ancho;
	int alto;

	bool hayCambios;

public:
	VentanaBase(void);
	virtual ~VentanaBase(void);

	virtual void iniciar() = 0;
	virtual void agregarElementoGrafico(ElementoGrafico* elemento) = 0;

	//metodos que se utilizan
	virtual SDL_Rect* getContornoConOffset();
	SDL_Surface* getSuperficie();
	SDL_Rect* getOffsetRect();
	SDL_Rect* getContornoRect();
	void setHayCambios(bool hayCambios);
	int getPosX();
	void setPosX(int posX);
	int getPosY();
	void setPosY(int posY);	
	virtual int getAncho();
	void setAncho(int ancho);
	virtual int getAlto();
	void setAlto(int alto);
	string getId();
	void setId(string id);

	//metodos que no se utilizan
	virtual Panel* getPanelComando() { return NULL; };
	virtual void setPanelComando(Panel* panel) {};
	virtual void limpiar() {};
	virtual void borrarElementoPorId(string id) {};
	virtual ElementoGrafico* getElementoPorId(string id) { return NULL; };
	virtual void borrarElemento(ElementoGrafico* elemento) {};
	virtual void forzarRefresh(ElementoGrafico* elemento) {};
	virtual int PushEvent(SDL_Event *event) { return 0; };
	virtual void merge(SDL_Surface* superficie) {};

};

#endif //_VENTANABASE_H__
