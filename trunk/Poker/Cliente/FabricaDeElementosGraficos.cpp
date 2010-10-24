#include "FabricaDeElementosGraficos.h"
#include "Apuesta.h"
#include "ParserException.h"
#include "JugadorAusente.h"
#include "Respuesta.h"
#include "Panel.h"
#include "TextBox.h"
#include "Mensaje.h"
#include <typeinfo.h>



FabricaDeElementosGraficos::FabricaDeElementosGraficos(void)
{
}

FabricaDeElementosGraficos::~FabricaDeElementosGraficos(void)
{
}

void FabricaDeElementosGraficos::generarEscenario(DomTree *arbolEscenario, Ventana *ventana)
{
	if (arbolEscenario)	{
		
		ventana->bloquear();

		try {
			Elemento* raiz = arbolEscenario->getRaiz();

			for(list<Elemento*>::iterator itEscenario = raiz->getHijos()->begin(); 
				itEscenario != raiz->getHijos()->end(); itEscenario++) {

				for(list<Elemento*>::iterator itElementosVentana = (*itEscenario)->getHijos()->begin(); 
					itElementosVentana != (*itEscenario)->getHijos()->end(); itElementosVentana++) {

					if (MensajesUtil::sonIguales(XML_MESA, (*itElementosVentana)->getNombre()))
					{
						string idMesa = (*itElementosVentana)->getAtributo("id");
						ElementoGrafico* mesaEnc = ventana->getElementoPorId(idMesa);
						Mesa* mesa = NULL;

						if (mesaEnc != NULL && MensajesUtil::sonIguales(typeid(*mesaEnc).name(), "class Mesa")){
							mesa = (Mesa*)mesaEnc;
						
						} else {
							// Se genera la MESA
							mesa = new Mesa();

							if (mesaEnc != NULL){
								ventana->borrarElementoPorId(idMesa);							
							} 

							ventana->agregarElementoGrafico(mesa);							
						}
						
						mesa->setId(idMesa);
						mesa->setAlto(ventana->getAlto());
						mesa->setAncho(ventana->getAncho());
						mesa->setFondo((*itElementosVentana)->getAtributo("fondo"));
						
					}
					else if (MensajesUtil::sonIguales(XML_JUGADORES, (*itElementosVentana)->getNombre()))
					{
						//
						// Se generan los JUGADORES
						//
						if ((*itElementosVentana)->getHijos()->size() > 6) {
							throw ParserException("El juego no admite mas de 6 jugadores.","V");
						}

						// control de posiciones ocupadas
						bool posiciones[6];
						for (int i = 0; i < 6; i++){
							posiciones[i] = false;
						}

						for(list<Elemento*>::iterator itJugador = (*itElementosVentana)->getHijos()->begin(); 
							itJugador != (*itElementosVentana)->getHijos()->end(); itJugador++) 
						{
							Jugador* jugador = generarJugador(itJugador, ventana);
							if (posiciones[jugador->getPosicion() - 1]) {
								throw ParserException(
									"No puede haber mas de un jugador ocupando la misma posicion.","V");
							}
							posiciones[jugador->getPosicion() - 1] = true;
						}

						//se completan las posiciones vacias
						// TODO: REEMPLAZAR ESTO: QUE VENGA EN EL ESCENARIO
						for (int i = 0; i < 6; i++){
							if (!posiciones[i]) {
								JugadorAusente* jugadorAusente = new JugadorAusente();
								jugadorAusente->setPosicion(i + 1);
								ventana->agregarElementoGrafico(jugadorAusente);
							}
						}

					}
					else if (MensajesUtil::sonIguales(XML_BOTE, (*itElementosVentana)->getNombre()))
					{
						// Se genera el BOTE
						Bote* bote = NULL;
						string idBote = (*itElementosVentana)->getAtributo("id");
						ElementoGrafico* elem = ventana->getElementoPorId(idBote);
						if (elem != NULL && MensajesUtil::sonIguales(typeid(*elem).name(), "class Bote")){
							bote = (Bote*)elem;

						} else {
							bote = new Bote();
							if(elem != NULL) {
								ventana->borrarElementoPorId(idBote);
							}
							ventana->agregarElementoGrafico(bote);
						}

						bote->setId(idBote);
						bote->setTotal(UtilTiposDatos::getEntero((*itElementosVentana)->getTexto()));
						
					}
					else if (MensajesUtil::sonIguales(XML_CARTASCOMUNITARIAS, (*itElementosVentana)->getNombre()))
					{
						// Se generan las CARTAS COMUNITARIAS
						string idCartasCom = (*itElementosVentana)->getAtributo("id");
						CartasComunitarias* cartascomunitarias = NULL;
						ElementoGrafico* elem = ventana->getElementoPorId(idCartasCom);

						if (elem != NULL && MensajesUtil::sonIguales(typeid(*elem).name(), "class CartasComunitarias")){
							cartascomunitarias = (CartasComunitarias*)elem;

						} else {							
							cartascomunitarias = new CartasComunitarias();
							if (elem != NULL) {
								ventana->borrarElementoPorId(idCartasCom);
							}
							ventana->agregarElementoGrafico(cartascomunitarias);
						}

						cartascomunitarias->setId(idCartasCom);
					
						for(list<Elemento*>::iterator itCartas = (*itElementosVentana)->getHijos()->begin(); 
							itCartas != (*itElementosVentana)->getHijos()->end(); itCartas++)
						{
							// Se genera las CARTAS
							for(list<Elemento*>::iterator itCarta = (*itCartas)->getHijos()->begin(); 
								itCarta != (*itCartas)->getHijos()->end(); itCarta++)
							{
								Carta* carta = generarCarta(itCarta, 
									cartascomunitarias->getElementoPorId((*itCarta)->getAtributo("id")));
								cartascomunitarias->setCarta(carta);
							}
						}
					}
					else if (MensajesUtil::sonIguales(XML_PANEL_COMANDO, (*itElementosVentana)->getNombre()))
					{
						// Se genera el Panel de Comandos
						Panel* panel = ventana->getPanelComando();

						if (panel == NULL){
							panel = new Panel();
							ventana->setPanelComando(panel);
						}

						// Se generan los botones
						for(list<Elemento*>::iterator itComponente = (*itElementosVentana)->getHijos()->begin(); 
							itComponente != (*itElementosVentana)->getHijos()->end(); itComponente++) {

								if (MensajesUtil::sonIguales(XML_PANEL_BOTON, (*itComponente)->getNombre())) {
									Boton* boton = generarBoton(itComponente, panel);
									panel->agregarComponente(boton, boton->getPosicion());
								}

								if (MensajesUtil::sonIguales(XML_PANEL_TEXTBOX, (*itComponente)->getNombre())) {
									TextBox* textBox = generarTextBox(itComponente, panel);
									panel->agregarComponente(textBox, textBox->getPosicion());
								}
						}
					}
					else if (MensajesUtil::sonIguales(XML_MENSAJE, (*itElementosVentana)->getNombre()))
					{
						// Se genera el Mensaje
						Mensaje* mensaje = NULL;
						string idMensaje = (*itElementosVentana)->getAtributo("id");
						ElementoGrafico* elem = ventana->getElementoPorId(idMensaje);
						if (elem != NULL && MensajesUtil::sonIguales(typeid(*elem).name(), "class Mensaje")){
							mensaje = (Mensaje*)elem;

						} else {
							mensaje = new Mensaje("");
							if(elem != NULL) {
								ventana->borrarElementoPorId(idMensaje);
							}
							ventana->agregarElementoGrafico(mensaje);
						}

						mensaje->setId(idMensaje);
						mensaje->setTexto((*itElementosVentana)->getTexto());
						if (MensajesUtil::sonIguales("true", (*itElementosVentana)->getAtributo("visible"))){
							mensaje->setVisible(true);
						} else {
							mensaje->setVisible(false);
						}
						
					}
				}
			}

		} catch (PokerException& e) {
			RecursosAplicacion::getLogErroresCliente()->escribir(&e.getError());
		} catch (exception& e2) {
			RecursosAplicacion::getLogErroresCliente()->escribir("Error al procesar el archivo escenario.");
			RecursosAplicacion::getLogErroresCliente()->escribir(e2.what());
		} catch (...) {
			RecursosAplicacion::getLogErroresCliente()->escribir("Error al procesar el archivo escenario.");
		}

		ventana->desbloquear();
	}
}

Jugador* FabricaDeElementosGraficos::generarJugador(list<Elemento*>::iterator itJugador, Ventana* ventana)
{
	string idJugador = (*itJugador)->getAtributo("id");
	ElementoGrafico* elem = ventana->getElementoPorId(idJugador);

	Jugador* jugador = NULL;

	if (elem != NULL && MensajesUtil::sonIguales(typeid(*elem).name(), "class Jugador")){
		jugador = (Jugador*)elem;
	
	} else {
		jugador = new Jugador();

		if (elem != NULL){
			ventana->borrarElementoPorId(idJugador);							
		} 

		ventana->agregarElementoGrafico(jugador);							
	}

	// Se setean los atributos del JUGADOR
	jugador->setId(idJugador);
	jugador->setNombre((*itJugador)->getAtributo("nombre"));
	
	// Se agregan las propiedades del JUGADOR
	for(list<Elemento*>::iterator itElemento = (*itJugador)->getHijos()->begin(); 
		itElemento != (*itJugador)->getHijos()->end(); itElemento++) 
	{
		if (MensajesUtil::sonIguales(XML_IMAGEN, (*itElemento)->getNombre()))
		{
			// Se genera la IMAGEN y se la carga al JUGADOR
			if (!MensajesUtil::esVacio((*itElemento)->getAtributo("nombre"))) {
				jugador->setImagen((*itElemento)->getAtributo("nombre"));
			}
		}
		else if (MensajesUtil::sonIguales(XML_FICHAS, (*itElemento)->getNombre()))
		{
			// Se genera las FICHAS
			jugador->setFichas(UtilTiposDatos::getEntero((*itElemento)->getTexto()));
		}
		else if (MensajesUtil::sonIguales(XML_APUESTA, (*itElemento)->getNombre()))
		{
			// Se genera la APUESTA
			jugador->setApuesta((*itElemento)->getTexto());
		}
		else if (MensajesUtil::sonIguales(XML_CARTAS, (*itElemento)->getNombre()))
		{
			// Se generan las CARTAS
			if ((*itElemento)->getHijos()->size() > 0 && (*itElemento)->getHijos()->size() != 2) {
				throw ParserException("El jugador " + jugador->getNombre() 
					+ " tiene una cantidad invalida de cartas.","V");
			}

			if ((*itElemento)->getHijos()->size() > 0) {

				list<Elemento*>::iterator itCarta = (*itElemento)->getHijos()->begin();
				Carta* carta = generarCarta(itCarta, jugador->getElementoPorId((*itCarta)->getAtributo("id")));
				jugador->setCarta1(carta);

				itCarta++;

				carta = generarCarta(itCarta, jugador->getElementoPorId((*itCarta)->getAtributo("id")));
				jugador->setCarta2(carta);
			}
		}
	}

	// La posicion se debe setear luego de cargar la imagen del jugador
	int posicion = UtilTiposDatos::getEntero((*itJugador)->getAtributo("posicion"));
	if (posicion < 1 || posicion > 6) {
		throw ParserException("Posicion de jugador no valida: " + MensajesUtil::intToString(posicion)
			+ ". Las posiciones validas son de 1 a 6.", "V");
	}
	jugador->setPosicion(posicion);

	return jugador;
}

Carta* FabricaDeElementosGraficos::generarCarta(list<Elemento*>::iterator itCarta, ElementoGrafico* elem)
{
	Carta* carta = NULL;

	if (elem != NULL && MensajesUtil::sonIguales(typeid(*elem).name(), "class Carta")){
		carta = (Carta*)elem;
	
	} else {
		carta = new Carta();						
	}

	carta->setId((*itCarta)->getAtributo("id"));
	carta->setNumero((*itCarta)->getAtributo("numero"));
	carta->setPalo((*itCarta)->getAtributo("palo"));
	carta->setPosicion(UtilTiposDatos::getEntero((*itCarta)->getAtributo("posicion")));
	
	if (MensajesUtil::sonIguales("true", (*itCarta)->getAtributo("visible"))){
		carta->setVisible(true);
	} else {
		carta->setVisible(false);
	}
	
	 return carta;
}

Boton* FabricaDeElementosGraficos::generarBoton(list<Elemento*>::iterator itBoton, Panel* panel)
{
	string idBoton = (*itBoton)->getAtributo("id");
	Boton* boton = NULL;
	ElementoGrafico* elem = panel->getElementoPorId(idBoton);

	if (elem != NULL && MensajesUtil::sonIguales(typeid(*elem).name(), "class Boton")){
		boton = (Boton*) elem;
		boton->setTexto((*itBoton)->getTexto());

	} else {
		boton = new Boton((*itBoton)->getTexto());
	}

	boton->setId(idBoton);
	boton->setPosicion(UtilTiposDatos::getEntero((*itBoton)->getAtributo("posicion")) - 1);
	
	if (MensajesUtil::sonIguales("true", (*itBoton)->getAtributo("habilitado"))) {
		boton->setHabilitado(true);

	} else {
		boton->setHabilitado(false);
	}

	boton->setIdOperacion((*itBoton)->getAtributo("operacion"));
	
	return boton;
}


TextBox* FabricaDeElementosGraficos::generarTextBox(list<Elemento*>::iterator itBoton, Panel* panel)
{
	string id = (*itBoton)->getAtributo("id");
	TextBox* textBox = NULL;
	ElementoGrafico* elem = panel->getElementoPorId(id);

	if (elem != NULL && MensajesUtil::sonIguales(typeid(*elem).name(), "class TextBox")){
		textBox = (TextBox*) elem;
		textBox->setTexto((*itBoton)->getTexto());

	} else {
		textBox = new TextBox((*itBoton)->getTexto());
	}

	textBox->setId(id);
	textBox->setPosicion(UtilTiposDatos::getEntero((*itBoton)->getAtributo("posicion")) - 1);
	
	if (MensajesUtil::sonIguales("true", (*itBoton)->getAtributo("habilitado"))) {
		textBox->setHabilitado(true);

	} else {
		textBox->setHabilitado(false);
	}

	textBox->setIdOperacion((*itBoton)->getAtributo("operacion"));
	
	return textBox;
}