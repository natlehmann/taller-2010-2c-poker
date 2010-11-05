#include "OpSubirApuesta.h"
#include "ContextoJuego.h"
#include "FabricaOperacionesServidor.h"
#include <vector>
#include "Operacion.h"
#include "UtilTiposDatos.h"


OpSubirApuesta::OpSubirApuesta(int idCliente, vector<string> parametros) : Operacion(idCliente) {
	this->parametros = parametros;
}

OpSubirApuesta::~OpSubirApuesta(void)
{
}

bool OpSubirApuesta::ejecutarAccion(Socket* socket){

	FabricaOperacionesServidor fab;
	vector<string> parametros;
	Operacion* operacion;
	string nombreOperacion = "OpEnviarEscenario";


	if (ContextoJuego::getInstancia()->isTurnoCliente(this->getIdCliente())) {

		string fichasTxt = this->parametros.at(0);
		int fichas = UtilTiposDatos::getEntero(fichasTxt);

		if (fichas <= 0) {
			nombreOperacion = "OpMostrarMensaje";
			parametros.push_back("Debe ingresar un numero entero mayor a 0.");
		}

		if (!ContextoJuego::getInstancia()->puedeSubirApuesta(this->getIdCliente(), fichas)) {
			nombreOperacion = "OpMostrarMensaje";
			parametros.push_back("La apuesta excede los limites.");

		} else if (!ContextoJuego::getInstancia()->esApuestaValida(this->getIdCliente(), fichas)) {
			nombreOperacion = "OpMostrarMensaje";
			parametros.push_back("La apuesta debe superar a las de los demas jugadores.");		
		
		} else {
			ContextoJuego::getInstancia()->subirApuesta(this->getIdCliente(), fichas);
		}
	}

	
	operacion = fab.newOperacion(nombreOperacion, parametros, this->getIdCliente());
	bool resultado = operacion->ejecutarAccion(socket);
	delete (operacion);

	return resultado;
}
