#ifndef _CONTENEDOR_H__
#define _CONTENEDOR_H__

#include "SDL.h" 
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <list>

#include "ElementoGrafico.h"

using namespace std;

class Contenedor : public ElementoGrafico {
protected:
	list<ElementoGrafico*> elementos;

public:
	Contenedor(void);
	virtual ~Contenedor(void);

	void agregarElementoGrafico(ElementoGrafico* elemento);
	
};

#endif //_CONTENEDOR_H__
