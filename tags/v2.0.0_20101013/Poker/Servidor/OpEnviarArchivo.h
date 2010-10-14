#ifndef _OP_ENVIARARCHIVO_H_
#define _OP_ENVIARARCHIVO_H_

#include "Operacion.h"
#include <vector>

class OpEnviarArchivo : public Operacion
{
	protected:
	vector<string> parametros;
	public:
	OpEnviarArchivo(vector<string> parametros);
	virtual ~OpEnviarArchivo(void);

	bool ejecutar(Socket* socket);
};

#endif // _OP_ENVIARARCHIVO_H_
