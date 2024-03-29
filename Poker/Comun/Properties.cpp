#include "Properties.h"
#include "FileException.h"
#include "MensajesUtil.h"

Properties::Properties(string nombreArchivo)
{
	this->properties = NULL;
	this->nombreArchivo = "";

	this->setNombreArchivo(nombreArchivo);
}

Properties::~Properties(void)
{
	if (this->archivo != NULL) {
		delete(this->archivo);
	}

	if (this->properties != NULL) {

		this->properties->erase(this->properties->begin(), this->properties->end());
		this->properties->clear();
		delete (this->properties);
	}
}

void Properties::setNombreArchivo(string nombreArchivo) {

	if (this->nombreArchivo.empty()) {

		this->nombreArchivo = nombreArchivo;

		this->archivo = new ifstream(this->nombreArchivo.c_str());

		if (!*this->archivo){
			delete(this->archivo);
			this->archivo = NULL;
			throw FileException("No se puede abrir el archivo " + this->nombreArchivo, "E");
		}	

		delete(this->archivo);
		this->archivo = NULL;
	}
}

string Properties::get(string clave){

	string resultado = "";

	if (this->properties == NULL) {
		this->inicializar();
	}

	map<string,string>::iterator it = this->properties->find(clave);

	if (it != this->properties->end()) {
		resultado = it->second;

	}

	return resultado;
}

void Properties::inicializar() {	

	this->properties = new map<string,string>();
	this->archivo = new ifstream(this->nombreArchivo.c_str());

	bool finArchivo = false;
	while (!finArchivo) {

		string linea;
		getline(*this->archivo,linea);

		if (this->archivo->eof()) {
			finArchivo = true;
		}

		if (this->archivo->bad()) {
			throw FileException("Se produjo un error de lectura en el archivo " 
				+ this->nombreArchivo, "E");
		}
	
		this->procesarLinea(linea);
	}

	this->archivo->close();
	delete(this->archivo);
	this->archivo = NULL;
}

void Properties::procesarLinea(string linea) {

	bool esComentario = false;

	unsigned int indiceComentario = linea.find_first_of(PROP_COMENTARIO);
	if (indiceComentario != string::npos) {
		string anterior = linea.substr(0, indiceComentario);
		anterior.erase(indiceComentario);
		if (MensajesUtil::esVacio(anterior)) {
			esComentario = true;
		}
	}

	if (!esComentario) {

		unsigned int indice = linea.find_first_of(PROP_SEPARADOR);

		// si la linea no contiene el signo igual se descarta
		if (indice != string::npos) {	
		
			string clave = linea.substr(0, indice);
			clave.erase(indice);
			clave = MensajesUtil::trim(clave);

			string valor = linea.substr(indice + string(PROP_SEPARADOR).size());
			valor = MensajesUtil::trim(valor);

			this->properties->insert(pair<string,string>(clave,valor));
		}
	}
}
