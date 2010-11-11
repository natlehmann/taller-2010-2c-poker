#pragma once
#include "operacionuicliente.h"

class OpUIClienteEnviarFoto :	public OperacionUICliente
{
	protected:
		virtual bool ejecutarAccion(Ventana* ventana);

	public:
		OpUIClienteEnviarFoto(vector<string> parametros);
		virtual ~OpUIClienteEnviarFoto(void);

	
};
