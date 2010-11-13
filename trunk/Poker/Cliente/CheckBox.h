#ifndef _CHECKBOX_H__
#define _CHECKBOX_H__

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

#include "ComponentePanel.h"
#include "Imagen.h"


class CheckBox : public ComponentePanel {
private:
	Imagen* imagenCheck;
	Imagen* imagenUnCheck;
	Imagen* imagenOverCheck;
	Imagen* imagenOverUnCheck;
	Imagen* imagenDeshabilitado;

	SDL_Surface* superficieTexto;
	bool hayCambiosTexto;

	int altoImagen;
	int anchoImagen;
	int espacio;
	char estado;
	bool checked;

	Imagen* setearImagen(string nombreImagen);
	void setearImagenTexto();
	SDL_Rect* getOffsetTexto();

	void configurar();
	void dibujarBoton(SDL_Surface* superficie, Imagen* imagen);


protected:
	virtual void dibujarSobreSup(SDL_Surface* superficie);

public:
	CheckBox(string texto);
	virtual ~CheckBox(void);	

	virtual ComponentePanel* clonar();

	void dibujarOverCheck(SDL_Surface* superficie);
	void dibujarOverUnCheck(SDL_Surface* superficie);
	virtual void dibujarDown(SDL_Surface* superficie);
	virtual void dibujarUp(SDL_Surface* superficie);

	virtual bool checkClick(SDL_Surface* superficie);
	virtual bool checkOver(SDL_Surface* superficie);
	virtual bool checkWrite(SDL_Surface* superficie, SDL_Event* evento, int pressed);

	virtual void setPosX(int posX);
	virtual void setPosY(int posY);
	virtual void setTexto(string texto);
	void setChecked(bool checked);
	bool getChecked();

	virtual bool equals(ElementoGrafico* otro);
};

#endif //_CHECKBOX_H__
