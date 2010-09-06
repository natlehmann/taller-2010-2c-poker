#include "Suma.h"
#include "UtilTiposDatos.h"

Suma::Suma() {}

Suma::Suma(string id, vector<double> parametros)
{
	this->id = id;
	this->parametros = parametros;
}

Suma::~Suma() {}

vector<Resultado> Suma::ejecutar()
{
	double resultadoOperacion = 0;
	vector<double>::iterator it = parametros.begin();
	while (it != parametros.end()) {
		double termino = *it;
		resultadoOperacion += termino;
		it++;
	}
	string resultadoString = UtilTiposDatos::doubleToString(resultadoOperacion);

	Resultado resultado("sum",resultadoString,false,id);
	vector<Resultado> resultados;
	resultados.push_back(resultado);
	return resultados;
}
