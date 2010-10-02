#ifndef _IMAGENRECORTADA_H__
#define _IMAGENRECORTADA_H__


#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

#include "ElementoGrafico.h"
#include "Color.h"

class ImagenRecortada : public ElementoGrafico {

private:
	Color* colorMascara;
	bool hayCambios;

	void setMascaraDefault();

protected:
	virtual void dibujarSobreSup(SDL_Surface* superficie);

public:
	ImagenRecortada(int ancho, int alto);
	virtual ~ImagenRecortada(void);

	virtual SDL_Surface* getSuperficie();

	virtual void setAncho(int ancho);
	virtual void setAlto(int alto);

	Color* getColorMascara();
	void setColorMascara(Uint8 red, Uint8 green, Uint8 blue);
	void setColorMascara(Color colorMascara);
};

#endif //_IMAGENRECORTADA_H__