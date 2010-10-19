#ifndef _BOTON_H__
#define _BOTON_H__

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

#include "ElementoGrafico.h"
#include "Imagen.h"
#include "Fuente.h"

#define MAXIMO_ANCHO_PANTALLA_PROP_TXT 800
#define PADDING_HORIZ   20
#define PADDING_VERT	20


class Boton : public ElementoGrafico {
private:
	string texto;
	bool ajustarAlTexto;
	Imagen* imagenUp;
	Imagen* imagenDown;
	Imagen* imagenOver;
	Fuente* fuente;
	bool habilitado;

	string idOperacion;

	char estado;

	Imagen* setearImagen(string nombreImagen);
	//void setearPosicion();
	void setearFuente();


protected:
	virtual void dibujarSobreSup(SDL_Surface* superficie);

public:
	//Boton(void);
	Boton(string texto);
	Boton(Boton* orig);
	//Boton(string texto, int posx, int posy);
	//Boton(string texto, int ancho, int alto, int posx, int posy);
	virtual ~Boton(void);

	string getTexto();
	void setTexto(string texto);
	bool estaSobre();
	bool esClickIzquierdo();
	bool esClickDerecho();

	bool isHabilitado();
	void setHabilitado(bool habilitado);

	string getIdOperacion();
	void setIdOperacion(string idOperacion);

	void dibujarOver(SDL_Surface* superficie);
	void dibujarDown(SDL_Surface* superficie);
	void dibujarUp(SDL_Surface* superficie);

	bool checkClick(SDL_Surface* superficie);
	bool checkOver(SDL_Surface* superficie);

	virtual void setPosX(int posX);
	virtual void setPosY(int posY);

	virtual bool equals(ElementoGrafico* otro);
};

#endif //_BOTON_H__
