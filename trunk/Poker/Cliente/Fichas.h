#ifndef _FICHAS_H__
#define _FICHAS_H__


#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

#include "ElementoGrafico.h"
#include "Imagen.h"
#include "Etiqueta.h"

#define FICHAS_ALTO_ETIQUETA 0.30

class Fichas : public ElementoGrafico {
private:
	string cantidad;
	Imagen* imagen;
	Etiqueta* etiqueta;

protected:
	virtual void dibujarSobreSup(SDL_Surface* superficie);

public:
	Fichas(string cantidad);
	virtual ~Fichas(void);

	string getCantidad();
	void setCantidad(string cantidad);
};

#endif //_FICHAS_H__
