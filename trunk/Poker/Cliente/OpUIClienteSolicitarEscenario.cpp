#include "OpUIClienteSolicitarEscenario.h"
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

OpUIClienteSolicitarEscenario::OpUIClienteSolicitarEscenario(void) : OperacionUICliente(){
}

OpUIClienteSolicitarEscenario::~OpUIClienteSolicitarEscenario(void){
}

bool OpUIClienteSolicitarEscenario::ejecutar(Ventana* ventana){

	bool ok = true;
	DomTree* tree = new DomTree("operaciones");
	Elemento* pedido = tree->agregarElemento("pedido");

	Elemento* operacion = pedido->agregarHijo("operacion");
	operacion->agregarAtributo("id", "OpEnviarEscenario");

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