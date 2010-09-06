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
