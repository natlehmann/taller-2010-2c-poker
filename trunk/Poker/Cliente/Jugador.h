#ifndef _JUGADOR_H__
#define _JUGADOR_H__


#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

#include "ElementoGrafico.h"
#include "Imagen.h"
#include "Carta.h"
#include "Apuesta.h"
#include "Etiqueta.h"

#define ALTO_MIN_ETIQUETA	0.25
#define ANCHO_MIN_CARTAS	0.3
#define SEPARACION_ENTRE_CARTAS	 1
#define SEPARACION_CARTAS_APUESTA 5
#define ALTO_MAXIMO_ETIQUETA 20
#define ANCHO_CARTA_PROPORCIONAL  0.65
#define ALTO_CARTA_PROPORCIONAL  0.85
#define JUGADOR_AUSENTE		0
#define JUGADOR_ACTIVO		1
#define JUGADOR_INACTIVO	2


class Jugador : public ElementoGrafico {
private:
	string nombre;
	int fichas;
	int estado;
	Carta* carta1;
	Carta* carta2;
	Apuesta* apuesta;
	Etiqueta* etiquetaNombre;
	Etiqueta* etiquetaFichas;
	bool dealer;
	Imagen* imagenDealer;

	void setearDisposicionAIzq();
	void setearDisposicionADer();
	SDL_Rect* calcularRectFoto();
	Imagen* getImagenDefault();
	void calcularCoordenadas();

	void dibujarJugador(SDL_Surface* superficie);

protected:
	Imagen* imagen;
	virtual void dibujarSobreSup(SDL_Surface* superficie);

public:
	Jugador(void);
	virtual ~Jugador(void);

	string getNombre();
	void setNombre(string nombre);

	Imagen* getImagen();
	void setImagen(string nombreImagen);

	void setCarta1(Carta* carta);
	void setCarta2(Carta* carta);
	Carta* getCarta1();
	Carta* getCarta2();

	/**
	* Setea alguna carta (la 1 o la 2) dependiendo de cual no haya sido seteada previamente.
	* Si ambas cartas ya fueron seteadas, lanza una excepcion.
	*/
	void setCarta(Carta* carta);

	void setApuesta(string cantidad);
	Apuesta* getApuesta();

	void setFichas(int cantidad);
	int getFichas();

	int getEstado();
	void setEstado(int estado);

	bool isDealer();
	void setDealer(bool esDealer);

	ElementoGrafico* getElementoPorId(string id);
};

#endif //_JUGADOR_H__
