#include "OpEnviarArchivo.h"
#include "Resultado.h"
#include "RecursosAplicacion.h"
#include "UtilTiposDatos.h"
#include "MensajesUtil.h"
#include <fstream>
#include <sstream>

OpEnviarArchivo::OpEnviarArchivo(vector<string> parametros){
	this->parametros = parametros;
}

OpEnviarArchivo::~OpEnviarArchivo(void){
}

bool OpEnviarArchivo::ejecutar(Socket* socket){

	bool error = false;

	//TODO: Ver el tema del tath de origende los archivos
	string pathOrigen = RecursosAplicacion::getServidorConfigProperties()->get("servidor.pathImagenes");
	string nombreArchivo = this->parametros.at(0);

	if (socket != NULL)
	{
		string msjRecibido;

		//genera el path completo
		string pathCompleto = pathOrigen;
		pathCompleto.append(nombreArchivo);

		//abre el archivo solicitado
		ifstream::pos_type size;
		ifstream file(pathCompleto.c_str(), ios::in | ios::binary | ios::ate);
		if (file.is_open())
		{
			//carga en memoria el archivo, y obtiene el tamanio
			size = file.tellg();
			char* memblock = new char [size];
			file.seekg (0, ios::beg);
			file.read (memblock, size);
			file.close();
			
			//envia el tamanio del archivo al cliente
			string sizeEntero = UtilTiposDatos::enteroAString(size);
			socket->enviar(sizeEntero);
			
			//si fue recibido ok por el cliente, envia el archivo
			if (socket->recibir(msjRecibido))
			{
				if (MensajesUtil::sonIguales(msjRecibido.data(), "OK"))
					socket->enviar(memblock, size);
			}

			delete[] memblock;
			
		}
		else 
		{
			RecursosAplicacion::getLogErroresServidor()->escribir(
				"No se puede abrir el archivo " + nombreArchivo + " para lectura.");
			
			string mjeError = "-1";
			socket->enviar(mjeError);
		}

	}

	return error;
}
