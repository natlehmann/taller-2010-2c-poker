#ifndef _OPERACION_UI_CLIENTE_DEJARMESA_H_
#define _OPERACION_UI_CLIENTE_DEJARMESA_H_


#include "OperacionUICliente.h"

using namespace std;

class OpUIClienteDejarMesa : public OperacionUICliente 
{
protected:
	virtual bool ejecutarAccion(Ventana* ventana);

public:
	OpUIClienteDejarMesa(void);
	virtual ~OpUIClienteDejarMesa(void);
};

#endif //_OPERACION_UI_CLIENTE_DEJARMESA_H_
