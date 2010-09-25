#include "Log.h"
#include "MensajesUtil.h"

#include <cstdlib>
#include <time.h>



Log::Log(string nombreArchivo) {
	this->nombreArchivo = nombreArchivo;
	this->archivo = new ofstream(nombreArchivo.c_str(), ios::out | ios::app);

	if (MensajesUtil::esVacio(nombreArchivo) || !archivo->is_open()) {
		cout << "No se ha podido abrir el archivo " + nombreArchivo + " para escritura." << endl;
		exit(1);
	}
}

Log::~Log(void) {
	this->archivo->close();
	delete(this->archivo);
}

void Log::escribir(Respuesta* respuesta) {

	// TODO: VER SI ES NECESARIO QUE SE ESCRIBA CON FORMATO XML
	*(this->archivo) << this->getFecha() << ": (" << respuesta->getId() << ") " 
			<<  respuesta->getValor() << endl;
}

void Log::escribir(string mensaje) {

	// TODO: VER SI ES NECESARIO QUE SE ESCRIBA CON FORMATO XML
	*(this->archivo) << this->getFecha() << ": " << mensaje << endl;
}

string Log::getFecha(){
	
	time_t rawtime;
	time ( &rawtime );
	string fecha = string(ctime(&rawtime));

	unsigned int fin = fecha.find("\n");
	fecha = fecha.substr(0, fin);
	fecha.erase(fin);

	return fecha;
}
 

