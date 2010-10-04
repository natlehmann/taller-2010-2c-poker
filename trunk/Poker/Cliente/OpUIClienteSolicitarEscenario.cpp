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

void OpUIClienteSolicitarEscenario::ejecutar(Ventana* ventana){

	DomTree* tree = new DomTree("operaciones");
	Elemento* pedido = tree->agregarElemento("pedido");

	Elemento* operacion = pedido->agregarHijo("operacion");
	operacion->agregarAtributo("id", "OpEnviarEscenario");

	XmlParser* parser = new XmlParser();

	// se envia el pedido al servidor
	//Cliente* cliente = UICliente::getCliente();
	bool enviado = Cliente::enviarMsj(parser->toString(tree));

	// se recibe la respuesta y se interpreta el xml
	string msjRecibido;
	bool recibido = Cliente::recibirMsj(msjRecibido);

	try {
		DomTree* arbolEscenario = parser->toDom(msjRecibido, "escenario");
		FabricaDeElementosGraficos::generarEscenario(arbolEscenario, ventana);

		// TODO: ELIMINAR ESTO (ES EJEMPLO, SE DEBERIA INSTANCIAR EN LA FABRICA)
		//Mesa* mesa = new Mesa();
		//mesa->setAlto(ventana->getAlto());
		//mesa->setAncho(ventana->getAncho());
		//mesa->setFondo("..\\Cliente\\recursos\\imagenes\\mesa600x800.bmp");
		//ventana->agregarElementoGrafico(mesa);
		//Jugador* jugador = new Jugador();
		//jugador->setImagen(new Imagen("..\\Servidor\\recursos\\imagenes\\jugador1.bmp"));
		//jugador->setPosicion(1);
		//ventana->agregarElementoGrafico(jugador);
		/*Jugador* jugador2 = new Jugador();
		jugador2->setImagen(new Imagen("..\\Servidor\\recursos\\imagenes\\jugador2.bmp"));
		jugador2->setPosicion(2);
		ventana->agregarElementoGrafico(jugador2);
		Jugador* jugador3 = new Jugador();
		jugador3->setImagen(new Imagen("..\\Servidor\\recursos\\imagenes\\jugador3.bmp"));
		jugador3->setPosicion(3);
		ventana->agregarElementoGrafico(jugador3);
		Jugador* jugador4 = new Jugador();
		jugador4->setImagen(new Imagen("..\\Servidor\\recursos\\imagenes\\jugador4.bmp"));
		jugador4->setPosicion(4);
		ventana->agregarElementoGrafico(jugador4);
		Jugador* jugador5 = new Jugador();
		jugador5->setImagen(new Imagen("..\\Servidor\\recursos\\imagenes\\jugador1.bmp"));
		jugador5->setPosicion(5);
		ventana->agregarElementoGrafico(jugador5);
		Jugador* jugador6 = new Jugador();
		jugador6->setImagen(new Imagen("..\\Servidor\\recursos\\imagenes\\jugador2.bmp"));
		jugador6->setPosicion(6);
		ventana->agregarElementoGrafico(jugador6);*/
		// HASTA ACA

		delete (arbolEscenario);

	} catch (PokerException& e) {
		RecursosAplicacion::getLogErroresCliente()->escribir(&(Respuesta)e.getError());
	}

	delete(parser);
	delete(tree);


}