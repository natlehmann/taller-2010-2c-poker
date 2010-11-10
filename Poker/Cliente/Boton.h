#ifndef _BOTON_H__
#define _BOTON_H__

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

#include "ComponentePanel.h"
#include "Imagen.h"


class Boton : public ComponentePanel {
private:
	Imagen* imagenUp;
	Imagen* imagenDown;
	Imagen* imagenOver;
	Imagen* imagenDeshabilitado;

	SDL_Surface* superficieTexto;
	bool hayCambiosTexto;

	char estado;

	Imagen* setearImagen(string nombreImagen);
	SDL_Rect* getOffsetTexto();
	void configurar();
	void dibujarBoton(SDL_Surface* superficie, Imagen* imagen);


protected:
	virtual void dibujarSobreSup(SDL_Surface* superficie);

public:
	Boton(string texto);
	//Boton(string texto, int alto, int ancho);
	virtual ~Boton(void);	

	virtual ComponentePanel* clonar();

	void dibujarOver(SDL_Surface* superficie);
	virtual void dibujarDown(SDL_Surface* superficie);
	virtual void dibujarUp(SDL_Surface* superficie);

	virtual bool checkClick(SDL_Surface* superficie);
	virtual bool checkOver(SDL_Surface* superficie);
	virtual bool checkWrite(SDL_Surface* superficie, SDL_Event* evento, int pressed);

	virtual void setPosX(int posX);
	virtual void setPosY(int posY);

	virtual void setTexto(string texto);

	virtual bool equals(ElementoGrafico* otro);
};

#endif //_BOTON_H__
