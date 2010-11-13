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
#include "VentanaLogin.h"
#include "VentanaNuevoJugador.h"
#include "VentanaAdministracion.h"
#include "VentanaEstadisticas.h"
#include "Sincronizador.h"


int main (int argc, char** argv)
{
	VentanaConfiguracion* ventanaConfiguracion = NULL;
	VentanaLogin* ventanaLogin = NULL;
	VentanaNuevoJugador* ventanaNuevoJugador = NULL;
	VentanaAdministracion* ventanaAdministracion = NULL;
	VentanaEstadisticas* ventanaEstadisticas = NULL;
	OperacionUICliente* operacion = NULL;
	Ventana* ventana = NULL;

	try {

		ventanaConfiguracion = new VentanaConfiguracion();
		ventanaConfiguracion->iniciar();

		if (ventanaConfiguracion->getConectado()) {
				
			UICliente::iniciarAplicacion();
			
			bool sigueLogin = true;
			while (sigueLogin) {
				ventanaLogin = new VentanaLogin();
				ventanaLogin->iniciar();

				if (ventanaLogin->getNuevo())
				{
					delete(ventanaLogin);
					ventanaLogin = NULL;

					//se debe llamar a la pantalla de creacion de usuario, y despues vuelve al login (sigue = true)
					ventanaNuevoJugador = new VentanaNuevoJugador();
					ventanaNuevoJugador->iniciar();

					if (ventanaNuevoJugador->getGuardado())
						sigueLogin = true;
					else if (ventanaNuevoJugador->getCancelado())
						sigueLogin = true;

					delete(ventanaNuevoJugador);
					ventanaNuevoJugador = NULL;
				}
				else 
					//en el caso de logueo o de cancel sale del ciclo
					sigueLogin = false;

			}

			if (ventanaLogin->getConectado()) {

				bool sigueAdministracion = true;
				while (sigueAdministracion) {

					ventanaAdministracion = new VentanaAdministracion(ventanaLogin->getUsuario(), 
																	  ventanaLogin->getSesionId(), 
																	  ventanaLogin->getCantFichas());
					ventanaAdministracion->iniciar();

					if (ventanaAdministracion->getVerEstadisticas())
					{
						ventanaEstadisticas = new VentanaEstadisticas(ventanaAdministracion->getUsuario(), 
																	  ventanaAdministracion->getSesionId());
						ventanaEstadisticas->iniciar();

						if (ventanaEstadisticas->getConsulto() || ventanaEstadisticas->getCancelado())
							sigueAdministracion = true;
						else 
							sigueAdministracion = true;

						delete(ventanaNuevoJugador);
						ventanaNuevoJugador = NULL;

						delete(ventanaAdministracion);
						ventanaAdministracion = NULL;
					
					}
					else if (ventanaAdministracion->getIrMesa())
					{
						delete(ventanaAdministracion);
						ventanaAdministracion = NULL;

						UICliente::iniciarSDL();

						string idOperacionInicial = RecursosCliente::getConfig()->get("cliente.operacion.inicial");
						FabricaOperacionesCliente fab;

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
					}
					else if (ventanaAdministracion->getCancelado()) {
						sigueAdministracion = false;
					}
				}

				delete(ventanaAdministracion);
				ventanaAdministracion = NULL;

			}

			delete (ventanaLogin);
			ventanaLogin = NULL;

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
		if (ventanaLogin != NULL) {
			delete(ventanaLogin);
		}
		if (ventanaNuevoJugador != NULL) {
			delete(ventanaNuevoJugador);
		}
		if (ventanaAdministracion == NULL) {
			delete(ventanaAdministracion);
		}
		if (ventanaEstadisticas == NULL) {
			delete(ventanaEstadisticas);
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
