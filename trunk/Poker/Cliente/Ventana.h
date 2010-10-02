#ifndef _VENTANA_H__
#define _VENTANA_H__

#define RESOLUCION_PANTALLA 24

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

protected:
	virtual void dibujarSobreSup(SDL_Surface* superficie);

public:
	Ventana(void);
	virtual ~Ventana(void);
};

#endif //_VENTANA_H__
