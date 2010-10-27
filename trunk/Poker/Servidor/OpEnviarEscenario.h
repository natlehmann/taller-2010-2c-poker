#ifndef _OP_ENVIARESCENARIO_H_
#define _OP_ENVIARESCENARIO_H_

#include "Operacion.h"

class OpEnviarEscenario : public Operacion
{
public:
	OpEnviarEscenario(int idCliente);
	virtual ~OpEnviarEscenario(void);

	bool ejecutar(Socket* socket);
};

#endif // _OP_ENVIARESCENARIO_H_
