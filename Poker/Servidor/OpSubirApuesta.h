#ifndef _OP_SUBIRAPUESTA_H_
#define _OP_SUBIRAPUESTA_H_

#include "Operacion.h"

using namespace std;

class OpSubirApuesta : public Operacion
{
protected:
	virtual bool ejecutarAccion(Socket* socket);

public:
	OpSubirApuesta(int idCliente, vector<string> parametros);
	virtual ~OpSubirApuesta(void);
};

#endif //_OP_SUBIRAPUESTA_H_
