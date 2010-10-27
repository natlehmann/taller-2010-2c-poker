#ifndef _OP_ENVIARARCHIVO_H_
#define _OP_ENVIARARCHIVO_H_

#include "Operacion.h"
#include <vector>

class OpEnviarArchivo : public Operacion
{
protected:
	virtual bool ejecutarAccion(Socket* socket);

public:
	OpEnviarArchivo(int idCliente, vector<string> parametros);
	virtual ~OpEnviarArchivo(void);
};

#endif // _OP_ENVIARARCHIVO_H_
