#ifndef _OPERACION_UI_CLIENTE_DEJARMESA_H_
#define _OPERACION_UI_CLIENTE_DEJARMESA_H_


#include "OperacionUICliente.h"

using namespace std;

class OpUIClienteDejarMesa : public OperacionUICliente 
{
public:
	OpUIClienteDejarMesa(void);
	virtual ~OpUIClienteDejarMesa(void);

	virtual bool ejecutar(Ventana* ventana);
};

#endif //_OPERACION_UI_CLIENTE_DEJARMESA_H_
