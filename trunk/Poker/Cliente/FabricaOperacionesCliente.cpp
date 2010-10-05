#include "FabricaOperacionesCliente.h"
#include "DatosInvalidosException.h"
#include "Error.h"
#include "MensajesUtil.h"
#include "OpUIClienteSolicitarEscenario.h"
#include "OpUIClienteSolicitarArchivo.h"

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

	// TODO: ACA SE VERIFICARIAN TODAS LAS DEMAS OPERACIONES

	if (operacion == NULL) {
		Error error("V","Id de operacion invalido.",nombreOperacion);
		throw DatosInvalidosException(error);
	}

	return operacion;

}

