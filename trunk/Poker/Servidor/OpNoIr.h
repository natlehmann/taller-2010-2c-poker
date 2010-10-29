#ifndef _OP_NOIR_H_
#define _OP_NOIR_H_

#include "Operacion.h"

using namespace std;

class OpNoIr : public Operacion
{
protected:
	virtual bool ejecutarAccion(Socket* socket);

public:
	OpNoIr(int idCliente);
	virtual ~OpNoIr(void);
};

#endif //_OP_NOIR_H_

