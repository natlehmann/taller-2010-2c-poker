#ifndef _JUGADOR_H__
#define _JUGADOR_H__


#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

#include "ElementoGrafico.h"
#include "Imagen.h"

#define ALTO_MIN_ETIQUETA	0.25
#define ANCHO_MIN_CARTAS	0.3

class Jugador : public ElementoGrafico {
private:
	int id;
	string nombre;
	int posicion;
	Imagen* imagen;

	void setearDisposicionAIzq();
	void setearDisposicionADer();
	SDL_Rect* calcularRectFoto();

protected:
	virtual void dibujarSobreSup(SDL_Surface* superficie);

public:
	Jugador(void);
	virtual ~Jugador(void);

	int getId();
	void setId(int id);
	string getNombre();
	void setNombre(string nombre);
	int getPosicion();
	void setPosicion(int posicion);

	Imagen* getImagen();
	void setImagen(Imagen* imagen);
};

#endif //_JUGADOR_H__
