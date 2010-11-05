#pragma once

#include "Operacion.h"

class OpLogin: public Operacion
{
	protected:
		virtual bool ejecutarAccion(Socket* socket);
	
	public:
		OpLogin(int idCliente, vector<string> parametros);
		virtual ~OpLogin(void);
};
