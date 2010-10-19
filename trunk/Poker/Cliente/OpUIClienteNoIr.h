#ifndef _OPERACION_UI_CLIENTE_NOIR_H_
#define _OPERACION_UI_CLIENTE_NOIR_H_


#include "OperacionUICliente.h"

using namespace std;

class OpUIClienteNoIr : public OperacionUICliente
{
public:
	OpUIClienteNoIr(void);
	virtual ~OpUIClienteNoIr(void);

	virtual bool ejecutar(Ventana* ventana);
};

#endif //_OPERACION_UI_CLIENTE_NOIR_H_
