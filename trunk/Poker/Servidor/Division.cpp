#include "Division.h"
#include "UtilTiposDatos.h"

Division::Division() {}

Division::Division(string id, vector<double> parametros)
{
	this->id = id;
	this->parametros = parametros;
}

Division::~Division() {}

vector<Resultado> Division::ejecutar()
{
	vector<Resultado> resultados;

	if (parametros.size() != 2) {
		Resultado resultadoError("E","cantidad de parametros incorrecta",true,id);
		resultados.push_back(resultadoError);
		return resultados;
	}

	double dividendo = parametros.at(0);
	double divisor = parametros.at(1);
	int cociente = 0;
	int resto = 0;

	if (divisor == 0) {

		Resultado resultadoError("E","division por cero",true,id);
		resultados.push_back(resultadoError);

	} else {

		if (!UtilTiposDatos::isInteger(dividendo) || !UtilTiposDatos::isInteger(divisor)) {

			Resultado resultadoError("E","parametros no enteros",true,id);
			resultados.push_back(resultadoError);

		} else {

			cociente = (int)dividendo / (int)divisor;
			resto = (int)dividendo % (int)divisor;

			string cocienteString = UtilTiposDatos::doubleToString(cociente);
			string restoString = UtilTiposDatos::doubleToString(resto);

			Resultado resultadoCociente("coc",cocienteString,false,id);
			Resultado resultadoResto("res",restoString,false,id);

			resultados.push_back(resultadoCociente);
			resultados.push_back(resultadoResto);

		}

	}

	return resultados;
}
