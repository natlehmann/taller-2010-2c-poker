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
#include "VentanaEstadistica.h"
#include "Sincronizador.h"
#include "OpUIClienteAgregarJugador.h"
#include "OpUIClienteGetCantFichas.h"
#include "DomTreeFactory.h"
#include <vector>


int main (int argc, char** argv)
{
	VentanaConfiguracion* ventanaConfiguracion = NULL;
	VentanaLogin* ventanaLogin = NULL;
	VentanaNuevoJugador* ventanaNuevoJugador = NULL;
	VentanaAdministracion* ventanaAdministracion = NULL;
	VentanaEstadistica* ventanaEstadistica = NULL;
	OperacionUICliente* operacion = NULL;
	Ventana* ventana = NULL;
	FabricaOperacionesCliente fab;

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

					vector<string> parametrosGCF;
					parametrosGCF.push_back(ventanaLogin->getUsuario());
					OpUIClienteGetCantFichas* opGetFichas = ((OpUIClienteGetCantFichas*)fab.newOperacion(
						"OpUIClienteGetCantFichas", parametrosGCF));
					opGetFichas->ejecutarAccion(NULL);
					int fichasJug = opGetFichas->getCantidadFichas();
					delete(opGetFichas);

					ventanaAdministracion = new VentanaAdministracion(ventanaLogin->getUsuario(), 
																	  ventanaLogin->getSesionId(), 
																	  fichasJug);
					ventanaAdministracion->iniciar();

					if (ventanaAdministracion->getVerEstadisticas())
					{
						ventanaEstadistica = new VentanaEstadistica(ventanaAdministracion->getUsuario(), 
																	ventanaAdministracion->getSesionId());
						ventanaEstadistica->iniciar();

						if (ventanaEstadistica->getCancelado())
							sigueAdministracion = true;
						else 
							sigueAdministracion = true;

						delete(ventanaEstadistica);
						ventanaEstadistica = NULL;

						delete(ventanaAdministracion);
						ventanaAdministracion = NULL;
					
					}
					else if (ventanaAdministracion->getIrMesa())
					{
						delete(ventanaAdministracion);
						ventanaAdministracion = NULL;

						UICliente::iniciarSDL();

						ventana = new VentanaImpl();
						Sincronizador::getInstancia()->registrarVentana(ventana);

						UICliente::lanzarThreads(ventana);

						vector<string> parametros;
						parametros.push_back(ventanaLogin->getUsuario());
						parametros.push_back(ventanaLogin->isVirtual()? "true" : "false");
						parametros.push_back(ventanaLogin->isObservador()? "true" : "false");

						operacion = fab.newOperacion("OpUIClienteAgregarJugador", parametros);
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
		if (ventanaEstadistica == NULL) {
			delete(ventanaEstadistica);
		}
		if (operacion != NULL) {
			delete(operacion);
		}
		if (ventana != NULL) {
			delete(ventana);
		}
	}

	delete(Sincronizador::getInstancia());
	return 0;

}



// para pruebas
/*
int main (int argc, char** argv)
{
	VentanaConfiguracion* ventanaConfiguracion = NULL;
	VentanaLogin* ventanaLogin = NULL;
	VentanaNuevoJugador* ventanaNuevoJugador = NULL;
	VentanaAdministracion* ventanaAdministracion = NULL;
	VentanaEstadistica* ventanaEstadistica = NULL;
	OperacionUICliente* operacion = NULL;
	Ventana* ventana = NULL;
	FabricaOperacionesCliente fab;

	try {

		UICliente::iniciarAplicacion();
		UICliente::conectarServidor("localhost", 5000);

		

						UICliente::iniciarSDL();

						ventana = new VentanaImpl();
						Sincronizador::getInstancia()->registrarVentana(ventana);

						UICliente::lanzarThreads(ventana);

						vector<string> parametros;
						parametros.push_back("nat");
						parametros.push_back("false");
						parametros.push_back("false");

						operacion = fab.newOperacion("OpUIClienteAgregarJugador", parametros);
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
		if (ventanaEstadistica == NULL) {
			delete(ventanaEstadistica);
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
*/
