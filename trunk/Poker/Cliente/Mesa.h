#ifndef _MESA_H__
#define _MESA_H__


#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

#include "ElementoGrafico.h"
#include "Imagen.h"

class Mesa : public ElementoGrafico {
private:
	Imagen* imagen;

protected:
	virtual void dibujarSobreSup(SDL_Surface* superficie);

public:
	Mesa(void);
	virtual ~Mesa(void);

	void setFondo(string nombreImagen);
};

#endif //_MESA_H__

