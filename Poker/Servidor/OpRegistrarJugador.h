#pragma once
#include "operacion.h"

class OpRegistrarJugador : public Operacion
{
	protected:
		virtual bool ejecutarAccion(Socket* socket);

	public:
		OpRegistrarJugador(int idCliente, vector<string> parametros);
		virtual ~OpRegistrarJugador(void);
};
