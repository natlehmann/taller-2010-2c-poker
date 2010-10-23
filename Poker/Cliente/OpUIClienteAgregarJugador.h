#ifndef _OPUICLIENTE_AGREGARJUGADOR_H_
#define _OPUICLIENTE_AGREGARJUGADOR_H_

#include "OperacionUICliente.h"

using namespace std;

class OpUIClienteAgregarJugador : public OperacionUICliente
{
public:
	OpUIClienteAgregarJugador(vector<string> parametros);
	virtual ~OpUIClienteAgregarJugador(void);

	virtual bool ejecutar(Ventana* ventana);
};

#endif //_OPUICLIENTE_AGREGARJUGADOR_H_
