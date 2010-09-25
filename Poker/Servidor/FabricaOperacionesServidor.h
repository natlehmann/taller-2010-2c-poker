#ifndef _FABRICAOPERACIONES_SERVIDOR_H_
#define _FABRICAOPERACIONES_SERVIDOR_H_

#include "Operacion.h"
#include "DomTree.h"
#include <vector>

using namespace std;

class FabricaOperacionesServidor {
public:
	FabricaOperacionesServidor();
	virtual ~FabricaOperacionesServidor();

	Operacion* newOperacion(DomTree* domTree);
	Operacion* newOperacion(string nombreOperacion);

private:
	void FabricaOperacionesServidor::validarParametro(Elemento* parametro, string idOperacion, int numeroDeParametro);
};

#endif /* _FABRICAOPERACIONES_SERVIDOR_H_ */
