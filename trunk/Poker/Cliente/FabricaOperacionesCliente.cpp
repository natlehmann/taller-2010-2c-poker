#include "FabricaOperacionesCliente.h"
#include "DatosInvalidosException.h"
#include "Error.h"
#include "MensajesUtil.h"
#include "OpUIClienteSolicitarEscenario.h"

using namespace std;

FabricaOperacionesCliente::FabricaOperacionesCliente() {}

FabricaOperacionesCliente::~FabricaOperacionesCliente() {}

OperacionUICliente* FabricaOperacionesCliente::newOperacion(string nombreOperacion){

	OperacionUICliente* operacion = NULL;

	if (MensajesUtil::sonIguales(nombreOperacion, "OpUIClienteSolicitarEscenario")) {
		operacion = new OpUIClienteSolicitarEscenario();
	}

	// TODO: ACA SE VERIFICARIAN TODAS LAS DEMAS OPERACIONES

	if (operacion == NULL) {
		Error error("V","Id de operacion invalido.",nombreOperacion);
		throw DatosInvalidosException(error);
	}

	return operacion;

}

