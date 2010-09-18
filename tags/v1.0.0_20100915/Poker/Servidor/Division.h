#ifndef DIVISION_H_
#define DIVISION_H_

#include "Operacion.h"

class Division: public Operacion {
public:
	Division();
	Division(string id, vector<double> parametros);
	virtual ~Division();
	vector<Respuesta*> ejecutar();
};

#endif /* DIVISION_H_ */
