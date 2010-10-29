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

	Elemento* parametros = operacion->agregarHijo("parametros");
	Elemento* parametro1 = parametros->agregarHijo("parametro");

	// TODO: VER SI ES NECESARIO MANDAR PASSWORD
	parametro1->agregarAtributo("nombre", "usuario");
	parametro1->setTexto(nombreJugador);

	XmlParser* parser = new XmlParser();

	// se envia el pedido al servidor
	Cliente* cliente = UICliente::getCliente();
	string msjRecibido;

	if (cliente->enviarRecibir(parser->toString(tree), msjRecibido)) 
	{
		try {
			DomTree* arbolEscenario = parser->toDom(msjRecibido, "escenario");
			FabricaDeElementosGraficos::generarEscenario(arbolEscenario, ventana);
			delete (arbolEscenario);

			UICliente::lanzarThreads(ventana);

		} catch (PokerException& e) {
			RecursosCliente::getLog()->escribir(&(Respuesta)e.getError());
			ok = false;
		}
	}
	else
	{
		RecursosCliente::getLog()->escribir("El servidor no devolvio ningun escenario.");
		ok = false;
	}

	delete(parser);
	delete(tree);

	return ok;
}
