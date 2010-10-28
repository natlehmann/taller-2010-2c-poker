#ifndef _OPUICLIENTE_AGREGARJUGADOR_H_
#define _OPUICLIENTE_AGREGARJUGADOR_H_

#include "OperacionUICliente.h"

using namespace std;

class OpUIClienteAgregarJugador : public OperacionUICliente
{
protected:
	virtual bool ejecutarAccion(Ventana* ventana);

public:
	OpUIClienteAgregarJugador(vector<string> parametros);
	virtual ~OpUIClienteAgregarJugador(void);
};

#endif //_OPUICLIENTE_AGREGARJUGADOR_H_
