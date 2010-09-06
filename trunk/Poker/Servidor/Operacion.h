#ifndef OPERACION_H_
#define OPERACION_H_

#include "Resultado.h"
#include <string>
#include <vector>

using namespace std;


class Operacion {

protected:
	string id;
	vector<double> parametros;

public:
	Operacion();
	virtual ~Operacion();

    string getId() const
    {
        return id;
    }

    void setId(string id)
    {
        this->id = id;
    }

    vector<double> getParametros() const
    {
        return parametros;
    }

    void setParametros(vector<double> parametros)
    {
        this->parametros = parametros;
    }

    virtual vector<Resultado> ejecutar() = 0;

};

#endif /* OPERACION_H_ */
