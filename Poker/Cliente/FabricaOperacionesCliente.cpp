#include "FabricaOperacionesCliente.h"
#include "DatosInvalidosException.h"
#include "Error.h"
#include "MensajesUtil.h"
#include "OpUIClienteSolicitarEscenario.h"
#include "OpUIClienteSolicitarArchivo.h"
#include "OpUIClienteDejarMesa.h"
#include "OpUIClienteIgualarApuesta.h"
#include "OpUIClienteNoIr.h"
#include "OpUIClienteSubirApuesta.h"
#include "OpUIClienteAgregarJugador.h"
#include "OpUIClienteLogin.h"
#include "OpUIClientePasar.h"
#include "OpUIClienteRegistrarJugador.h"
#include "OpUIClienteComprarFichas.h"
#include "OpUIClienteEnviarFoto.h"
#include "OpUIClienteSolicitarEstadistica.h"
#include "OpUIClienteLogoff.h"
#include "OpUIClienteGetCantFichas.h"

using namespace std;

FabricaOperacionesCliente::FabricaOperacionesCliente() {}

FabricaOperacionesCliente::~FabricaOperacionesCliente() {}

OperacionUICliente* FabricaOperacionesCliente::newOperacion(string nombreOperacion){

	vector<string> parametros;
	return this->newOperacion(nombreOperacion, parametros);

}

OperacionUICliente* FabricaOperacionesCliente::newOperacion(string nombreOperacion, string parametro){

	vector<string> parametros;
	parametros.push_back(parametro);
	return this->newOperacion(nombreOperacion, parametros);

}

OperacionUICliente* FabricaOperacionesCliente::newOperacion(string nombreOperacion, vector<string> parametros){

	OperacionUICliente* operacion = NULL;

	if (MensajesUtil::sonIguales(nombreOperacion, "OpUIClienteSolicitarEscenario")) {
		operacion = new OpUIClienteSolicitarEscenario();
	}
	else if(MensajesUtil::sonIguales(nombreOperacion, "OpUIClienteSolicitarArchivo")) {
		operacion = new OpUIClienteSolicitarArchivo(parametros);
	}
	else if(MensajesUtil::sonIguales(nombreOperacion, "OpUIClienteDejarMesa")) {
		operacion = new OpUIClienteDejarMesa();
	}
	else if(MensajesUtil::sonIguales(nombreOperacion, "OpUIClienteIgualarApuesta")) {
		operacion = new OpUIClienteIgualarApuesta();
	}
	else if(MensajesUtil::sonIguales(nombreOperacion, "OpUIClienteNoIr")) {
		operacion = new OpUIClienteNoIr();
	}
	else if(MensajesUtil::sonIguales(nombreOperacion, "OpUIClienteSubirApuesta")) {
		operacion = new OpUIClienteSubirApuesta(parametros);
	}
	else if(MensajesUtil::sonIguales(nombreOperacion, "OpUIClienteAgregarJugador")) {
		operacion = new OpUIClienteAgregarJugador(parametros);
	}
	else if(MensajesUtil::sonIguales(nombreOperacion, "OpUIClienteLogin")) {
		operacion = new OpUIClienteLogin(parametros);
	}
	else if(MensajesUtil::sonIguales(nombreOperacion, "OpUIClientePasar")) {
		operacion = new OpUIClientePasar();
	}
	else if(MensajesUtil::sonIguales(nombreOperacion, "OpUIClienteRegistrarJugador")) {
		operacion = new OpUIClienteRegistrarJugador(parametros);
	}
	else if(MensajesUtil::sonIguales(nombreOperacion, "OpUIClienteComprarFichas")) {
		operacion = new OpUIClienteComprarFichas(parametros);
	}
	else if(MensajesUtil::sonIguales(nombreOperacion, "OpUIClienteEnviarFoto")) {
		operacion = new OpUIClienteEnviarFoto(parametros);
	}
	else if(MensajesUtil::sonIguales(nombreOperacion, "OpUIClienteSolicitarEstadistica")) {
		operacion = new OpUIClienteSolicitarEstadistica(parametros);
	}	
	else if(MensajesUtil::sonIguales(nombreOperacion, "OpUIClienteLogoff")) {
		operacion = new OpUIClienteLogoff(parametros);
	}
	else if(MensajesUtil::sonIguales(nombreOperacion, "OpUIClienteGetCantFichas")) {
		operacion = new OpUIClienteGetCantFichas(parametros);
	}

	if (operacion == NULL) {
		Error error("V","Id de operacion invalido.",nombreOperacion);
		throw DatosInvalidosException(error);
	}

	return operacion;

}

