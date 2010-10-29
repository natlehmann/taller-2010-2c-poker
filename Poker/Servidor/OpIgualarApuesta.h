#ifndef _OP_IGUALARAPUESTA_H_
#define _OP_IGUALARAPUESTA_H_

#include "Operacion.h"

using namespace std;

class OpIgualarApuesta : public Operacion
{
protected:
	virtual bool ejecutarAccion(Socket* socket);

public:
	OpIgualarApuesta(int idCliente);
	virtual ~OpIgualarApuesta(void);
};

#endif //_OP_IGUALARAPUESTA_H_

