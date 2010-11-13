#ifndef _OPUICLIENTE_REGISTRARJUGADOR_H_
#define _OPUICLIENTE_REGISTRARJUGADOR_H_

#include "OperacionUICliente.h"

using namespace std;

class OpUIClienteRegistrarJugador : public OperacionUICliente
{
	private:
		string error;

	protected:
		virtual bool ejecutarAccion(Ventana* ventana);

	public:
		OpUIClienteRegistrarJugador(vector<string> parametros);
		virtual ~OpUIClienteRegistrarJugador(void);

		virtual string getError();
};

#endif //_OPUICLIENTE_REGISTRARJUGADOR_H_