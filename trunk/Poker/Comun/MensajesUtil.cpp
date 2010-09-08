#include "MensajesUtil.h"
#include "FormatException.h"


string MensajesUtil::concatMensaje(char* partes[]){

	int longitud = 0;
	bool terminado = false;
	int i = 0;

	while(!terminado) {

		if (strcmp(partes[i], "\0") == 0) {
			terminado = true;
		} else {
			longitud += strlen(partes[i]);
		}
		i++;
	}

	char* resultado = new char[longitud + 1];
	terminado = false;

	strcpy(resultado, partes[0]);
	i = 1;

	while(!terminado) {
		if (strcmp(partes[i], "\0") == 0) {
			terminado = true;
		} 
		strcat(resultado, partes[i]);
		i++;
	}

	return resultado;
}

bool MensajesUtil::sonIguales(string primero, string segundo) {
	bool iguales = false;
	if (primero.size() == segundo.size()) {
		iguales = equal(primero.begin(), primero.end(), segundo.begin());
	}
	return iguales;
}


template < class T >
string MensajesUtil::toString(const T &arg)
{
	ostringstream	out;
	out << arg;
	return(string(out.str()));
}

bool MensajesUtil::esVacio(string texto) {
	bool vacio = true;
	for (unsigned int i = 0; i < texto.size(); i++) {
		if (texto.at(i) != ' ') {
			vacio = false;
		}
	}
	return vacio;
}

string MensajesUtil::trim(string texto) {

	if (!MensajesUtil::esVacio(texto)) {
		unsigned int inicio = texto.find_first_not_of(" \t\n");
		unsigned int fin = texto.find_last_not_of(" \t\n");

		string resultado = texto.substr(inicio, fin +1);
		resultado.erase((fin + 1) - inicio);

		return resultado;

	} else {
		return "";
	}
}


string MensajesUtil::intToString(int value) {
	char buffer[50];
	int resultado = sprintf(buffer,"%d",value);
	if (resultado <= 0) {
		throw FormatException("No se puede convertir el valor a string.");
	}
	 return string(buffer);
}

