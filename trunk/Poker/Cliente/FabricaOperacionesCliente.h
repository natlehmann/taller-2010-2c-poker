#ifndef _FABRICAOPERACIONES_CLIENTE_H_
#define _FABRICAOPERACIONES_CLIENTE_H_

#include "OperacionUICliente.h"
#include <vector>

using namespace std;

class FabricaOperacionesCliente {

public:
	FabricaOperacionesCliente();
	virtual ~FabricaOperacionesCliente();

	OperacionUICliente* newOperacion(string nombreOperacion);
	OperacionUICliente* newOperacion(string nombreOperacion, string parametro);
	OperacionUICliente* newOperacion(string nombreOperacion, vector<string> parametros);

};

#endif /* _FABRICAOPERACIONES_CLIENTE_H_ */
