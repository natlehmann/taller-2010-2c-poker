#ifndef _VENTANAIMPL_H__
#define _VENTANAIMPL_H__

#include "SDL.h" 
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <list>
#include "Panel.h"
#include "Mesa.h"
#include <windows.h>
#include "VentanaAuxiliar.h"
#include "Ventana.h"

using namespace std;

class VentanaImpl : public Ventana {
private:
	SDL_mutex* eventLock;
	SDL_cond* eventWait;

	SDL_Surface* pantalla;
	Panel* panelComando;
	void manejarEventos(SDL_Event* event);
	void refrescar(SDL_Surface* superficie);
	Mesa* mesa;

	SDL_Rect* contornoConOffset;


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
	SDL_Rect* offset;
	SDL_Rect* contorno;


protected:
	virtual void dibujarSobreSup(SDL_Surface* superficie);
	virtual void dibujar(SDL_Surface* superficie);

	virtual SDL_Rect* getContornoConOffset();
	

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

public:
	VentanaImpl(void);
	virtual ~VentanaImpl(void);


	int WaitEvent(SDL_Event *event);
	int PollEvent(SDL_Event *event);
	int PushEvent(SDL_Event *event);

	virtual void iniciar();
	virtual void limpiar();

	virtual Panel* getPanelComando();
	virtual void setPanelComando(Panel* panel);

	virtual void merge(SDL_Surface* superficie);

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

#endif //_VENTANAIMPL_H__
