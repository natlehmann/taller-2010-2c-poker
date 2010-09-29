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

OpUIClienteSolicitarEscenario::OpUIClienteSolicitarEscenario(void) : OperacionUICliente(){
}

OpUIClienteSolicitarEscenario::~OpUIClienteSolicitarEscenario(void){
}

void OpUIClienteSolicitarEscenario::ejecutar(Ventana* ventana){

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
		// ej: 
		// FabricaEscenario::generar(arbolEscenario, ventana);


		// TODO: ELIMINAR ESTO (ES EJEMPLO, SE DEBERIA INSTANCIAR EN LA FABRICA)
		Mesa* mesa = new Mesa();
		mesa->setAlto(ventana->getAlto());
		mesa->setAncho(ventana->getAncho());
		mesa->setFondo("..\\Cliente\\recursos\\imagenes\\mesa600x800.bmp");
		ventana->agregarElementoGrafico(mesa);
		Jugador* jugador = new Jugador();
		jugador->setImagen(new Imagen("..\\Servidor\\recursos\\imagenes\\jugador1.bmp"));
		jugador->setPosicion(1);
		ventana->agregarElementoGrafico(jugador);


		delete (arbolEscenario);

	} catch (PokerException& e) {
		RecursosAplicacion::getLogErroresCliente()->escribir(&(Respuesta)e.getError());
	}

	delete(parser);
	delete(tree);


}