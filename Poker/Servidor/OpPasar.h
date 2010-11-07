#ifndef _OP_PASAR_H_
#define _OP_PASAR_H_

#include "Operacion.h"

using namespace std;

class OpPasar : public Operacion
{
protected:
	virtual bool ejecutarAccion(Socket* socket);

public:
	OpPasar(int idCliente);
	virtual ~OpPasar(void);
};

#endif //_OP_PASAR_H_

