#include "Resta.h"
#include "UtilTiposDatos.h"

Resta::Resta() {}

Resta::Resta(string id, vector<double> parametros)
{
	this->id = id;
	this->parametros = parametros;
}

Resta::~Resta() {}

vector<Resultado> Resta::ejecutar()
{
	double resultadoOperacion = 0;
	vector<double>::iterator it = parametros.begin();
	if (it != parametros.end()) {
		resultadoOperacion = *it;
		it++;
		while (it != parametros.end()) {
			double termino = *it;
			resultadoOperacion -= termino;
			it++;
		}
	}
	string resultadoString = UtilTiposDatos::doubleToString(resultadoOperacion);

	Resultado resultado("res",resultadoString,false,id);
	vector<Resultado> resultados;
	resultados.push_back(resultado);
	return resultados;
}
