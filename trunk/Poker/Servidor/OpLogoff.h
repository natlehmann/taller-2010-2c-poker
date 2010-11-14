#pragma once

#include "Operacion.h"

class OpLogoff: public Operacion
{
	protected:
		virtual bool ejecutarAccion(Socket* socket);
	
	public:
		OpLogoff(int idCliente, vector<string> parametros);
		virtual ~OpLogoff(void);
};
