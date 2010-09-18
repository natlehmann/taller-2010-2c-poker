#ifndef RESULTADO_H_
#define RESULTADO_H_

#include <string>
#include "Respuesta.h"

using namespace std;


class Resultado : public Respuesta {

public:
	Resultado();
	Resultado(string id, string valor, string idOperacion);
	virtual ~Resultado();

};

#endif /* RESULTADO_H_ */
