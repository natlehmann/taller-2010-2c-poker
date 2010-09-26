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

public:
	Imagen(void);
	virtual ~Imagen(void);

	virtual void dibujar();

	void setNombre(string nombre);
	string getNombre();

	void setTamanio(long tamanio);
	long getTamanio();
};

#endif //_IMAGEN_H__