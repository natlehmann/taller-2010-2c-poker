#pragma once
#include "OpJugadorVirtual.h"

class OpSubirJugadorVirtual : public OpJugadorVirtual
{
protected:
	virtual void ejecutarAccion();
public:
	OpSubirJugadorVirtual(int idCliente);
	~OpSubirJugadorVirtual(void);
};
