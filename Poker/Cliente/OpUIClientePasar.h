#ifndef _OPERACION_UI_CLIENTE_PASAR_H_
#define _OPERACION_UI_CLIENTE_PASAR_H_


#include "OperacionUICliente.h"

using namespace std;

class OpUIClientePasar : public OperacionUICliente
{
protected:
	virtual bool ejecutarAccion(Ventana* ventana);

public:
	OpUIClientePasar(void);
	virtual ~OpUIClientePasar(void);
};

#endif //_OPERACION_UI_CLIENTE_PASAR_H_

