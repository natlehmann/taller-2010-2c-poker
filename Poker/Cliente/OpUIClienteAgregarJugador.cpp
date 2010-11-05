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

	//TODO: SE COMENTA HASTA QUE ESTE IMPLEMENTADO
	//string nombreJugador = parametros.at(0);
	string nombreJugador = "PEPE";

	Elemento* parametros = operacion->agregarHijo("parametros");
	Elemento* parametro1 = parametros->agregarHijo("parametro");

	// TODO: VER SI ES NECESARIO MANDAR PASSWORD
	parametro1->agregarAtributo("nombre", "usuario");
	parametro1->setTexto(nombreJugador);

	ok = this->enviarMensaje(tree, ventana);

	delete(tree);

	return ok;
}
