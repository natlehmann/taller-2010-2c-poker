#ifndef _OP_IGUALAR_JUGADORVIRTUAL_H_
#define _OP_IGUALAR_JUGADORVIRTUAL_H_

#include "OpJugadorVirtual.h"

class OpIgualarJugadorVirtual :	public OpJugadorVirtual
{
protected:
	virtual bool ejecutarAccion(Socket* socket);

public:
	OpIgualarJugadorVirtual(int idCliente);
	~OpIgualarJugadorVirtual();
};

#endif //_OP_IGUALAR_JUGADORVIRTUAL_H_
