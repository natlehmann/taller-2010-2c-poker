#pragma once
#include "operacion.h"

class OpEnviarEstadistica : public Operacion
{
	protected:
		virtual bool ejecutarAccion(Socket* socket);

	public:
		OpEnviarEstadistica(int idCliente, vector<string> parametros);
		~OpEnviarEstadistica(void);
};
