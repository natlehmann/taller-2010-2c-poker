#ifndef _OP_SUBIR_JUGADORVIRTUAL_H_
#define _OP_SUBIR_JUGADORVIRTUAL_H_

#include "OpJugadorVirtual.h"

class OpSubirJugadorVirtual : public OpJugadorVirtual
{
protected:
	virtual bool ejecutarAccion(Socket* socket);

public:
	OpSubirJugadorVirtual(int idCliente);
	~OpSubirJugadorVirtual(void);
};

#endif //_OP_SUBIR_JUGADORVIRTUAL_H_

