#ifndef _FABRICAOPERACIONES_CLIENTE_H_
#define _FABRICAOPERACIONES_CLIENTE_H_

#include "OperacionUICliente.h"

using namespace std;

class FabricaOperacionesCliente {

public:
	FabricaOperacionesCliente();
	virtual ~FabricaOperacionesCliente();

	OperacionUICliente* newOperacion(string nombreOperacion);

};

#endif /* _FABRICAOPERACIONES_CLIENTE_H_ */
