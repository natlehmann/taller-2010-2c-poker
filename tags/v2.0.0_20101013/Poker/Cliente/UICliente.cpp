#include "SDL.h"
#include "SDL_ttf.h"
#include "UICliente.h"
#include "ParserEntradaTeclado.h"
#include "MensajesUtil.h"
#include "XmlParserArchivo.h"
#include "DomTree.h"
#include "GeneradorRespuesta.h"
#include "UtilTiposDatos.h"
#include "RecursosAplicacion.h"
#include "UIException.h"
#include <fstream>
#include <cstdlib>

Cliente* UICliente::cliente = NULL;

UICliente::UICliente(void)
{
}

UICliente::~UICliente(void)
{
	if (cliente != NULL) {
		delete (this->cliente);
	}
}



void UICliente::iniciarAplicacion()
{
	if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 ) {
		throw UIException("No se pudo inicializar la interfaz grafica.","E");
	}

	if( TTF_Init() == -1 ) {
		throw UIException("No se pudo inicializar la interfaz grafica.","E");
	}
	
	UICliente::conectarServidor();
}


bool UICliente::conectarServidor()
{
	bool conecto = false;

	string ip = RecursosAplicacion::getClienteConfigProperties()->get("cliente.conexion.ip");
	int puerto = UtilTiposDatos::getEntero(
			RecursosAplicacion::getClienteConfigProperties()->get("cliente.conexion.puerto"));

	if (puerto > 0)  
	{
		mostrarMensaje("INTENTANDO CONECTAR CON EL SERVIDOR " + ip + " ...", false);
		
		if (UICliente::cliente != NULL)
		{
			if (UICliente::cliente->estaConectado())
				UICliente::cliente->finalizarConexion();

			delete(UICliente::cliente);
			UICliente::cliente = NULL;
		}

		UICliente::cliente = new Cliente(puerto, ip);
		conecto = UICliente::cliente->iniciarConexion();
	}

	if (!conecto || puerto <= 0) {

		mostrarMensaje("NO SE HA PODIDO ESTABLECER LA CONEXION CON EL SERVIDOR, INTENTELO MAS TARDE.", false);

		if (UICliente::cliente->estaConectado())
			UICliente::cliente->finalizarConexion();

		RecursosAplicacion::getLogErroresCliente()->escribir(
			"No se puede establecer la conexion. O bien el servidor esta caido o la IP y puerto de conexion son incorrectos.");

		if (UICliente::cliente != NULL) {
			delete(UICliente::cliente);
		}

		exit(1);
	}

	return conecto;
}

Cliente* UICliente::getCliente(){
	return UICliente::cliente;
}

void UICliente::finalizar()
{
	SDL_Quit();
	TTF_Quit(); 
	UICliente::cliente->finalizarConexion();
}


void UICliente::mostrarMensaje(string msg, bool ingresaDatos)
{
	std::cout << msg;

	if (!ingresaDatos){
		std::cout << std::endl;
	}
}
