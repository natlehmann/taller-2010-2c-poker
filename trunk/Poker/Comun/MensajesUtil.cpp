#include "MensajesUtil.h"


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
char* MensajesUtil::toString(const T &arg)
{
	ostringstream	out;
	out << arg;
	return(out.str());
}
