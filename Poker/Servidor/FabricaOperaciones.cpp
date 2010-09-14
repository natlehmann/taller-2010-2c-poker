#include "FabricaOperaciones.h"
#include "Suma.h"
#include "Resta.h"
#include "Multiplicacion.h"
#include "Division.h"
#include "UtilTiposDatos.h"
#include "DatosInvalidosException.h"
#include "Error.h"
#include "MensajesUtil.h"
#include <list>
using namespace std;

FabricaOperaciones::FabricaOperaciones() {}

FabricaOperaciones::~FabricaOperaciones() {}

Operacion* FabricaOperaciones::newOperacion(DomTree* domTree)
{
	string idOperacion;
	vector<double> parametros;

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

	if (hijosPedido == NULL || hijosPedido->size() != 2) {
		Error resultado("V",
			string("Error en linea ") + MensajesUtil::intToString(elementoPedido->getNumeroDeLinea()) 
			+ string(". El tag 'pedido' debe tener dos hijos, 'operacion' y 'parametros'."),"");
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

	if (idOperacion.length() != 1 || (idOperacion[0] != 'S' && idOperacion[0] != 'R' && idOperacion[0] != 'M' && idOperacion[0] != 'D')) {
		Error resultado("V",
			string("Error en linea ") + MensajesUtil::intToString(elementoOperacion->getNumeroDeLinea())
			+ string(". El atributo 'id' del tag 'operacion' debe ser 'S', 'R', 'M' o 'D'."),"");
		throw DatosInvalidosException(resultado);
	}
	if (elementoOperacion->getTexto().size() != 0) {
		Error resultado("V",
			string("Error en linea ") + MensajesUtil::intToString(elementoOperacion->getNumeroDeLinea())
			+ string(". El tag 'operacion' no puede contener texto. Se encontro '")
			+ elementoOperacion->getTexto()+"'.",idOperacion);
		throw DatosInvalidosException(resultado);
	}

	it++;
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
	if (idOperacion[0] == 'D' && hijosParametros->size() != 2) {
		Error resultado("V",
			string("Error en linea ") + MensajesUtil::intToString(elementoParametros->getNumeroDeLinea())
			+ string(". Una division debe tener 2 parametros, 'dividendo' y 'divisor'."),idOperacion);
		throw DatosInvalidosException(resultado);
	}
	if (hijosParametros->size() < 2) {
		Error resultado("V",
			string("Error en linea ") + MensajesUtil::intToString(elementoParametros->getNumeroDeLinea())
			+ string(". Deben haber al menos dos parametros para realizar la operacion."),idOperacion);
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
		parametros.push_back(UtilTiposDatos::stringADouble(valor));
	}
	
	switch (idOperacion.at(0))
	{
	case 'S':
		return new Suma("S",parametros);
		break;
	case 'R':
		return new Resta("R",parametros);
		break;
	case 'M':
		return new Multiplicacion("M",parametros);
		break;
	case 'D':
		return new Division("D",parametros);
		break;
	}
	return NULL;
}


void FabricaOperaciones::validarParametro(Elemento* parametro, string idOperacion, int numeroDeParametro)
{
	if (parametro->getAtributos()->size() != 1) {
		Error resultado("V",
			string("Error en linea ") + MensajesUtil::intToString(parametro->getNumeroDeLinea())
			+ string(". El tag 'parametro' debe tener un atributo 'nombre'."),"");
		throw DatosInvalidosException(resultado);
	}

	string atributoNombre = MensajesUtil::trim(parametro->getAtributo("nombre"));

	switch (idOperacion.at(0))
	{
	case 'S':
		if (strcmp("sum",atributoNombre.c_str()) != 0) {
			Error resultado("V",
				string("Error en linea ") + MensajesUtil::intToString(parametro->getNumeroDeLinea())
				+ string(". El atributo 'nombre' del tag 'parametro' para una suma debe ser 'sum'. Se encontro '")
				+ atributoNombre +"'.",idOperacion);
			throw DatosInvalidosException(resultado);
		}
		break;

	case 'R':
		if (strcmp("res",atributoNombre.c_str()) != 0) {
			Error resultado("V",
				string("Error en linea ") + MensajesUtil::intToString(parametro->getNumeroDeLinea())
				+ string(". El atributo 'nombre' del tag 'parametro' para una resta debe ser 'res'. Se encontro '")
				+ atributoNombre +"'.",idOperacion);
			throw DatosInvalidosException(resultado);
		}
		break;

	case 'M':
		if (strcmp("mul",atributoNombre.c_str()) != 0) {
			Error resultado("V",
				string("Error en linea ") + MensajesUtil::intToString(parametro->getNumeroDeLinea())
				+ string(". El atributo 'nombre' del tag 'parametro' para una multiplicacion debe ser 'mul'. Se encontro '")
				+ atributoNombre +"'.",idOperacion);
			throw DatosInvalidosException(resultado);
		}
		break;

	case 'D':
		if (numeroDeParametro == 1) {
			if (strcmp("dividendo",atributoNombre.c_str()) != 0) {
				Error resultado("V",
					string("Error en linea ") + MensajesUtil::intToString(parametro->getNumeroDeLinea())
					+ string(". El primer parametro para una division debe ser tener el valor 'dividendo' en el atributo 'nombre' . Se encontro '")
					+ atributoNombre +"'.",idOperacion);
				throw DatosInvalidosException(resultado);
			}
		} else {
			if (strcmp("divisor",atributoNombre.c_str()) != 0) {
				Error resultado("V",
					string("Error en linea ") + MensajesUtil::intToString(parametro->getNumeroDeLinea())
					+ string(". El segundo parametro para una division debe ser tener el valor 'divisor' en el atributo 'nombre' . Se encontro '")
					+ atributoNombre +"'.",idOperacion);
				throw DatosInvalidosException(resultado);
			}
		}
		break;
	}

	if (!UtilTiposDatos::esDouble(parametro->getTexto())) {
		Error resultado("V",
			string("Error en linea ") + MensajesUtil::intToString(parametro->getNumeroDeLinea())
			+ string(". El parametro contiene un valor que no es numerico. Se encontro '")
			+ parametro->getTexto()+"'.",idOperacion);
		throw DatosInvalidosException(resultado);
	}
}
