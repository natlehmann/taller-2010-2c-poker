#ifndef FABRICAOPERACIONES_H_
#define FABRICAOPERACIONES_H_

#include "Operacion.h"
#include "DomTree.h"
#include <vector>

using namespace std;

class FabricaOperaciones {
public:
	FabricaOperaciones();
	virtual ~FabricaOperaciones();
	Operacion* newOperacion(DomTree* domTree);

private:
	void FabricaOperaciones::validarParametro(Elemento* parametro, string idOperacion, int numeroDeParametro);
};

#endif /* FABRICAOPERACIONES_H_ */
