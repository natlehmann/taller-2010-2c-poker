#include "SDL.h" 
#include <vld.h>
#include "RecursosAplicacion.h"
#include "UICliente.h"
#include "FabricaOperacionesCliente.h"
#include "OperacionUICliente.h"
#include "PokerException.h"
#include "Respuesta.h"
#include "Ventana.h"


int main (int argc, char** argv)
{
	OperacionUICliente* operacion = NULL;

	try {
		UICliente::iniciarAplicacion();

		string idOperacionInicial = 
			RecursosAplicacion::getClienteConfigProperties()->get("cliente.operacion.inicial");
		FabricaOperacionesCliente fab;
		Ventana ventana;

		operacion = fab.newOperacion(idOperacionInicial);
		if (operacion->ejecutar(&ventana))
			ventana.dibujar(NULL);
		else
			UICliente::mostrarMensaje("La aplicacion se ejecuto con errores. Por favor verifique el archivo 'errores.err'.", false);

		delete(operacion);
		operacion = NULL;

		UICliente::finalizar();

	} catch (PokerException& e) {
		RecursosAplicacion::getLogErroresCliente()->escribir(&e.getError());
		UICliente::mostrarMensaje(
			"La aplicacion se ejecuto con errores. Por favor verifique el archivo 'errores.err'.", false);
		if (operacion != NULL) {
			delete(operacion);
		}
	}

	return 0;

}
