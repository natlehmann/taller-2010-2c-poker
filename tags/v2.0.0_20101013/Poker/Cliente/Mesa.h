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
	string id;
	Imagen* imagen;

protected:
	virtual void dibujarSobreSup(SDL_Surface* superficie);

public:
	Mesa(void);
	virtual ~Mesa(void);

	string getId();
	void setId(string id);

	void setFondo(string nombreImagen);
};

#endif //_MESA_H__

