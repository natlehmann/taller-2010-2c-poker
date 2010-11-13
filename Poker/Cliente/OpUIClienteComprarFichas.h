#pragma once
#include "operacionuicliente.h"

class OpUIClienteComprarFichas : public OperacionUICliente
{
	private:
		string error;

	protected:
		virtual bool ejecutarAccion(Ventana* ventana);

	public:
		OpUIClienteComprarFichas(vector<string> parametros);
		virtual ~OpUIClienteComprarFichas(void);

		virtual string getError();
};
