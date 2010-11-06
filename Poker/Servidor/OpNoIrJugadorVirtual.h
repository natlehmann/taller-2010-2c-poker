#ifndef _OP_NOIR_JUGADORVIRTUAL_H_
#define _OP_NOIR_JUGADORVIRTUAL_H_

#include "OpJugadorVirtual.h"

class OpNoIrJugadorVirtual : public OpJugadorVirtual
{
protected:
	virtual bool ejecutarAccion(Socket* socket);

public:
	OpNoIrJugadorVirtual(int idCliente);
	~OpNoIrJugadorVirtual(void);
};

#endif //_OP_NOIR_JUGADORVIRTUAL_H_

