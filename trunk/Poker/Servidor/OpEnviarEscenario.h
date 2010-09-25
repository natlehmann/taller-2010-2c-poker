#ifndef _OP_ENVIARESCENARIO_H_
#define _OP_ENVIARESCENARIO_H_

#include "Operacion.h"

class OpEnviarEscenario : public Operacion
{
public:
	OpEnviarEscenario(void);
	virtual ~OpEnviarEscenario(void);

	Respuesta* ejecutar();
};

#endif // _OP_ENVIARESCENARIO_H_
