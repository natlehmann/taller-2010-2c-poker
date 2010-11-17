#ifndef _VENTANAAUXILIAR_H__
#define _VENTANAAUXILIAR_H__

#define RESOLUCION_PANTALLA 24

#include "SDL.h" 
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <list>
#include <set>
#include "Panel.h"
#include "Mesa.h"
#include "Ventana.h"
#include "Mensaje.h"

using namespace std;

class VentanaAuxiliar : public Ventana
{
private:
	Panel* panelComando;
	Mesa* mesa;
	Mensaje* mensaje;


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

	set<string> nombresJugadores;


protected:
	virtual void dibujarSobreSup(SDL_Surface* superficie);
	

	/* Metodos de ElementoGrafico */
	SDL_Rect* getOffsetRect();
	SDL_Rect* getContornoRect();
	void setHayCambios(bool hayCambios);
	string getId();
	void setId(string id);
	int getPosicion();
	void setPosicion(int posicion);

public:
	VentanaAuxiliar(void);
	virtual ~VentanaAuxiliar(void);

	virtual void iniciar();
	virtual void limpiar();

	virtual void dibujar(SDL_Surface* superficie);

	virtual int PushEvent(SDL_Event *event);

	virtual void merge(SDL_Surface* superficie);

	virtual Panel* getPanelComando();
	virtual void setPanelComando(Panel* panel);

	virtual ElementoGrafico* getElementoPorId(string id);

	virtual void borrarElementoPorId(string id);

	virtual void borrarElemento(ElementoGrafico* elemento);

	virtual void mostrarMensaje(string mensaje);

	virtual void registrarNombreJugador(string nombre);
	void limpiarFotosJugadores();

	/**
	* Fuerza el redibujo de todos los elementos de la ventana que se intersecten con el elemento
	* recibido por parametro.
	* Pensado para casos en que desaparece un elemento.
	*/
	virtual void forzarRefresh(ElementoGrafico* elemento);


	/* Metodos de Contenedor */
	virtual void agregarElementoGrafico(ElementoGrafico* elemento);

	
	/* Metodos de ElementoGrafico */
	int getAncho();
	int getAlto();
	int getPosX();
	void setPosX(int posX);
	int getPosY();
	void setPosY(int posY);	
	void setAncho(int ancho);
	void setAlto(int alto);

	SDL_Surface* getSuperficie();
	void setSuperficie(SDL_Surface* superficie);

};

#endif //_VENTANAAUXILIAR_H__

