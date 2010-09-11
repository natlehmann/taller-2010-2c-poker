#include "UtilTiposDatos.h"
#include <sstream>
#include <stdlib.h>

UtilTiposDatos::UtilTiposDatos() {}

UtilTiposDatos::~UtilTiposDatos() {}

string UtilTiposDatos::doubleToString(double numero) 
{
	ostringstream strs;
	strs << numero;
	string numeroString = strs.str();
	return numeroString;
}

double UtilTiposDatos::stringToDouble(string numero) 
{
	return atof(numero.c_str());
}

bool UtilTiposDatos::isInteger(double numero) 
{
	int parteEntera = (int)numero;
	double resta = numero - parteEntera;
	return (resta == 0);
}

bool UtilTiposDatos::isNumber(string numero)
{
	if (numero.size() < 1) {
		return 0;
	}
	if (numero.size() == 1) {
		return isdigit(numero[0]);
	}
	if (!isdigit(numero[0]) && numero[0] != '-') {
		return 0;
	}
	if (numero[0] == '-' && numero[1] == '.') {
		return 0;
	}
	bool esDecimal = false;
	for (unsigned int i = 1; i < numero.size(); i++) {
		if (!isdigit(numero[i]) && numero[i]!='.') {
			return 0;
		}
		if (numero[i]=='.') {
			if (!esDecimal) {
				esDecimal = true;
			} else {
				return 0;
			}
		}
	}
	return true;
}
