#include "Resta.h"
#include "UtilTiposDatos.h"

Resta::Resta() {}

Resta::Resta(string id, vector<double> parametros)
{
	this->id = id;
	this->parametros = parametros;
}

Resta::~Resta() {}

vector<Respuesta*> Resta::ejecutar()
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

	Resultado* resultado = new Resultado("res",resultadoString,id);
	vector<Respuesta*> resultados;
	resultados.push_back(resultado);
	return resultados;
}
