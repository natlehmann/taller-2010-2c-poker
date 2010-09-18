#ifndef SUMA_H_
#define SUMA_H_

#include "Operacion.h"

class Suma: public Operacion {
public:
	Suma();
	Suma(string id, vector<double> parametros);
	virtual ~Suma();
	vector<Respuesta*> ejecutar();
};

#endif /* SUMA_H_ */
