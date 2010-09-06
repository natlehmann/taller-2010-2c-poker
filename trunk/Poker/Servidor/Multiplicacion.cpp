#include "Multiplicacion.h"
#include "UtilTiposDatos.h"

Multiplicacion::Multiplicacion() {}

Multiplicacion::Multiplicacion(string id, vector<double> parametros)
{
	this->id = id;
	this->parametros = parametros;
}

Multiplicacion::~Multiplicacion() {}

vector<Resultado> Multiplicacion::ejecutar()
{
	double resultadoOperacion = 0;
	vector<double>::iterator it = parametros.begin();
	if (it != parametros.end()) {
		resultadoOperacion = *it;
		it++;
		while (it != parametros.end()) {
			double factor = *it;
			resultadoOperacion *= factor;
			it++;
		}
	}
	string resultadoString = UtilTiposDatos::doubleToString(resultadoOperacion);

	Resultado resultado("mul",resultadoString,false,id);
	vector<Resultado> resultados;
	resultados.push_back(resultado);
	return resultados;
}
