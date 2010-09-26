#ifndef _VENTANA_H__
#define _VENTANA_H__

#define RESOLUCION_PANTALLA 32

#include "SDL.h" 
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

#include "Contenedor.h"

using namespace std;

class Ventana : public Contenedor {
private:
	SDL_Surface* pantalla;

public:
	Ventana(void);
	virtual ~Ventana(void);

	virtual void dibujar();
};

#endif //_VENTANA_H__
