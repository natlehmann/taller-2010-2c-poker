#ifndef _OPERACION_UI_CLIENTE_H_
#define _OPERACION_UI_CLIENTE_H_

#include <string>
#include <vector>
#include "Ventana.h"

using namespace std;

class OperacionUICliente
{
protected:
	vector<string> parametros;

	virtual bool ejecutarAccion(Ventana* ventana) = 0;

public:
	OperacionUICliente(void);
	virtual ~OperacionUICliente(void);

	virtual bool ejecutar(Ventana* ventana);
};

#endif
