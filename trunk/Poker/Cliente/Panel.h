#ifndef _PANEL_H__
#define _PANEL_H__

#include "SDL.h" 
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

#include "Contenedor.h"

using namespace std;

class Panel : public Contenedor
{
protected:
	virtual void dibujarSobreSup(SDL_Surface* superficie);

public:
	Panel(void);
	virtual ~Panel(void);
};

#endif //_PANEL_H__
