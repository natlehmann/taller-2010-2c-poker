#ifndef _TEXTBOX_H__
#define _TEXTBOX_H__


#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

#include "SDL_ttf.h"
#include "ComponentePanel.h"
#include "Color.h"
#include "Fuente.h"
#include "UtilTiposDatos.h"


class TextBox : public ComponentePanel
{
private:
	Color* fondoFoco;
	Color* fondoNotFoco;
	Color* borde;

	bool foco;
	string::size_type cursorPosition;

	int alineacionHorizontal;
	int alineacionVertical;

	void ajustarOffset(SDL_Rect* offset, SDL_Surface* superficie);

protected:
	virtual void dibujarSobreSup(SDL_Surface* superficie);

public:
	TextBox(string mensaje);
	virtual ~TextBox(void);

	virtual ComponentePanel* clonar();

	void dibujarTexto(SDL_Surface* superficie);

	bool checkWrite(SDL_Surface* superficie, SDL_Event* evento, int pressed);
	bool checkClick(SDL_Surface* superficie);
	bool checkOver(SDL_Surface* superficie);

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
