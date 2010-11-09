#pragma once
#include "operacion.h"

class OpComprarFichas :	public Operacion
{
	protected:
		virtual bool ejecutarAccion(Socket* socket);

	public:
		OpComprarFichas(int idCliente, vector<string> parametros);
		virtual ~OpComprarFichas(void);
};
