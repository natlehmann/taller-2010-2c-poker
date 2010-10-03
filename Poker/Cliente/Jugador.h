#ifndef _JUGADOR_H__
#define _JUGADOR_H__


#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

#include "ElementoGrafico.h"
#include "Imagen.h"
#include "Carta.h"

#define ALTO_MIN_ETIQUETA	0.25
#define ANCHO_MIN_CARTAS	0.3
#define SEPARACION_ENTRE_CARTAS	 1

class Jugador : public ElementoGrafico {
private:
	int id;
	string nombre;
	int posicion;
	Imagen* imagen;
	Carta* carta1;
	Carta* carta2;

	void setearDisposicionAIzq();
	void setearDisposicionADer();
	SDL_Rect* calcularRectFoto();

	void dibujarJugador(SDL_Surface* superficie);

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

	void setCarta1(Carta* carta);
	void setCarta2(Carta* carta);
	Carta* getCarta1();
	Carta* getCarta2();

	/**
	* Setea alguna carta (la 1 o la 2) dependiendo de cual no haya sido seteada previamente.
	* Si ambas cartas ya fueron seteadas, lanza una excepcion.
	*/
	void setCarta(Carta* carta);
};

#endif //_JUGADOR_H__
