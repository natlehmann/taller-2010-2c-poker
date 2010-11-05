#ifndef _ITERADOR_RONDA_ACTIVOS_H_
#define _ITERADOR_RONDA_ACTIVOS_H_

#include "IteradorRonda.h"

class IteradorRondaActivos : public IteradorRonda
{
private:
	int indiceFinal;

	void setIndiceFinal();

public:
	IteradorRondaActivos(JugadorModelo** jugadores, int indiceInicial);
	virtual ~IteradorRondaActivos(void);

	virtual JugadorModelo* getSiguiente();
	virtual void reset(int indiceInicial);
};

#endif //_ITERADOR_RONDA_ACTIVOS_H_
