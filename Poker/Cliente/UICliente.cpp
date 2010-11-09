#include "SDL.h"
#include "SDL_ttf.h"
#include "UICliente.h"
#include "ParserEntradaTeclado.h"
#include "MensajesUtil.h"
#include "XmlParserArchivo.h"
#include "DomTree.h"
#include "GeneradorRespuesta.h"
#include "UtilTiposDatos.h"
#include "RecursosCliente.h"
#include "UIException.h"
#include "OperacionUICliente.h"
#include "FabricaOperacionesCliente.h"
#include "FabricaDeElementosGraficos.h"
#include "DomTreeFactory.h"
#include "Timer.h"
#include "Planificador.h"
#include <fstream>
#include <cstdlib>

Cliente* UICliente::cliente = NULL;
SDL_Thread* UICliente::threadRefresh = NULL;

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

	if( SDL_EnableUNICODE(1) == -1 ) {
		throw UIException("No se pudo inicializar la interfaz grafica.","E");
	}

    /* Enable auto repeat for keyboard input */
	if( SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL) == -1 ) {
		throw UIException("No se pudo inicializar la interfaz grafica.","E");
	}

	DomTreeFactory::inicializar();
	
	//UICliente::conectarServidor();

}


void UICliente::lanzarThreads(Ventana* ventana){

	int (*puntero)(void*) = &Planificador::planificarOperacion; 
	try {
		Planificador::setVentana(ventana);
		UICliente::threadRefresh = SDL_CreateThread(puntero, ventana);

	} catch (PokerException& e) {
		RecursosCliente::getLog()->escribir(&e.getError());
		UICliente::mostrarMensaje(
			"La aplicacion se ejecuto con errores. Por favor verifique el archivo 'errores.err'.", false);
	}
}

bool UICliente::conectarServidor()
{
	 return UICliente::conectarServidor("", 0);
}

bool UICliente::conectarServidor(string ip, int puerto)
{
	bool conecto = false;

	if (ip.length() == 0) 
		ip = RecursosCliente::getConfig()->get("cliente.conexion.ip");
	if (puerto == 0)
		puerto = UtilTiposDatos::getEntero(RecursosCliente::getConfig()->get("cliente.conexion.puerto"));

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

		RecursosCliente::getLog()->escribir(
			"No se puede establecer la conexion. O bien el servidor esta caido o la IP y puerto de conexion son incorrectos.");

		if (UICliente::cliente != NULL) {
			delete(UICliente::cliente);
			UICliente::cliente = NULL;
		}

		//exit(1);
	}

	return conecto;
}

Cliente* UICliente::getCliente(){
	return UICliente::cliente;
}

void UICliente::finalizar()
{
	Planificador::finalizar();

	if (UICliente::threadRefresh != NULL) {
		if (!Planificador::isFinalizado()) {
			SDL_WaitThread(UICliente::threadRefresh,NULL);
		}
		//SDL_KillThread(UICliente::threadRefresh);
	}

	SDL_Quit();
	TTF_Quit(); 

	DomTreeFactory::finalizar();

	UICliente::cliente->finalizarConexion();
}


void UICliente::mostrarMensaje(string msg, bool ingresaDatos)
{
	std::cout << msg;

	if (!ingresaDatos){
		std::cout << std::endl;
	}
}
