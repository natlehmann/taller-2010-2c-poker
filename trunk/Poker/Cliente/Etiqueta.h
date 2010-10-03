#ifndef _ETIQUETA_H__
#define _ETIQUETA_H__


#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

#include "ElementoGrafico.h"
#include "Color.h"

class Etiqueta : public ElementoGrafico
{
private:
	string mensaje;
	Color* fondo;

protected:
	virtual void dibujarSobreSup(SDL_Surface* superficie);

public:
	Etiqueta(void);
	Etiqueta(string mensaje);
	virtual ~Etiqueta(void);

	void setMensaje(string mensaje);
	string getMensaje();

	void setFondo(Color* color);
	Color* getFondo();
};

#endif //_ETIQUETA_H__
