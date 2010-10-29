#ifndef _OP_DEJARMESA_H_
#define _OP_DEJARMESA_H_

#include "Operacion.h"

using namespace std;

class OpDejarMesa : public Operacion
{
protected:
	virtual bool ejecutarAccion(Socket* socket);

public:
	OpDejarMesa(int idCliente);
	virtual ~OpDejarMesa(void);
};

#endif //_OP_DEJARMESA_H_

