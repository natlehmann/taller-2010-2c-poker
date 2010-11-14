#include "OpUIClienteAgregarJugador.h"
#include "DomTree.h"
#include "DomTreeFactory.h"
#include "Elemento.h"
#include "UICliente.h"
#include "Cliente.h"
#include "XmlParser.h"
#include "PokerException.h"
#include "RecursosCliente.h"
#include "Respuesta.h"
#include "FabricaDeElementosGraficos.h"

OpUIClienteAgregarJugador::OpUIClienteAgregarJugador(vector<string> parametros) : OperacionUICliente(){
	this->parametros = parametros;
}

OpUIClienteAgregarJugador::~OpUIClienteAgregarJugador(void)
{
}

bool OpUIClienteAgregarJugador::ejecutarAccion(Ventana* ventana){

	bool ok = true;
	DomTree* tree = new DomTree("operaciones");
	Elemento* operacion = this->agregarOperacion(tree, "OpAgregarJugador");

	string nombreJugador = parametros.at(0);
	string esVirtual = parametros.at(1);
	string esObservador = parametros.at(2);

	Elemento* parametros = operacion->agregarHijo("parametros");
	Elemento* parametro1 = parametros->agregarHijo("parametro");
	Elemento* parametro2 = parametros->agregarHijo("parametro");
	Elemento* parametro3 = parametros->agregarHijo("parametro");

	parametro1->agregarAtributo("nombre", "usuario");
	parametro1->setTexto(nombreJugador);
	parametro2->agregarAtributo("nombre", "virtual");
	parametro2->setTexto(esVirtual);
	parametro3->agregarAtributo("nombre", "observador");
	parametro3->setTexto(esObservador);

	ok = this->enviarMensaje(tree, ventana);

	delete(tree);

	return ok;
}
