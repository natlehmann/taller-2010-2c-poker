#ifndef _ITERADOR_RONDA_H_
#define _ITERADOR_RONDA_H_

#include <string>
#include "JugadorModelo.h"

#define MAX_CANTIDAD_JUGADORES	6

class IteradorRonda
{
protected:
	JugadorModelo** jugadores;
	int indiceInicial;
	int indiceCorriente;
	int indiceAnterior;
	bool iniciado;

public:
	IteradorRonda(JugadorModelo** jugadores, int indiceInicial);
	virtual ~IteradorRonda(void);

	virtual JugadorModelo* getSiguiente();
	virtual bool esUltimo();
	virtual void reset(int indiceInicial);
};

#endif //_ITERADOR_RONDA_H_
