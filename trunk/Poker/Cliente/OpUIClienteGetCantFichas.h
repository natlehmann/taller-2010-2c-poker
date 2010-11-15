#ifndef _OPERACION_UI_CLIENTE_GETCANTFICHAS_H_
#define _OPERACION_UI_CLIENTE_GETCANTFICHAS_H_


#include "OperacionUICliente.h"

using namespace std;

class OpUIClienteGetCantFichas : public OperacionUICliente
{
protected:
	int cantidadFichas;

public:
	OpUIClienteGetCantFichas(vector<string> parametros);
	virtual ~OpUIClienteGetCantFichas(void);

	virtual bool ejecutarAccion(Ventana* ventana);
	int getCantidadFichas();
};

#endif //_OPERACION_UI_CLIENTE_GETCANTFICHAS_H_

