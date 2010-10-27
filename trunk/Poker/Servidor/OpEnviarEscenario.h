#ifndef _OP_ENVIARESCENARIO_H_
#define _OP_ENVIARESCENARIO_H_

#include "Operacion.h"

class OpEnviarEscenario : public Operacion
{
protected:
	virtual bool ejecutarAccion(Socket* socket);

public:
	OpEnviarEscenario(int idCliente);
	virtual ~OpEnviarEscenario(void);
};

#endif // _OP_ENVIARESCENARIO_H_
