#ifndef MULTIPLICACION_H_
#define MULTIPLICACION_H_

#include "Operacion.h"

class Multiplicacion: public Operacion {
public:
	Multiplicacion();
	Multiplicacion(string id, vector<double> parametros);
	virtual ~Multiplicacion();
	vector<Resultado> ejecutar();
};

#endif /* MULTIPLICACION_H_ */
