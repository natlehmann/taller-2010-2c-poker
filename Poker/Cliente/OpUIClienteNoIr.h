#ifndef _OPERACION_UI_CLIENTE_NOIR_H_
#define _OPERACION_UI_CLIENTE_NOIR_H_


#include "OperacionUICliente.h"

using namespace std;

class OpUIClienteNoIr : public OperacionUICliente
{
protected:
	virtual bool ejecutarAccion(Ventana* ventana);

public:
	OpUIClienteNoIr(void);
	virtual ~OpUIClienteNoIr(void);
};

#endif //_OPERACION_UI_CLIENTE_NOIR_H_
