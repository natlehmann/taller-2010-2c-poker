#ifndef _OPERACION_UI_CLIENTE_SUBIRAPUESTA_H_
#define _OPERACION_UI_CLIENTE_SUBIRAPUESTA_H_


#include "OperacionUICliente.h"

using namespace std;

class OpUIClienteSubirApuesta : public OperacionUICliente
{
public:
	OpUIClienteSubirApuesta(void);
	virtual ~OpUIClienteSubirApuesta(void);

	virtual bool ejecutar(Ventana* ventana);
};

#endif //_OPERACION_UI_CLIENTE_SUBIRAPUESTA_H_
