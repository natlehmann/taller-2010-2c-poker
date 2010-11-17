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

	JugadorModelo** jugadores = ContextoJuego::getInstancia()->getJugadores();
	for (int i = 0; i < MAX_CANTIDAD_JUGADORES; i++) {

		Elemento* elemJugador = elemJugadores->agregarHijo("jugador", "escenario");
		elemJugador->agregarAtributo("id", UtilTiposDatos::enteroAString(jugadores[i]->getId()));
		elemJugador->agregarAtributo("posicion", UtilTiposDatos::enteroAString(jugadores[i]->getPosicion()));
		elemJugador->agregarAtributo("nombre", jugadores[i]->getNombre());

		if (jugadores[i]->isDealer()) {
			elemJugador->agregarAtributo("dealer", "true");

		} else {
			elemJugador->agregarAtributo("dealer", "false");
		}

		if (jugadores[i]->isAusente()) {
			elemJugador->agregarAtributo("estado", "ausente");

		} else {
			if (jugadores[i]->isActivo()) {
				elemJugador->agregarAtributo("estado", "activo");

			} else {
				elemJugador->agregarAtributo("estado", "inactivo");
			}
		}


		if (!jugadores[i]->isAusente()) {

			// se agrega la imagen
			Elemento* elemImagen = elemJugador->agregarHijo("imagen", "escenario");
			if ( jugadores[i]->isActivo() && !MensajesUtil::esVacio(jugadores[i]->getNombreImagen()) ) {
				elemImagen->agregarAtributo("nombre", jugadores[i]->getNombreImagen());
			
			} else {
				// TODO: VER SI SE MANDA NOMBRE IMAGEN A ARCHIVO PROPERTIES
				elemImagen->agregarAtributo("nombre", "jugador_default.bmp");
			}


			// se agregan las fichas
			Elemento* elemFichas = elemJugador->agregarHijo("fichas", "escenario");
			elemFichas->setTexto(UtilTiposDatos::enteroAString(jugadores[i]->getFichas()));

			// se agregan la apuesta
			Elemento* elemApuesta = elemJugador->agregarHijo("apuesta", "escenario");
			elemApuesta->setTexto(UtilTiposDatos::enteroAString(jugadores[i]->getApuesta()));

			// se agregan las cartas
			Elemento* elemCartas = elemJugador->agregarHijo("cartas", "escenario");
			Elemento* elemCarta1 = elemCartas->agregarHijo("carta", "escenario");
			Elemento* elemCarta2 = elemCartas->agregarHijo("carta", "escenario");

			elemCarta1->agregarAtributo("id", UtilTiposDatos::enteroAString(jugadores[i]->getId()) + "_c1");
			elemCarta2->agregarAtributo("id", UtilTiposDatos::enteroAString(jugadores[i]->getId()) + "_c2");

			if (jugadores[i]->getCarta1() != NULL && jugadores[i]->getCarta2() != NULL) {	
				elemCarta1->agregarAtributo("visible", "true");
				elemCarta2->agregarAtributo("visible", "true");

				// si el jugador puede ver las cartas
				if (jugadores[i]->getId() == idJugador 
					|| ContextoJuego::getInstancia()->getMostrandoCartas()
					|| jugadores[idJugador]->isObservador()) {

					elemCarta1->agregarAtributo("numero", jugadores[i]->getCarta1()->getNumero());
					elemCarta1->agregarAtributo("palo", jugadores[i]->getCarta1()->getPalo());
					elemCarta1->agregarAtributo("reverso", "false");					

					elemCarta2->agregarAtributo("numero", jugadores[i]->getCarta2()->getNumero());
					elemCarta2->agregarAtributo("palo", jugadores[i]->getCarta2()->getPalo());
					elemCarta2->agregarAtributo("reverso", "false");
				
				} else {

					elemCarta1->agregarAtributo("reverso", "true");
					elemCarta2->agregarAtributo("reverso", "true");
				}

			} else {
				elemCarta1->agregarAtributo("visible", "false");
				elemCarta2->agregarAtributo("visible", "false");
			}

		}
	}
}

void EstadoJuego::agregarCartasComunitarias(DomTree* arbol){

	Elemento* elementoEscenario = arbol->getRaiz()->getHijos()->front();
	Elemento* elemCartasCom = elementoEscenario->agregarHijo("cartascomunitarias", "escenario");

	CartasComunitariasModelo* cartasComunitarias = ContextoJuego::getInstancia()->getCartasComunitarias();
	elemCartasCom->agregarAtributo("id", UtilTiposDatos::enteroAString(cartasComunitarias->getId()));

	Elemento* elemCartas = elemCartasCom->agregarHijo("cartas", "escenario");


	list<CartaModelo*> cartas = cartasComunitarias->getCartas();
	if (!cartas.empty()) {		

		for (list<CartaModelo*>::iterator it = cartas.begin(); it != cartas.end(); it++) {

			Elemento* elemCarta = elemCartas->agregarHijo("carta", "escenario");
			elemCarta->agregarAtributo("id", string("cc") + UtilTiposDatos::enteroAString((*it)->getPosicion()));
			elemCarta->agregarAtributo("posicion", UtilTiposDatos::enteroAString((*it)->getPosicion()));
			elemCarta->agregarAtributo("numero", (*it)->getNumero());
			elemCarta->agregarAtributo("palo", (*it)->getPalo());
			elemCarta->agregarAtributo("reverso", "false");
			elemCarta->agregarAtributo("visible", "true");
		}
	
	} else {
		// blanqueo de cartas
		for (int i = 1; i <= 5; i++) {

			Elemento* elemCarta = elemCartas->agregarHijo("carta", "escenario");
			elemCarta->agregarAtributo("id", string("cc") + UtilTiposDatos::enteroAString(i));
			elemCarta->agregarAtributo("posicion", UtilTiposDatos::enteroAString(i));
			elemCarta->agregarAtributo("visible", "false");
		}
	}
}

void EstadoJuego::agregarPanelBotones(DomTree* arbol, int idJugador){	

	bool terminado = false;
	if (idJugador >= 0) {
		
		JugadorModelo* jugador = ContextoJuego::getInstancia()->getJugador(idJugador);
		if (!jugador->isVirtual() && jugador->isActivo()) {

			bool botonesHabilitados;
			if (ContextoJuego::getInstancia()->isRondaAllIn()) {
				botonesHabilitados = false;
			} else {
				botonesHabilitados = ContextoJuego::getInstancia()->isTurnoJugador(idJugador);
			}

			bool puedeSubirApuesta;
			if (ContextoJuego::getInstancia()->puedeSubirApuesta(idJugador)) {
				puedeSubirApuesta = true;
			} else {
				puedeSubirApuesta = false;
			}

			this->agregarPanelBotones(arbol, botonesHabilitados, puedeSubirApuesta);
			terminado = true;
		}
	} 

	if (!terminado) {
		this->agregarPanelBotones(arbol, false, true);
	}
}


void EstadoJuego::agregarPanelBotones(DomTree* arbol, bool habilitados, bool puedeSubirApuesta){

	Elemento* elementoEscenario = arbol->getRaiz()->getHijos()->front();
	Elemento* elemPanel = elementoEscenario->agregarHijo("panelComando", "escenario");
	elemPanel->agregarAtributo("id", "panelCom");

	// TODO: VER SI LOS TEXTOS LOS PONEMOS EN EL ARCHIVO DE PROPERTIES
	Elemento* boton1 = elemPanel->agregarHijo("boton", "escenario");
	boton1->agregarAtributo("id", "btDejarMesa");
	boton1->agregarAtributo("posicion", "1");
	boton1->agregarAtributo("operacion", "OpUIClienteDejarMesa");
	boton1->setTexto("Dejar Mesa");
	this->agregarAtributoHabilitado(boton1, true);


	Elemento* boton2 = elemPanel->agregarHijo("boton", "escenario");
	boton2->agregarAtributo("id", "btIgualar");
	boton2->agregarAtributo("posicion", "2");

	if (ContextoJuego::getInstancia()->puedePasar()) {		
		boton2->agregarAtributo("operacion", "OpUIClientePasar");
		boton2->setTexto("Pasar");

	} else {

		boton2->agregarAtributo("operacion", "OpUIClienteIgualarApuesta");
		if (puedeSubirApuesta || !habilitados) {
			boton2->setTexto("Igualar");
		} else {
			boton2->setTexto("All In");
		}
	}	

	Elemento* boton3 = elemPanel->agregarHijo("boton", "escenario");
	boton3->agregarAtributo("id", "btNoIr");
	boton3->agregarAtributo("posicion", "3");
	boton3->agregarAtributo("operacion", "OpUIClienteNoIr");
	boton3->setTexto("No Ir");

	Elemento* boton4 = elemPanel->agregarHijo("boton", "escenario");
	boton4->agregarAtributo("id", "btSubir");
	boton4->agregarAtributo("posicion", "4");
	boton4->agregarAtributo("operacion", "OpUIClienteSubirApuesta");
	boton4->agregarAtributo("idComponentePanelRelacionado", "txtApuesta");
	boton4->setTexto("Subir");

	Elemento* textBox = elemPanel->agregarHijo("textBox", "escenario");
	textBox->agregarAtributo("id", "txtApuesta");
	textBox->agregarAtributo("posicion", "5");
	textBox->agregarAtributo("operacion", "OpUIClienteSubirApuesta");

	this->agregarAtributoHabilitado(boton2, habilitados);
	this->agregarAtributoHabilitado(boton3, habilitados);
	this->agregarAtributoHabilitado(boton4, habilitados && puedeSubirApuesta);
	this->agregarAtributoHabilitado(textBox, habilitados && puedeSubirApuesta);
}


void EstadoJuego::agregarAtributoHabilitado(Elemento* elemento, bool habilitado) {

	if (habilitado) {
		elemento->agregarAtributo("habilitado", "true");
	
	} else {
		elemento->agregarAtributo("habilitado", "false");
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

	string resultado = this->arbolToString(arbol);
	delete (arbol);

	return resultado;
}

string EstadoJuego::getEscenarioConMensaje(int idJugador, string mensaje){

	DomTree* arbol = this->crearArbolEscenario();
	this->agregarMesa(arbol);
	this->agregarBote(arbol);
	this->agregarJugadores(arbol, idJugador);
	this->agregarCartasComunitarias(arbol);
	this->agregarPanelBotones(arbol, idJugador);

	this->agregarMensaje(arbol, mensaje);

	string resultado = this->arbolToString(arbol);
	delete (arbol);

	return resultado;
}

