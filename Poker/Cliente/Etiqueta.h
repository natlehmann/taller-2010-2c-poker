#ifndef _ETIQUETA_H__
#define _ETIQUETA_H__


#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

#include "SDL_ttf.h"
#include "ElementoGrafico.h"
#include "Color.h"
#include "Fuente.h"
#include "UtilTiposDatos.h"

#define MAXIMO_ANCHO_PANTALLA_PROP_TXT 800
#define MAXIMO_ALTO_PANTALLA_PROP_TXT 600

#define ALINEACION_HORIZ_DERECHA 1
#define ALINEACION_HORIZ_IZQUIERDA -1
#define ALINEACION_HORIZ_CENTRO 0

#define ALINEACION_VERT_ABAJO 1
#define ALINEACION_VERT_ARRIBA -1
#define ALINEACION_VERT_CENTRO 0

class Etiqueta : public ElementoGrafico
{
private:
	string mensaje;
	Color* fondo;
	int alineacionHorizontal;
	int alineacionVertical;

	void ajustarOffset(SDL_Rect* offset, SDL_Surface* superficie);

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

	void setAlineacionHorizontal(int alineacion);
	int getAlineacionHorizontal();

	void setAlineacionVertical(int alineacion);
	int getAlineacionVertical();
};

#endif //_ETIQUETA_H__
