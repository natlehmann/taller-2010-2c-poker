#include "OpEnviarEscenario.h"
#include "Resultado.h"
#include "RecursosServidor.h"
#include "ContextoJuego.h"
#include "MensajesUtil.h"
#include <fstream>

OpEnviarEscenario::OpEnviarEscenario(int idCliente) : Operacion(idCliente) {
}

OpEnviarEscenario::~OpEnviarEscenario(void){
}

bool OpEnviarEscenario::ejecutarAccion(Socket* socket){
cout << "Enviando escenario a cliente " << this->getIdCliente() << endl;
/*
	bool error = false;
	Resultado* resultado = new Resultado();
	string contenido = "";

	string nombreArchivo = RecursosServidor::getConfig()->get("servidor.archivoEscenario");
	ifstream archivo(nombreArchivo.c_str());

	if (!archivo)
	{
		resultado->setValor(contenido);
		RecursosServidor::getLog()->escribir(
			"No se puede abrir el archivo " + nombreArchivo + " para lectura.");
	
	} 
	else 
	{
		while (!archivo.eof()) {

			string linea;
			getline(archivo,linea);
			contenido = contenido + linea + "\n";
		}

		archivo.close();

		resultado->setValor(contenido);
		resultado->setIdOperacion("OpEnviarEscenario");
	}

	if (socket != NULL && resultado!= NULL){
		string respuesta = resultado->getValor();
		if(!socket->enviar(respuesta))
			error = true;
	}
	else
		error = true;

	return error;
*/


	bool error = false;

	string respuesta = ContextoJuego::getInstancia()->getEscenarioJuego(this->getIdCliente());

	if (socket != NULL && !MensajesUtil::esVacio(respuesta)){
		if(!socket->enviar(respuesta)) {
			error = true;
		}
	}
	else {
		error = true;
	}

	return error;
}
