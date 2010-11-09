#ifndef _OPUICLIENTE_REGISTRARJUGADOR_H_
#define _OPUICLIENTE_REGISTRARJUGADOR_H_

#include "OperacionUICliente.h"

using namespace std;

class OpUIClienteRegistrarJugador : public OperacionUICliente
{
	protected:
		virtual bool ejecutarAccion(Ventana* ventana);

	public:
		OpUIClienteRegistrarJugador(vector<string> parametros);
		virtual ~OpUIClienteRegistrarJugador(void);
};

#endif //_OPUICLIENTE_REGISTRARJUGADOR_H_