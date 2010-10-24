#include "EstadoJuego.h"
#include "DomTree.h"
#include "ContextoJuego.h"
#include "MesaModelo.h"
#include "UtilTiposDatos.h"

EstadoJuego::EstadoJuego(void)
{
}

EstadoJuego::~EstadoJuego(void)
{
}

Elemento* EstadoJuego::crearElementoEscenario() {
	DomTree* tree = new DomTree("escenario");
	Elemento* escenario = tree->agregarElemento("escenario");

	return escenario;
}

void EstadoJuego::agregarMesa(Elemento* elementoEscenario) {

	MesaModelo* mesaModelo = ContextoJuego::getInstancia()->getMesa();

	Elemento* mesa = elementoEscenario->agregarHijo("mesa");
	mesa->agregarAtributo("id", UtilTiposDatos::enteroAString(mesaModelo->getId()));
	mesa->agregarAtributo("fondo", mesaModelo->getFondo());
}

void EstadoJuego::agregarBote(Elemento* elementoEscenario) {

	BoteModelo* boteModelo = ContextoJuego::getInstancia()->getBote();

	Elemento* bote = elementoEscenario->agregarHijo("bote");
	bote->agregarAtributo("id", UtilTiposDatos::enteroAString(boteModelo->getId()));
	bote->setTexto(UtilTiposDatos::enteroAString(boteModelo->getCantidad()));
}

void EstadoJuego::agregarMensaje(Elemento* elementoEscenario, string mensaje){
	// TODO !!!
}
