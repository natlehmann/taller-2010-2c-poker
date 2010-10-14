#ifndef _APUESTA_H__
#define _APUESTA_H__


#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

#include "ElementoGrafico.h"
#include "Imagen.h"
#include "Etiqueta.h"

#define APUESTA_ALTO_ETIQUETA 0.30

class Apuesta : public ElementoGrafico {
private:
	string cantidad;
	Imagen* imagen;
	Etiqueta* etiqueta;

protected:
	virtual void dibujarSobreSup(SDL_Surface* superficie);

public:
	Apuesta(string cantidad);
	virtual ~Apuesta(void);

	string getCantidad();
	void setCantidad(string cantidad);
};

#endif //_APUESTA_H__
