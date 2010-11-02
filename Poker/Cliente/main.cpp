#include "SDL.h" 
#include <vld.h>
#include "RecursosCliente.h"
#include "UICliente.h"
#include "FabricaOperacionesCliente.h"
#include "OperacionUICliente.h"
#include "PokerException.h"
#include "Respuesta.h"
#include "VentanaProxy.h"
#include "VentanaImpl.h"
#include "Sincronizador.h"


int main (int argc, char** argv)
{
	OperacionUICliente* operacion = NULL;
	Ventana* ventana = NULL;

	try {
		UICliente::iniciarAplicacion();

		string idOperacionInicial = 
			RecursosCliente::getConfig()->get("cliente.operacion.inicial");
		FabricaOperacionesCliente fab;

		//ventana = new VentanaProxy();
		ventana = new VentanaImpl();
		Sincronizador::getInstancia()->registrarVentana(ventana);

		UICliente::lanzarThreads(ventana);

		operacion = fab.newOperacion(idOperacionInicial);
		if (operacion->ejecutar(ventana)){

			ventana->iniciar();

		} else {
			UICliente::mostrarMensaje(
				"La aplicacion se ejecuto con errores. Por favor verifique el archivo 'errores.err'.", false);
		}

		UICliente::finalizar();

		delete(operacion);
		operacion = NULL;
		delete(ventana);
		ventana = NULL;

		delete(Sincronizador::getInstancia());
		


	} catch (PokerException& e) {

		RecursosCliente::getLog()->escribir(&e.getError());
		UICliente::mostrarMensaje(
			"La aplicacion se ejecuto con errores. Por favor verifique el archivo 'errores.err'.", false);
		if (operacion != NULL) {
			delete(operacion);
		}
		if (ventana != NULL) {
			delete(ventana);
		}
	}

	return 0;

}
