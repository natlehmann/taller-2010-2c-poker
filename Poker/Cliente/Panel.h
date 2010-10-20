#ifndef _PANEL_H__
#define _PANEL_H__

#include "SDL.h" 
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <list>

#include "Contenedor.h"
#include "ComponentePanel.h"
#include "TextBox.h"
#include "Color.h"

#define PANEL_SEPARACION_BOTONES_H  10
#define PANEL_SEPARACION_BOTONES_V  4

#define MAX_CANT_COMPONENTES 6


using namespace std;

class Panel : public Contenedor
{
private:
	Color* borde;
	Color* fondo;

	ComponentePanel* componentes[MAX_CANT_COMPONENTES];
	bool hayNuevosComponentes;
	list<ComponentePanel*> listaComponentes;

	void configurar();

protected:
	virtual void dibujarSobreSup(SDL_Surface* superficie);

public:
	Panel(void);
	virtual ~Panel(void);

	/**
	* Agrega un boton en una posicion determinada.
	*/
	void agregarComponente(ComponentePanel* componente, int posicion);

	list<ComponentePanel*> getComponentes();

	virtual ElementoGrafico* getElementoPorId(string id);
};
#endif //_PANEL_H__
