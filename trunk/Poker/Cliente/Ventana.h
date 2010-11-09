#ifndef _VENTANA_H__
#define _VENTANA_H__

#define RESOLUCION_PANTALLA 24
#define FRAMES_PER_SECOND   15

#include "SDL.h" 
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <list>
#include "Panel.h"
#include "Mesa.h"
#include <windows.h>

using namespace std;

//class VentanaAuxiliar;

class Ventana {

protected:
	Ventana(void);

public:
	virtual ~Ventana(void);

	virtual void iniciar() = 0;
	virtual void limpiar() = 0;

	virtual int PushEvent(SDL_Event *event) = 0;
	virtual void merge(SDL_Surface* superficie) = 0;

	virtual Panel* getPanelComando() = 0;
	virtual void setPanelComando(Panel* panel) = 0;

	/* Metodos de Contenedor */
	virtual void agregarElementoGrafico(ElementoGrafico* elemento) = 0;
	virtual void borrarElementoPorId(string id) = 0;
	virtual void borrarElemento(ElementoGrafico* elemento) = 0;
	virtual ElementoGrafico* getElementoPorId(string id) = 0;


	virtual void mostrarMensaje(string mensaje) = 0;
	/**
	* Fuerza el redibujo de todos los elementos de la ventana que se intersecten con el elemento
	* recibido por parametro.
	* Pensado para casos en que desaparece un elemento.
	*/
	virtual void forzarRefresh(ElementoGrafico* elemento) = 0;
	
	/* Metodos de ElementoGrafico */
	virtual int getAncho() = 0;
	virtual int getAlto() = 0;
	

};

#endif //_VENTANA_H__
