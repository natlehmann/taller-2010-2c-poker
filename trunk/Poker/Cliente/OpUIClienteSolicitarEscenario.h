#ifndef _OPUICLIENTE_SOLICITARESCENARIO_H_
#define _OPUICLIENTE_SOLICITARESCENARIO_H_

#include <string>
#include "OperacionUICliente.h"

using namespace std;

class OpUIClienteSolicitarEscenario : public OperacionUICliente
{
protected:
	virtual bool ejecutarAccion(Ventana* ventana);

public:
	OpUIClienteSolicitarEscenario(void);
	virtual ~OpUIClienteSolicitarEscenario(void);
};

#endif
