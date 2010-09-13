#include "Division.h"
#include "UtilTiposDatos.h"
#include "DatosInvalidosException.h"

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

	double dividendo = parametros.at(0);
	double divisor = parametros.at(1);
	int cociente = 0;
	int resto = 0;

	if (divisor == 0) {

		Error resultadoError("E","Division por cero.",id);
		throw DatosInvalidosException(resultadoError);

	} else {

		if (!UtilTiposDatos::esEntero(dividendo) || !UtilTiposDatos::esEntero(divisor)) {

			Error resultadoError("E","Parametros no enteros.",id);
			throw DatosInvalidosException(resultadoError);

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
