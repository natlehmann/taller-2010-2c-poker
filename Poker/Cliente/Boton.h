#ifndef _BOTON_H__
#define _BOTON_H__

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

#include "ElementoGrafico.h"
#include "Imagen.h"


class Boton : public ElementoGrafico {
private:
	string texto;
	bool ajustarAlTexto;
	Imagen* imagenUp;
	Imagen* imagenDown;
	Imagen* imagenOver;

	char estado;

	Imagen* setearImagen(string nombreImagen);
	void setearPosicion();


protected:
	virtual void dibujarSobreSup(SDL_Surface* superficie);

public:
	Boton(void);
	Boton(string texto);
	Boton(string texto, int posx, int posy);
	Boton(string texto, int ancho, int alto, int posx, int posy);
	virtual ~Boton(void);

	string getTexto();
	void setTexto(string texto);
	bool estaSobre();
	bool esClickIzquierdo();
	bool esClickDerecho();

	void dibujarOver(SDL_Surface* superficie);
	void dibujarDown(SDL_Surface* superficie);
	void dibujarUp(SDL_Surface* superficie);

	bool checkClick(SDL_Surface* superficie);
	bool checkOver(SDL_Surface* superficie);
};

#endif //_BOTON_H__
