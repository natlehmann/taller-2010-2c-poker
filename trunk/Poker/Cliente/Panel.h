#ifndef _PANEL_H__
#define _PANEL_H__

#include "SDL.h" 
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <list>

#include "Contenedor.h"
#include "Boton.h"
#include "TextBox.h"
#include "Color.h"

#define PANEL_SEPARACION_BOTONES_H  10
#define PANEL_SEPARACION_BOTONES_V  4

#define MAX_CANT_BOTONES 6


using namespace std;

class Panel : public Contenedor
{
private:
	Color* borde;
	Color* fondo;

	/*
	Boton* btDejarMesa;
	Boton* btNoIr;
	Boton* btIgualar;
	Boton* btSubir;
	*/
	TextBox* textBox;

	Boton* botones[MAX_CANT_BOTONES];
	bool hayNuevosBotones;
	list<Boton*> listaBotones;

	void configurarBotones();

protected:
	virtual void dibujarSobreSup(SDL_Surface* superficie);

public:
	Panel(void);
	virtual ~Panel(void);

	/**
	* Agrega un boton en una posicion determinada.
	*/
	void agregarBoton(Boton* boton, int posicion);

	list<Boton*> getBotones();

	virtual ElementoGrafico* getElementoPorId(string id);

	/*
	Boton* getBotonDejarMesa();
	Boton* getBotonNoIr();
	Boton* getBotonIgualar();
	Boton* getBotonSubir();
	*/
	TextBox* getTextBox();
};
#endif //_PANEL_H__
