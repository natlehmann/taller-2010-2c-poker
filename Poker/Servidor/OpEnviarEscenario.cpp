#include "OpEnviarEscenario.h"
#include "Resultado.h"
#include "RecursosAplicacion.h"
#include <fstream>

OpEnviarEscenario::OpEnviarEscenario(void){
}

OpEnviarEscenario::~OpEnviarEscenario(void){
}

bool OpEnviarEscenario::ejecutar(Socket* socket){
	bool error = false;
	Resultado* resultado = NULL;

	string nombreArchivo = RecursosAplicacion::getServidorConfigProperties()->get("servidor.archivoEscenario");
	ifstream archivo(nombreArchivo.c_str());

	if (!archivo){
		RecursosAplicacion::getLogErroresServidor()->escribir(
			"No se puede abrir el archivo " + nombreArchivo + " para lectura.");
	
	} else {
	
		resultado = new Resultado();
		string contenido = "";

		while (!archivo.eof()) {

			string linea;
			getline(archivo,linea);
			contenido = contenido + linea + "\n";
		}

		archivo.close();

		resultado->setValor(contenido);
		resultado->setIdOperacion("OpEnviarEscenario");
	}

	if (socket != NULL){
		string respuesta = resultado->getValor();
		if(!socket->enviar(respuesta))
			error = true;
	}
	else
		error = true;

	return error;	
}
