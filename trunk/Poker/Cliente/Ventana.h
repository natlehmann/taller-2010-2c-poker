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

using namespace std;

class Ventana {
private:
	SDL_Surface* pantalla;
	Panel* panelComando;
	void manejarEventos(SDL_Event* event);
	void refrescar(SDL_Surface* superficie);
	Mesa* mesa;


	/* Atributos de Contenedor */
	list<ElementoGrafico*> elementos;

	/* Atributos y metodos de ElementoGrafico */
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


protected:
	Ventana(void);
	virtual void dibujarSobreSup(SDL_Surface* superficie);
	virtual void dibujar(SDL_Surface* superficie);
	

	/* Metodos de ElementoGrafico */
	SDL_Surface* getSuperficie();
	SDL_Rect* getOffsetRect();
	SDL_Rect* getContornoRect();
	void setHayCambios(bool hayCambios);
	int getPosX();
	void setPosX(int posX);
	int getPosY();
	void setPosY(int posY);	
	void setAncho(int ancho);
	void setAlto(int alto);
	string getId();
	void setId(string id);
	int getPosicion();
	void setPosicion(int posicion);
	bool equals(Ventana* otro);

public:
	virtual ~Ventana(void);

	virtual void iniciar();
	virtual void limpiar();

	virtual Panel* getPanelComando();
	virtual void setPanelComando(Panel* panel);


	virtual void bloquear();
	virtual void desbloquear();

	virtual ElementoGrafico* getElementoPorId(string id);

	virtual void borrarElementoPorId(string id);

	virtual void borrarElemento(ElementoGrafico* elemento);

	/**
	* Fuerza el redibujo de todos los elementos de la ventana que se intersecten con el elemento
	* recibido por parametro.
	* Pensado para casos en que desaparece un elemento.
	*/
	virtual void forzarRefresh(ElementoGrafico* elemento);


	/* Metodos de Contenedor */
	virtual void agregarElementoGrafico(ElementoGrafico* elemento);

	
	/* Metodos de ElementoGrafico */
	virtual int getAncho();
	virtual int getAlto();

	

};

#endif //_VENTANA_H__
