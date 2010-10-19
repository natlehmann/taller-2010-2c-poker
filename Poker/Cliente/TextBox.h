#ifndef _TEXTBOX_H__
#define _TEXTBOX_H__


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

class TextBox : public ElementoGrafico
{
private:
	Color* fondoFoco;
	Color* fondoNotFoco;
	Color* borde;
	Fuente* fuente;

	bool foco;
	string::size_type cursorPosition;
	string mensaje;
	int alineacionHorizontal;
	int alineacionVertical;

	void ajustarOffset(SDL_Rect* offset, SDL_Surface* superficie);

protected:
	virtual void dibujarSobreSup(SDL_Surface* superficie);

public:
	TextBox(void);
	TextBox(string mensaje);
	virtual ~TextBox(void);

	void dibujarTexto(SDL_Surface* superficie);

	bool checkWrite(SDL_Surface* superficie, SDL_Event* evento, int pressed);
	bool checkClick(SDL_Surface* superficie);
	bool checkOver(SDL_Surface* superficie);
	bool estaSobre();
	bool esClickIzquierdo();
	bool esClickDerecho();

	void setMensaje(string mensaje);
	string getMensaje();

	void setFondoFoco(Color* color);
	Color* getFondoFoco();

	void setFondoNotFoco(Color* color);
	Color* getFondoNotFoco();

	void setBorde(Color* color);
	Color* getBorde();

	void setAlineacionHorizontal(int alineacion);
	int getAlineacionHorizontal();

	void setAlineacionVertical(int alineacion);
	int getAlineacionVertical();
};

#endif //_TEXTBOX_H__
