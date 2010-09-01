#include "MensajesUtil.h"


char* MensajesUtil::concatMensaje(char* partes[]){

	int longitud = 0;
	bool terminado = false;
	int i = 0;

	while(!terminado) {
		if (partes[i] == "\0") {
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
		if (partes[i] == "\0") {
			terminado = true;
		} 
		strcat(resultado, partes[i]);
		i++;
	}

	return resultado;
}


template < class T >
char* MensajesUtil::toString(const T &arg)
{
	ostringstream	out;
	out << arg;
	return(out.str());
}
