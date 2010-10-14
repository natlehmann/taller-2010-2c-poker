#ifndef _OPUICLIENTE_SOLICITARESCENARIO_H_
#define _OPUICLIENTE_SOLICITARESCENARIO_H_

#include <string>
#include "OperacionUICliente.h"

using namespace std;

class OpUIClienteSolicitarEscenario : public OperacionUICliente
{
public:
	OpUIClienteSolicitarEscenario(void);
	virtual ~OpUIClienteSolicitarEscenario(void);

	virtual bool ejecutar(Ventana* ventana);
};

#endif
