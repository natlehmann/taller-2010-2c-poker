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

OpUIClienteSolicitarEscenario::OpUIClienteSolicitarEscenario(void) : OperacionUICliente(){
}

OpUIClienteSolicitarEscenario::~OpUIClienteSolicitarEscenario(void){
}

void OpUIClienteSolicitarEscenario::ejecutar(){

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

	try {
		DomTree* arbolEscenario = parser->toDom(msjRecibido, "escenario");

		// TODO: PASAR EL MENSAJE POR LA FABRICA DE ESCENARIO PARA QUE CONFIGURE LA VENTANA
		cout << "Recibi este arbol " << parser->toString(arbolEscenario) << endl;

		delete (arbolEscenario);

	} catch (PokerException& e) {
		RecursosAplicacion::getLogErroresCliente()->escribir(&(Respuesta)e.getError());
	}

	delete(parser);
	delete(tree);


}