#ifndef _IMAGEN_H__
#define _IMAGEN_H__

#define _CRT_SECURE_NO_DEPRECATE 1


#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <windows.h>

#include "ElementoGrafico.h"

class Imagen : public ElementoGrafico {
private:
	string nombre;
	string nombreSinPath;

	SDL_Surface* cargarBMP();
	char* invertirBMP(char *bitmapImage, BITMAPINFOHEADER bitmapInfoHeader);

protected:
	virtual void dibujarSobreSup(SDL_Surface* superficie);

public:
	Imagen(string nombre);
	Imagen(string nombre, bool solicitarImagen);
	virtual ~Imagen(void);

	string getNombre();
	string getNombreSinPath();

	void dibujarSobreSup(SDL_Surface* superficie, SDL_Rect* posicionEnSup);
	void generarSuperficie();
};

#endif //_IMAGEN_H__