#ifndef _OP_MOSTRARMENSAJE_H_
#define _OP_MOSTRARMENSAJE_H_

#include "Operacion.h"

using namespace std;

class OpMostrarMensaje : public Operacion
{
protected:
	virtual bool ejecutarAccion(Socket* socket);

public:
	OpMostrarMensaje(int idCliente, vector<string> parametros);
	virtual ~OpMostrarMensaje(void);
};

#endif //_OP_MOSTRARMENSAJE_H_

