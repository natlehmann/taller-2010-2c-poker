#pragma once
#include "operacion.h"

class OpEnviarEstadistica : public Operacion
{
	private: 
	string getFechaActual();
	string getHoraActual();
	ofstream* archivo;

	protected:
		virtual bool ejecutarAccion(Socket* socket);

	public:
		OpEnviarEstadistica(int idCliente, vector<string> parametros);
		~OpEnviarEstadistica(void);
};
