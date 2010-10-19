#ifndef _OPERACION_UI_CLIENTE_IGUALARAPUESTA_H_
#define _OPERACION_UI_CLIENTE_IGUALARAPUESTA_H_


#include "OperacionUICliente.h"

using namespace std;

class OpUIClienteIgualarApuesta : public OperacionUICliente
{
public:
	OpUIClienteIgualarApuesta(void);
	virtual ~OpUIClienteIgualarApuesta(void);

	virtual bool ejecutar(Ventana* ventana);
};

#endif //_OPERACION_UI_CLIENTE_IGUALARAPUESTA_H_
