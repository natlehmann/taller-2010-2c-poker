#ifndef RESTA_H_
#define RESTA_H_

#include "Operacion.h"

class Resta: public Operacion {
public:
	Resta();
	Resta(string id, vector<double> parametros);
	virtual ~Resta();
	vector<Resultado> ejecutar();
};

#endif /* RESTA_H_ */
