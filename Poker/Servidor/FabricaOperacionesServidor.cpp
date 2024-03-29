#include "FabricaOperacionesServidor.h"
#include "UtilTiposDatos.h"
#include "DatosInvalidosException.h"
#include "Error.h"
#include "MensajesUtil.h"
#include "OpEnviarEscenario.h"
#include "OpEnviarArchivo.h"
#include "OpLogin.h"
#include "OpLogoff.h"
#include "OpAgregarJugador.h"
#include "OpNoIr.h"
#include "OpIgualarApuesta.h"
#include "OpDejarMesa.h"
#include "OpSubirApuesta.h"
#include "RecursosServidor.h"
#include "OpMostrarMensaje.h"
#include "OpPasar.h"
#include "OpRegistrarJugador.h"
#include "OpComprarFichas.h"
#include "OpRecibirFoto.h"
#include "OpEnviarEstadistica.h"
#include "OpGetCantidadFichas.h"
#include <list>
using namespace std;


FabricaOperacionesServidor::FabricaOperacionesServidor() {}

FabricaOperacionesServidor::~FabricaOperacionesServidor() {}

Operacion* FabricaOperacionesServidor::newOperacion(string nombreOperacion, vector<string> parametros, int idCliente){

	Operacion* operacion = NULL;

	if (MensajesUtil::sonIguales(nombreOperacion, "OpEnviarEscenario")) {
		operacion = new OpEnviarEscenario(idCliente);
	}
	else if (MensajesUtil::sonIguales(nombreOperacion, "OpEnviarArchivo")) {
		operacion = new OpEnviarArchivo(idCliente, parametros);
	}
	else if (MensajesUtil::sonIguales(nombreOperacion, "OpLogin")) {
		operacion = new OpLogin(idCliente, parametros);
	}
	else if (MensajesUtil::sonIguales(nombreOperacion, "OpLogoff")) {
		operacion = new OpLogoff(idCliente, parametros);
	}
	else if (MensajesUtil::sonIguales(nombreOperacion, "OpAgregarJugador")) {
		operacion = new OpAgregarJugador(idCliente, parametros);
	}
	else if (MensajesUtil::sonIguales(nombreOperacion, "OpNoIr")) {
		operacion = new OpNoIr(idCliente);
	}
	else if (MensajesUtil::sonIguales(nombreOperacion, "OpIgualarApuesta")) {
		operacion = new OpIgualarApuesta(idCliente);
	}
	else if (MensajesUtil::sonIguales(nombreOperacion, "OpDejarMesa")) {
		operacion = new OpDejarMesa(idCliente);
	}
	else if (MensajesUtil::sonIguales(nombreOperacion, "OpSubirApuesta")) {
		operacion = new OpSubirApuesta(idCliente, parametros);
	}
	else if (MensajesUtil::sonIguales(nombreOperacion, "OpMostrarMensaje")) {
		operacion = new OpMostrarMensaje(idCliente, parametros);
	}
	else if (MensajesUtil::sonIguales(nombreOperacion, "OpPasar")) {
		operacion = new OpPasar(idCliente);
	}
	else if (MensajesUtil::sonIguales(nombreOperacion, "OpRegistrarJugador")) {
		operacion = new OpRegistrarJugador(idCliente, parametros);
	}
	else if (MensajesUtil::sonIguales(nombreOperacion, "OpComprarFichas")) {
		operacion = new OpComprarFichas(idCliente, parametros);
	}
	else if (MensajesUtil::sonIguales(nombreOperacion, "OpRecibirFoto")) {
		operacion = new OpRecibirFoto(idCliente, parametros);
	}
	else if (MensajesUtil::sonIguales(nombreOperacion, "OpEnviarEstadistica")) {
		operacion = new OpEnviarEstadistica(idCliente, parametros);
	}
	else if (MensajesUtil::sonIguales(nombreOperacion, "OpGetCantidadFichas")) {
		operacion = new OpGetCantidadFichas(idCliente, parametros);
	}

	if (operacion == NULL) {
		RecursosServidor::getLog()->escribir(string("Se solicito un Id de operacion invalido: ") + nombreOperacion);
		Error error("V","Id de operacion invalido.",nombreOperacion);
		throw DatosInvalidosException(error);
	}

	return operacion;

}

Operacion* FabricaOperacionesServidor::newOperacion(DomTree* domTree, int idCliente)
{
	string idOperacion;
	vector<string> parametros;

	if (domTree == NULL) {
		Error resultado("V","Error inesperado leyendo datos de entrada.","");
		throw DatosInvalidosException(resultado);
	}

	Elemento* elementoRaiz = domTree->getRaiz();

	if (elementoRaiz == NULL) {
		Error resultado("V","Error inesperado leyendo datos de entrada.","");
		throw DatosInvalidosException(resultado);
	}

	list<Elemento*>* hijosRaiz = elementoRaiz->getHijos();

	if (hijosRaiz == NULL) {
		Error resultado("V","Error inesperado leyendo datos de entrada.","");
		throw DatosInvalidosException(resultado);
	}
	if (hijosRaiz->size() != 1) {
		Error resultado("V","Error inesperado leyendo datos de entrada.\nHay mas de un elemento raiz.","");
		throw DatosInvalidosException(resultado);
	}

	list<Elemento*>::iterator it = hijosRaiz->begin();
	Elemento* elementoPedido = *it;

	if (elementoPedido == NULL) {
		Error resultado("V","Error inesperado leyendo datos de entrada.","");
		throw DatosInvalidosException(resultado);
	}
	if (strcmp("pedido",elementoPedido->getNombre().c_str()) != 0) {
		Error resultado("V",
			string("Error en linea ") + MensajesUtil::intToString(elementoPedido->getNumeroDeLinea()) 
			+  string(". Se esperaba tag 'pedido' y se encontro '") 
			+ elementoPedido->getNombre() + "'.","");
		throw DatosInvalidosException(resultado);
	}
	if (elementoPedido->getTexto().size() != 0) {
		Error resultado("V",
			string("Error en linea ") + MensajesUtil::intToString(elementoPedido->getNumeroDeLinea()) 
			+ string(". El tag 'pedido' no puede contener texto. Se encontro '")
			+ elementoPedido->getTexto()+"'.","");
		throw DatosInvalidosException(resultado);
	}

	list<Elemento*>* hijosPedido = elementoPedido->getHijos();

	if (hijosPedido == NULL || hijosPedido->size() < 1) {
		Error resultado("V",
			string("Error en linea ") + MensajesUtil::intToString(elementoPedido->getNumeroDeLinea()) 
			+ string(". El tag 'pedido' debe tener al menos un hijo."),"");
		throw DatosInvalidosException(resultado);
	}

	it = hijosPedido->begin();
	Elemento* elementoOperacion = *it;

	if (strcmp("operacion",elementoOperacion->getNombre().c_str()) != 0) {
		Error resultado("V",
			string("Error en linea ") + MensajesUtil::intToString(elementoOperacion->getNumeroDeLinea()) 
			+ string(". Se esperaba tag 'operacion' y se encontro '")
			+ elementoOperacion->getNombre() + "'.","");
		throw DatosInvalidosException(resultado);
	}
	if (elementoOperacion->getAtributos()->size() != 1) {
		Error resultado("V",
			string("Error en linea ") + MensajesUtil::intToString(elementoOperacion->getNumeroDeLinea())
			+ string(". El tag 'operacion' debe tener un atributo 'id'."),"");
		throw DatosInvalidosException(resultado);
	}

	idOperacion = MensajesUtil::trim(elementoOperacion->getAtributo("id"));

	if (elementoOperacion->getTexto().size() != 0) {
		Error resultado("V",
			string("Error en linea ") + MensajesUtil::intToString(elementoOperacion->getNumeroDeLinea())
			+ string(". El tag 'operacion' no puede contener texto. Se encontro '")
			+ elementoOperacion->getTexto()+"'.",idOperacion);
		throw DatosInvalidosException(resultado);
	}

		
	list<Elemento*>* hijosOperacion = elementoOperacion->getHijos();
	if (hijosOperacion != NULL && hijosOperacion->size() >= 1) 
	{
		//it++;
		it = hijosOperacion->begin();
		Elemento* elementoParametros = *it;

		if (strcmp("parametros",elementoParametros->getNombre().c_str()) != 0) {
			Error resultado("V",
				string("Error en linea ") + MensajesUtil::intToString(elementoParametros->getNumeroDeLinea())
				+ string(". Se esperaba tag 'parametros' y se encontro '")
				+ elementoParametros->getNombre()+"'.",idOperacion);
			throw DatosInvalidosException(resultado);
		}
		if (elementoParametros->getTexto().size() != 0) {
			Error resultado("V",
				string("Error en linea ") + MensajesUtil::intToString(elementoParametros->getNumeroDeLinea())
				+ string(". El tag 'parametros' no puede contener texto y se encontro '")
				+ elementoParametros->getTexto()+"'.",idOperacion);
			throw DatosInvalidosException(resultado);
		}

		list<Elemento*>* hijosParametros = elementoParametros->getHijos();

		if (hijosParametros == NULL || hijosParametros->size() == 0) {
			Error resultado("V",
				string("Error en linea ") + MensajesUtil::intToString(elementoParametros->getNumeroDeLinea())
				+ string(". El tag 'parametros' no tiene hijos. Se esperaba tag 'parametro'."),idOperacion);
			throw DatosInvalidosException(resultado);
		}

		int cantidadParametros = 0;
		for (it = hijosParametros->begin(); it != hijosParametros->end(); it++) {
			cantidadParametros++;
			Elemento* elementoParametro = *it;
			if (elementoParametro == NULL) {
				Error resultado("V",
					string("Error en linea ") + MensajesUtil::intToString(elementoParametros->getNumeroDeLinea())
					+ string(". El tag 'parametros' no tiene hijos. Se esperaba tag 'parametro'."),idOperacion);
				throw DatosInvalidosException(resultado);
			}
			validarParametro(elementoParametro, idOperacion, cantidadParametros);
			string valor = elementoParametro->getTexto();
			parametros.push_back(valor);
		}
	}
	return this->newOperacion(idOperacion, parametros, idCliente);
}


void FabricaOperacionesServidor::validarParametro(Elemento* parametro, string idOperacion, int numeroDeParametro)
{
	if (parametro->getAtributos()->size() != 1) {
		Error resultado("V",
			string("Error en linea ") + MensajesUtil::intToString(parametro->getNumeroDeLinea())
			+ string(". El tag 'parametro' debe tener un atributo 'nombre'."),"");
		throw DatosInvalidosException(resultado);
	}

	string atributoNombre = MensajesUtil::trim(parametro->getAtributo("nombre"));

	if (MensajesUtil::sonIguales(idOperacion, "OpEnviarEscenario")) {
		if (strcmp("nombreArchivo",atributoNombre.c_str()) != 0) {
			Error resultado("V",
				string("Error en linea ") + MensajesUtil::intToString(parametro->getNumeroDeLinea())
				+ string(". El atributo 'nombre' del tag 'parametro' para una transferencia de archivo debe ser 'nombreArchivo'. Se encontro '")
				+ atributoNombre +"'.",idOperacion);
			throw DatosInvalidosException(resultado);
		}
	}

	if (MensajesUtil::sonIguales(idOperacion, "OpSubirApuesta")) {
		if (strcmp("fichas",atributoNombre.c_str()) != 0) {
			Error resultado("V",
				string("Error en linea ") + MensajesUtil::intToString(parametro->getNumeroDeLinea())
				+ string(". El atributo 'nombre' del tag 'parametro' para subir la apuesta de un jugador debe ser 'fichas'. Se encontro '")
				+ atributoNombre +"'.",idOperacion);
			throw DatosInvalidosException(resultado);
		}
	}

	if (MensajesUtil::sonIguales(MensajesUtil::trim(parametro->getTexto()),"")) {
			Error resultado("V",
				string("Error en linea ") + MensajesUtil::intToString(parametro->getNumeroDeLinea())
				+ string(". El valor del parametro '" + atributoNombre + "' esta vacio."),idOperacion);
		throw DatosInvalidosException(resultado);
	}

}
