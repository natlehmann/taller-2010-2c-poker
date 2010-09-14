#include "UtilTiposDatos.h"
#include <sstream>
#include <stdlib.h>


UtilTiposDatos::UtilTiposDatos() {}

UtilTiposDatos::~UtilTiposDatos() {}

string UtilTiposDatos::doubleAString(double numero) 
{
	// Esto se hace para el caso en que numero sea -0, 
	// para que no lo formatee con signo.
	numero = numero == 0 ? 0 : numero;
	ostringstream strs;
	strs << numero;
	string numeroString = strs.str();
	return numeroString;
}

double UtilTiposDatos::stringADouble(string numero) 
{
	double valor = atof(numero.c_str());
	return valor == 0 ? 0 : valor;
}

bool UtilTiposDatos::esEntero(double numero) 
{
	int parteEntera = (int)numero;
	double resta = numero - parteEntera;
	return (resta == 0);
}

bool UtilTiposDatos::esEntero(string numero) 
{
	if (numero.size() < 1) {
		return false;
	}
	if (numero.size() == 1) {
		return esDigito(numero[0]);
	}
	if (!esDigito(numero[0]) && numero[0] != '-') {
		return false;
	}
	for (unsigned int i = 1; i < numero.size(); i++) {
		if (!esDigito(numero[i])) {
			return false;
		}
	}
	return true;
}

int UtilTiposDatos::getEntero(string valor)
{
	int resul = -1;
	unsigned int indice = 0;
	unsigned int longitudString = valor.length();
	bool salir = false;
	
	if (longitudString > 0)
	{
		while((indice < longitudString) && !(salir))
		{
			if (esDigito(valor[indice]))
				indice += 1;
			else
				salir = true;
		}
	}

	if (!salir)
		resul = atoi(valor.data());
	
	return resul;
};

bool UtilTiposDatos::esDouble(string valor)
{
	unsigned int indice = 0;
	unsigned int longitudString = valor.length();
	bool encontroPunto = false;
	bool negativo = false;
	bool salir = false;
	bool resul = false;
	
	if (longitudString > 0)
	{
		if (valor[indice] == _MENOS_)
		{
			if (longitudString != 1)
			{
				negativo = true;
				indice += 1;					
			}
			else
				salir = false;
		}

		while((indice < longitudString) && !(salir))
		{
			if (esDigito(valor[indice]))
				indice += 1;
			else 
				if ((valor[indice]== _PUNTO_)&&(!encontroPunto)&&(longitudString>indice+1))
				{						
					encontroPunto = true;
					indice += 1;
				}
				else
					salir = true;
		}
	}

	if (!salir)
		resul = true;
	
	return resul;
};

bool UtilTiposDatos::validarSiNo(string valor)
{
	bool resul = false;

	if ((valor == _SI_) || (valor == _NO_)||(valor == _si_) || (valor == _no_))
		resul = true;

	return resul;
}

bool UtilTiposDatos::esDigito(int caracter) 
{
	return (caracter >= 48 && caracter <= 57);
}
