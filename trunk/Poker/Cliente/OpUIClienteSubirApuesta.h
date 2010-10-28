#ifndef _OPERACION_UI_CLIENTE_SUBIRAPUESTA_H_
#define _OPERACION_UI_CLIENTE_SUBIRAPUESTA_H_


#include "OperacionUICliente.h"

using namespace std;

class OpUIClienteSubirApuesta : public OperacionUICliente
{
protected:
	virtual bool ejecutarAccion(Ventana* ventana);

public:
	OpUIClienteSubirApuesta(void);
	virtual ~OpUIClienteSubirApuesta(void);
};

#endif //_OPERACION_UI_CLIENTE_SUBIRAPUESTA_H_
