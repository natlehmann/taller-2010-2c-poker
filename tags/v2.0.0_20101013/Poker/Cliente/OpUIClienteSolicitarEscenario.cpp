#include "OpUIClienteSolicitarEscenario.h"
#include "DomTree.h"
#include "DomTreeFactory.h"
#include "Elemento.h"
#include "UICliente.h"
#include "Cliente.h"
#include "XmlParser.h"
#include "PokerException.h"
#include "RecursosAplicacion.h"
#include "Respuesta.h"
#include "Mesa.h"
#include "Jugador.h"
#include "Imagen.h"
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
	bool enviado = cliente->enviarMsj(parser->toString(tree));

	// se recibe la respuesta y se interpreta el xml
	string msjRecibido;
	bool recibido = cliente->recibirMsj(msjRecibido);

	if (msjRecibido.length() > 1)
	{
		try {
			DomTree* arbolEscenario = parser->toDom(msjRecibido, "escenario");
			FabricaDeElementosGraficos::generarEscenario(arbolEscenario, ventana);
			delete (arbolEscenario);

		} catch (PokerException& e) {
			RecursosAplicacion::getLogErroresCliente()->escribir(&(Respuesta)e.getError());
			ok = false;
		}
	}
	else
	{
		RecursosAplicacion::getLogErroresCliente()->escribir("El servidor no devolvio ningun escenario.");
		ok = false;
	}

	delete(parser);
	delete(tree);

	return ok;
}