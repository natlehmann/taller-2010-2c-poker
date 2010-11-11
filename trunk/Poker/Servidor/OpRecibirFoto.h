#pragma once
#include "Operacion.h"
#include <fstream>
#include <string>

using namespace std;

class OpRecibirFoto : public Operacion
{
	protected:
			virtual bool ejecutarAccion(Socket* socket);

	public:
		OpRecibirFoto(int idCliente, vector<string> parametros);
		virtual ~OpRecibirFoto(void);
};
