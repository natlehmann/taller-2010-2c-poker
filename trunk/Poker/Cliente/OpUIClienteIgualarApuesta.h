#ifndef _OPERACION_UI_CLIENTE_IGUALARAPUESTA_H_
#define _OPERACION_UI_CLIENTE_IGUALARAPUESTA_H_


#include "OperacionUICliente.h"

using namespace std;

class OpUIClienteIgualarApuesta : public OperacionUICliente
{
protected:
	virtual bool ejecutarAccion(Ventana* ventana);

public:
	OpUIClienteIgualarApuesta(void);
	virtual ~OpUIClienteIgualarApuesta(void);
};

#endif //_OPERACION_UI_CLIENTE_IGUALARAPUESTA_H_
