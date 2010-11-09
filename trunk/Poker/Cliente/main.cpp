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
#include "VentanaConfiguracion.h"
#include "Sincronizador.h"


int main (int argc, char** argv)
{
	VentanaConfiguracion* ventanaConfiguracion = NULL;
	OperacionUICliente* operacion = NULL;
	Ventana* ventana = NULL;

	try {

		UICliente::iniciarAplicacion();

		ventanaConfiguracion = new VentanaConfiguracion();
		ventanaConfiguracion->iniciar();

		if (ventanaConfiguracion->getConectado()) {

			string idOperacionInicial = RecursosCliente::getConfig()->get("cliente.operacion.inicial");
			FabricaOperacionesCliente fab;

			ventana = new VentanaImpl();
			Sincronizador::getInstancia()->registrarVentana(ventana);

			UICliente::lanzarThreads(ventana);

			/* Prueba envio de la solicitud de logueo */
			/*vector<string> parametros;
			parametros.push_back("Jose89");
			parametros.push_back("xxx");
			parametros.push_back("S");
			parametros.push_back("N");
			operacion = fab.newOperacion(idOperacionInicial, parametros);*/

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
		}

		delete (ventanaConfiguracion);
		ventanaConfiguracion = NULL;

	} catch (PokerException& e) {

		RecursosCliente::getLog()->escribir(&e.getError());
		UICliente::mostrarMensaje(
			"La aplicacion se ejecuto con errores. Por favor verifique el archivo 'errores.err'.", false);

		if (ventanaConfiguracion != NULL) {
			delete(ventanaConfiguracion);
		}
		if (operacion != NULL) {
			delete(operacion);
		}
		if (ventana != NULL) {
			delete(ventana);
		}
	}

	return 0;

}
