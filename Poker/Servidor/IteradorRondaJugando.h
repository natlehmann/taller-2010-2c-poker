#ifndef _ITERADOR_RONDA_JUGANDO_H_
#define _ITERADOR_RONDA_JUGANDO_H_

#include "IteradorRonda.h"

class IteradorRondaJugando : public IteradorRonda
{
private:
	int indiceFinal;

	void setIndiceFinal();

public:
	IteradorRondaJugando(JugadorModelo** jugadores, int indiceInicial);
	virtual ~IteradorRondaJugando(void);

	virtual JugadorModelo* getSiguiente();
	virtual void reset(int indiceInicial);
};

#endif //_ITERADOR_RONDA_JUGANDO_H_
