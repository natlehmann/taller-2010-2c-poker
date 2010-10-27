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

string EstadoJuego::arbolToString(DomTree* arbol){

	XmlParser parser;
	return parser.toString(arbol);
}
