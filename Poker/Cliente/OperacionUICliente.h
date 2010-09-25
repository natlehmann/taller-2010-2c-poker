#ifndef _OPERACION_UI_CLIENTE_H_
#define _OPERACION_UI_CLIENTE_H_

#include <string>

using namespace std;

class OperacionUICliente
{
public:
	OperacionUICliente(void);
	virtual ~OperacionUICliente(void);

	// TODO: Por parametro recibe la Ventana
	virtual void ejecutar() = 0;
};

#endif
