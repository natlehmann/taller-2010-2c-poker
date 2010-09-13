#include "Division.h"
#include "UtilTiposDatos.h"

Division::Division() {}

Division::Division(string id, vector<double> parametros)
{
	this->id = id;
	this->parametros = parametros;
}

Division::~Division() {}

vector<Respuesta*> Division::ejecutar()
{
	vector<Respuesta*> resultados;

	if (parametros.size() != 2) {
		Error* resultadoError = new Error("E","cantidad de parametros incorrecta",id);
		resultados.push_back(resultadoError);
		return resultados;
	}

	double dividendo = parametros.at(0);
	double divisor = parametros.at(1);
	int cociente = 0;
	int resto = 0;

	if (divisor == 0) {

		Error* resultadoError = new Error("E","division por cero",id);
		resultados.push_back(resultadoError);

	} else {

		if (!UtilTiposDatos::esEntero(dividendo) || !UtilTiposDatos::esEntero(divisor)) {

			Error* resultadoError = new Error("E","parametros no enteros",id);
			resultados.push_back(resultadoError);

		} else {

			cociente = (int)dividendo / (int)divisor;
			resto = (int)dividendo % (int)divisor;

			string cocienteString = UtilTiposDatos::doubleAString(cociente);
			string restoString = UtilTiposDatos::doubleAString(resto);

			Resultado* resultadoCociente = new Resultado("coc",cocienteString,id);
			Resultado* resultadoResto = new Resultado("res",restoString,id);

			resultados.push_back(resultadoCociente);
			resultados.push_back(resultadoResto);

		}

	}

	return resultados;
}
