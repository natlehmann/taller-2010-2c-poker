#ifndef _OPUICLIENTE_LOGIN_H_
#define _OPUICLIENTE_LOGIN_H_

#include "OperacionUICliente.h"

using namespace std;

class OpUIClienteLogin : public OperacionUICliente
{
protected:
	virtual bool ejecutarAccion(Ventana* ventana);

public:
	OpUIClienteLogin(void);
	virtual ~OpUIClienteLogin(void);
};

#endif //_OPUICLIENTE_LOGIN_H_
