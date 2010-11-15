#include "MensajesUtil.h"
#include "FormatException.h"
#include <sys/stat.h> 

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
	if (texto.size() > 0) {
		unsigned int index = texto.find_first_not_of(" \n\t");
		if (index != string::npos) {
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

list<string> MensajesUtil::split(string texto, string separador){

	list<string> resultado;
	unsigned int inicial = 0;
	unsigned int final = texto.find_first_of(separador, inicial);
	bool terminado = false;

	while (!terminado) {

		if (final == string::npos) {
			final = texto.size();
			terminado = true;
		}

		string fragmento = texto.substr(inicial, final);
		fragmento.erase(final - inicial);
		fragmento = MensajesUtil::trim(fragmento);

		if (!MensajesUtil::esVacio(fragmento)) {
			resultado.push_back(fragmento);
		}

		if (!terminado) {
			inicial = final + separador.size();
			final = texto.find_first_of(separador, inicial);
		}
	}

	return resultado;
}


set<string*>* MensajesUtil::splitToSet(string texto, string separador){

	set<string*>* resultado = new set<string*>();
	unsigned int inicial = 0;
	unsigned int final = texto.find_first_of(separador, inicial);
	bool terminado = false;

	while (!terminado) {

		if (final == string::npos) {
			final = texto.size();
			terminado = true;
		}

		string fragmento = texto.substr(inicial, final);
		fragmento.erase(final - inicial);
		fragmento = MensajesUtil::trim(fragmento);

		if (!MensajesUtil::esVacio(fragmento)) {
			resultado->insert(new string(fragmento));
		}

		if (!terminado) {
			inicial = final + separador.size();
			final = texto.find_first_of(separador, inicial);
		}
	}

	return resultado;
}


list<string> MensajesUtil::split(string texto){
	return MensajesUtil::split(texto, ",");
}

set<string*>* MensajesUtil::splitToSet(string texto){
	return MensajesUtil::splitToSet(texto, ",");
}

bool MensajesUtil::FileExists(string strFilename) { 
  struct stat stFileInfo; 
  bool exists = true; 
  int intStat; 

  // Attempt to get the file attributes 
  intStat = stat(strFilename.c_str(),&stFileInfo); 
  if(intStat != 0) 
  { 
    // We were not able to get the file attributes. 
    // This may mean that we don't have permission to 
    // access the folder which contains this file. If you 
    // need to do that level of checking, lookup the 
    // return values of stat which will give you 
    // more details on why stat failed. 
    exists = false; 
  } 
   
  return exists; 
}

