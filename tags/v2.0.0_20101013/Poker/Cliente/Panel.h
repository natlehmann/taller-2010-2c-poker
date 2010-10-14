#ifndef _PANEL_H__
#define _PANEL_H__

#include "SDL.h" 
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

#include "Contenedor.h"
#include "Boton.h"
#include "Color.h"

#define PANEL_SEPARACION_BOTONES_H  10
#define PANEL_SEPARACION_BOTONES_V  4


using namespace std;

class Panel : public Contenedor
{
private:
	Color* borde;
	Color* fondo;
	Boton* btDejarMesa;
	Boton* btNoIr;
	Boton* btIgualar;
	Boton* btSubir;

	void configurarBotones();
protected:
	virtual void dibujarSobreSup(SDL_Surface* superficie);

public:
	Panel(void);
	virtual ~Panel(void);

	Boton* getBotonDejarMesa();
	Boton* getBotonNoIr();
	Boton* getBotonIgualar();
	Boton* getBotonSubir();
};
#endif //_PANEL_H__
