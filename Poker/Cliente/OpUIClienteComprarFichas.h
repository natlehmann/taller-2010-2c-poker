#pragma once
#include "operacionuicliente.h"

class OpUIClienteComprarFichas : public OperacionUICliente
{
	protected:
		virtual bool ejecutarAccion(Ventana* ventana);

	public:
		OpUIClienteComprarFichas(vector<string> parametros);
		virtual ~OpUIClienteComprarFichas(void);
};
