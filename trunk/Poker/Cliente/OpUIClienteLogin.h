#ifndef _OPUICLIENTE_LOGIN_H_
#define _OPUICLIENTE_LOGIN_H_

#include "OperacionUICliente.h"

using namespace std;

class OpUIClienteLogin : public OperacionUICliente
{
public:
	OpUIClienteLogin(void);
	virtual ~OpUIClienteLogin(void);

	virtual bool ejecutar(Ventana* ventana);
};

#endif //_OPUICLIENTE_LOGIN_H_
