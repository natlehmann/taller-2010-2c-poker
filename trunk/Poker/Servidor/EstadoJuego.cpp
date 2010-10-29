#include "EstadoJuego.h"
#include "DomTree.h"
#include "ContextoJuego.h"
#include "MesaModelo.h"
#include "UtilTiposDatos.h"
#include "MensajeModelo.h"
#include "XmlParser.h"
#include "JugadorModelo.h"
#include "MensajesUtil.h"
#include "UtilTiposDatos.h"
#include "CartasComunitariasModelo.h"
#include "CartaModelo.h"
#include <list>
#include <vector>

EstadoJuego::EstadoJuego(void)
{
}

EstadoJuego::~EstadoJuego(void)
{
}

DomTree* EstadoJuego::crearArbolEscenario() {
	DomTree* tree = new DomTree("escenario");
	Elemento* escenario = tree->agregarElemento("escenario");

	return tree;
}

void EstadoJuego::agregarMesa(DomTree* arbol) {
	
	Elemento* elementoEscenario = arbol->getRaiz()->getHijos()->front();
	MesaModelo* mesaModelo = ContextoJuego::getInstancia()->getMesa();

	Elemento* mesa = elementoEscenario->agregarHijo("mesa", "escenario");
	mesa->agregarAtributo("id", UtilTiposDatos::enteroAString(mesaModelo->getId()));
	mesa->agregarAtributo("fondo", mesaModelo->getFondo());
}

void EstadoJuego::agregarBote(DomTree* arbol) {

	Elemento* elementoEscenario = arbol->getRaiz()->getHijos()->front();
	BoteModelo* boteModelo = ContextoJuego::getInstancia()->getBote();

	Elemento* bote = elementoEscenario->agregarHijo("bote", "escenario");
	bote->agregarAtributo("id", UtilTiposDatos::enteroAString(boteModelo->getId()));
	bote->setTexto(UtilTiposDatos::enteroAString(boteModelo->getCantidad()));
}

void EstadoJuego::agregarMensaje(DomTree* arbol, string mensaje){
	
	Elemento* elementoEscenario = arbol->getRaiz()->getHijos()->front();
	MensajeModelo* mensajeModelo = ContextoJuego::getInstancia()->getMensaje();
	mensajeModelo->setTexto(mensaje);

	Elemento* elemMensaje = elementoEscenario->agregarHijo("mensaje", "escenario");
	elemMensaje->agregarAtributo("id", UtilTiposDatos::enteroAString(mensajeModelo->getId()));
	elemMensaje->agregarAtributo("visible", "true");
	elemMensaje->setTexto(mensajeModelo->getTexto());
}

void EstadoJuego::borrarMensaje(DomTree* arbol){
	
	Elemento* elementoEscenario = arbol->getRaiz()->getHijos()->front();
	MensajeModelo* mensajeModelo = ContextoJuego::getInstancia()->getMensaje();
	mensajeModelo->setTexto("");

	Elemento* elemMensaje = elementoEscenario->agregarHijo("mensaje", "escenario");
	elemMensaje->agregarAtributo("id", UtilTiposDatos::enteroAString(mensajeModelo->getId()));
	elemMensaje->agregarAtributo("visible", "false");
	elemMensaje->setTexto(mensajeModelo->getTexto());
}

void EstadoJuego::agregarJugadores(DomTree* arbol, int idJugador){

	Elemento* elementoEscenario = arbol->getRaiz()->getHijos()->front();
	Elemento* elemJugadores = elementoEscenario->agregarHijo("jugadores", "escenario");

	vector<JugadorModelo*> jugadores = ContextoJuego::getInstancia()->getJugadores();
	for (vector<JugadorModelo*>::iterator it = jugadores.begin(); it != jugadores.end(); it++) {

		Elemento* elemJugador = elemJugadores->agregarHijo("jugador", "escenario");
		elemJugador->agregarAtributo("id", UtilTiposDatos::enteroAString((*it)->getId()));
		elemJugador->agregarAtributo("posicion", UtilTiposDatos::enteroAString((*it)->getPosicion()));
		elemJugador->agregarAtributo("nombre", (*it)->getNombre());

		if ((*it)->isAusente()) {
			elemJugador->agregarAtributo("estado", "ausente");

		} else {
			if ((*it)->isActivo()) {
				elemJugador->agregarAtributo("estado", "activo");

			} else {
				elemJugador->agregarAtributo("estado", "inactivo");
			}
		}


		if (!(*it)->isAusente()) {

			// se agrega la imagen
			Elemento* elemImagen = elemJugador->agregarHijo("imagen", "escenario");
			if ( (*it)->isActivo() && !MensajesUtil::esVacio((*it)->getNombreImagen()) ) {
				elemImagen->agregarAtributo("nombre", (*it)->getNombreImagen());
			
			} else {
				// TODO: VER SI SE MANDA NOMBRE IMAGEN A ARCHIVO PROPERTIES
				elemImagen->agregarAtributo("nombre", "jugador_default.bmp");
			}


			// se agregan las fichas
			Elemento* elemFichas = elemJugador->agregarHijo("fichas", "escenario");
			elemFichas->setTexto(UtilTiposDatos::enteroAString((*it)->getFichas()));

			// se agregan la apuesta
			Elemento* elemApuesta = elemJugador->agregarHijo("apuesta", "escenario");
			elemApuesta->setTexto(UtilTiposDatos::enteroAString((*it)->getApuesta()));

			// se agregan las cartas
			if ((*it)->getCarta1() != NULL && (*it)->getCarta2() != NULL) {

				Elemento* elemCartas = elemJugador->agregarHijo("cartas", "escenario");
				Elemento* elemCarta1 = elemCartas->agregarHijo("carta", "escenario");
				Elemento* elemCarta2 = elemCartas->agregarHijo("carta", "escenario");

				elemCarta1->agregarAtributo("id", (*it)->getCarta1()->getId());
				elemCarta2->agregarAtributo("id", (*it)->getCarta2()->getId());

				// TODO: AGREGAR CHEQUEO PARA FUNCIONALIDAD DE "VER TODAS LAS CARTAS"

				// para el jugador que inicio el pedido
				if ((*it)->getId() == idJugador) {

					elemCarta1->agregarAtributo("numero", (*it)->getCarta1()->getNumero());
					elemCarta1->agregarAtributo("palo", (*it)->getCarta1()->getPalo());
					elemCarta1->agregarAtributo("reverso", "false");

					elemCarta2->agregarAtributo("numero", (*it)->getCarta2()->getNumero());
					elemCarta2->agregarAtributo("palo", (*it)->getCarta2()->getPalo());
					elemCarta2->agregarAtributo("reverso", "false");
				
				} else {

					elemCarta1->agregarAtributo("reverso", "true");
					elemCarta2->agregarAtributo("reverso", "true");
				}
			}

		}
	}
}

void EstadoJuego::agregarCartasComunitarias(DomTree* arbol){

	Elemento* elementoEscenario = arbol->getRaiz()->getHijos()->front();
	Elemento* elemCartasCom = elementoEscenario->agregarHijo("cartascomunitarias", "escenario");

	CartasComunitariasModelo* cartasComunitarias = ContextoJuego::getInstancia()->getCartasComunitarias();
	elemCartasCom->agregarAtributo("id", UtilTiposDatos::enteroAString(cartasComunitarias->getId()));

	list<CartaModelo*> cartas = cartasComunitarias->getCartas();
	if (!cartas.empty()) {

		Elemento* elemCartas = elemCartasCom->agregarHijo("cartas", "escenario");

		for (list<CartaModelo*>::iterator it = cartas.begin(); it != cartas.end(); it++) {

			Elemento* elemCarta = elemCartas->agregarHijo("carta", "escenario");
			elemCarta->agregarAtributo("id", (*it)->getId());
			elemCarta->agregarAtributo("posicion", UtilTiposDatos::enteroAString((*it)->getPosicion()));
			elemCarta->agregarAtributo("reverso", "true");
			
			// TODO: AGREGAR CHEQUEO PARA FUNCIONALIDAD DE "VER TODAS LAS CARTAS"

			if (ContextoJuego::getInstancia()->getMostrandoCartas()) {
				elemCarta->agregarAtributo("numero", (*it)->getNumero());
				elemCarta->agregarAtributo("palo", (*it)->getPalo());
				elemCarta->agregarAtributo("reverso", "false");
			}
		}
	}
}

void EstadoJuego::agregarPanelBotones(DomTree* arbol, int idJugador){

	Elemento* elementoEscenario = arbol->getRaiz()->getHijos()->front();
	Elemento* elemPanel = elementoEscenario->agregarHijo("panelComando", "escenario");
	elemPanel->agregarAtributo("id", "panelCom");

	// TODO: VER SI LOS TEXTOS LOS PONEMOS EN EL ARCHIVO DE PROPERTIES
	Elemento* boton1 = elemPanel->agregarHijo("boton", "escenario");
	boton1->agregarAtributo("id", "btDejarMesa");
	boton1->agregarAtributo("posicion", "1");
	boton1->agregarAtributo("operacion", "OpUIClienteDejarMesa");
	boton1->setTexto("Dejar Mesa");

	Elemento* boton2 = elemPanel->agregarHijo("boton", "escenario");
	boton2->agregarAtributo("id", "btIgualar");
	boton2->agregarAtributo("posicion", "2");
	boton2->agregarAtributo("operacion", "OpUIClienteIgualarApuesta");
	boton2->setTexto("Igualar");

	Elemento* boton3 = elemPanel->agregarHijo("boton", "escenario");
	boton3->agregarAtributo("id", "btNoIr");
	boton3->agregarAtributo("posicion", "3");
	boton3->agregarAtributo("operacion", "OpUIClienteNoIr");
	boton3->setTexto("No Ir");

	Elemento* boton4 = elemPanel->agregarHijo("boton", "escenario");
	boton4->agregarAtributo("id", "btSubir");
	boton4->agregarAtributo("posicion", "4");
	boton4->agregarAtributo("operacion", "OpUIClienteSubirApuesta");
	boton4->setTexto("Subir");

	Elemento* textBox = elemPanel->agregarHijo("textBox", "escenario");
	textBox->agregarAtributo("id", "txtApuesta");
	textBox->agregarAtributo("posicion", "5");
	textBox->agregarAtributo("operacion", "OpUIClienteSubirApuesta");

	if (ContextoJuego::getInstancia()->isTurnoJugador(idJugador)) {
		boton1->agregarAtributo("habilitado", "true");
		boton2->agregarAtributo("habilitado", "true");
		boton3->agregarAtributo("habilitado", "true");
		boton4->agregarAtributo("habilitado", "true");
		textBox->agregarAtributo("habilitado", "true");
	
	} else {
		boton1->agregarAtributo("habilitado", "false");
		boton2->agregarAtributo("habilitado", "false");
		boton3->agregarAtributo("habilitado", "false");
		boton4->agregarAtributo("habilitado", "false");
		textBox->agregarAtributo("habilitado", "false");
	}

}

string EstadoJuego::arbolToString(DomTree* arbol){

	XmlParser parser;
	return parser.toString(arbol);
}

string EstadoJuego::getEscenarioEstandar(int idJugador){

	DomTree* arbol = this->crearArbolEscenario();
	this->agregarMesa(arbol);
	this->agregarBote(arbol);
	this->agregarJugadores(arbol, idJugador);
	this->agregarCartasComunitarias(arbol);
	this->agregarPanelBotones(arbol, idJugador);
	this->borrarMensaje(arbol);

	return this->arbolToString(arbol);
}
