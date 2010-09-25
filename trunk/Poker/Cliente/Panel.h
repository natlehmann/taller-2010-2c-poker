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
public:
	Panel(void);
	virtual ~Panel(void);

	virtual void dibujar();
};

#endif //_PANEL_H__
