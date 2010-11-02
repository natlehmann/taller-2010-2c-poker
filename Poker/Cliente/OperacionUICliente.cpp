#include "OperacionUICliente.h"
#include "PokerException.h"
#include "RecursosCliente.h"
#include "XmlParser.h"
#include "Cliente.h"
#include "UICliente.h"
#include "FabricaDeElementosGraficos.h"
#include "VentanaAuxiliar.h"
#include "Sincronizador.h"

OperacionUICliente::OperacionUICliente(void)
{
}

OperacionUICliente::~OperacionUICliente(void)
{
}

bool OperacionUICliente::ejecutar(Ventana* ventana){

	bool resultado = false;
	
	Ventana* aux = Sincronizador::getInstancia()->getVentanaAuxiliar();

	try {
		resultado = this->ejecutarAccion(aux);

	} catch(PokerException& e){
		RecursosCliente::getLog()->escribir(&(e.getError()));

	} catch(exception& e){
		RecursosCliente::getLog()->escribir("Se produjo un error ejecutando la operacion. " + string(e.what()));

	} catch(...){
		RecursosCliente::getLog()->escribir("Se produjo un error ejecutando la operacion.");
	}

	/*
	SDL_Event event;

	event.type = SDL_USEREVENT;
	event.user.code = 1;
	event.user.data1 = "";
	event.user.data2 = 0;

	ventana->PushEvent(&event);
	*/

	Sincronizador::getInstancia()->notificarCambio();

	return resultado;
}

Elemento* OperacionUICliente::agregarOperacion(DomTree* arbol, string nombreOperacion) {

	Elemento* pedido = arbol->agregarElemento("pedido");

	Elemento* operacion = pedido->agregarHijo("operacion");
	operacion->agregarAtributo("id", nombreOperacion);

	return operacion;
}


bool OperacionUICliente::enviarPedido(string nombreOperacion, Ventana* ventana) {
	
	DomTree* tree = new DomTree("operaciones");
	this->agregarOperacion(tree, nombreOperacion);

	bool resultado = this->enviarMensaje(tree, ventana);

	delete(tree);

	return resultado;
}

bool OperacionUICliente::enviarMensaje(DomTree* tree, Ventana* ventana) {

	bool ok = true;
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
	return ok;
}
