#ifndef _IMAGEN_H__
#define _IMAGEN_H__


#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

#include "ElementoGrafico.h"

class Imagen : public ElementoGrafico {
private:
	string nombre;
	long tamanio;

protected:
	virtual void dibujarSobreSup(SDL_Surface* superficie);

public:
	Imagen(string nombre);
	virtual ~Imagen(void);

	string getNombre();

	void setTamanio(long tamanio);
	long getTamanio();
};

#endif //_IMAGEN_H__