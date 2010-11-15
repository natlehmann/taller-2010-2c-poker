#ifndef _OP_GETCANTFICHAS_H_
#define _OP_GETCANTFICHAS_H_

#include "Operacion.h"

using namespace std;

class OpGetCantidadFichas : public Operacion
{
protected:
	virtual bool ejecutarAccion(Socket* socket);

public:
	OpGetCantidadFichas(int idCliente, vector<string> parametros);
	virtual ~OpGetCantidadFichas(void);
};

#endif //_OP_GETCANTFICHAS_H_

