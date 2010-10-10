#include "FabricaDeElementosGraficos.h"
#include "Apuesta.h"
#include "ParserException.h"
#include "JugadorAusente.h"

FabricaDeElementosGraficos::FabricaDeElementosGraficos(void)
{
}

FabricaDeElementosGraficos::~FabricaDeElementosGraficos(void)
{
}

void FabricaDeElementosGraficos::generarEscenario(DomTree *arbolEscenario, Ventana *ventana)
{
	if (arbolEscenario)
	{
		Elemento* raiz = arbolEscenario->getRaiz();

		for(list<Elemento*>::iterator itEscenario = raiz->getHijos()->begin(); itEscenario != raiz->getHijos()->end(); itEscenario++) 
		{
			for(list<Elemento*>::iterator itElementosVentana = (*itEscenario)->getHijos()->begin(); itElementosVentana != (*itEscenario)->getHijos()->end(); itElementosVentana++) 
			{
				if (MensajesUtil::sonIguales(XML_MESA, (*itElementosVentana)->getNombre()))
				{
					// Se genera la MESA
					Mesa* mesa = new Mesa();
					mesa->setId((*itElementosVentana)->getAtributo("id"));
					mesa->setAlto(ventana->getAlto());
					mesa->setAncho(ventana->getAncho());
					mesa->setFondo((*itElementosVentana)->getAtributo("fondo"));
					ventana->agregarElementoGrafico(mesa);
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
						Jugador* jugador = generarJugador(itJugador);
						if (posiciones[jugador->getPosicion() - 1]) {
							throw ParserException(
								"No puede haber mas de un jugador ocupando la misma posicion.","V");
						}
						posiciones[jugador->getPosicion() - 1] = true;
						ventana->agregarElementoGrafico(jugador);
					}

					//se completan las posiciones vacias
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
					//int cantidad = UtilTiposDatos::getEntero((*itElementosVentana)->getTexto());
					Bote* bote = new Bote();
					bote->setTotal(UtilTiposDatos::getEntero((*itElementosVentana)->getTexto()));
					ventana->agregarElementoGrafico(bote);
				}
				else if (MensajesUtil::sonIguales(XML_CARTASCOMUNITARIAS, (*itElementosVentana)->getNombre()))
				{
					// Se generan las CARTAS COMUNITARIAS
					CartasComunitarias* cartascomunitarias = new CartasComunitarias();
				
					for(list<Elemento*>::iterator itCartas = (*itElementosVentana)->getHijos()->begin(); itCartas != (*itElementosVentana)->getHijos()->end(); itCartas++)
					{
						// Se genera las CARTAS
						for(list<Elemento*>::iterator itCarta = (*itCartas)->getHijos()->begin(); itCarta != (*itCartas)->getHijos()->end(); itCarta++)
						{
							Carta* carta = generarCarta(itCarta);
							cartascomunitarias->setCarta(carta);
						}

						ventana->agregarElementoGrafico(cartascomunitarias);
					}
				}
			}
		}
		
	}
}

Jugador* FabricaDeElementosGraficos::generarJugador(list<Elemento*>::iterator itJugador)
{
	Jugador* jugador = new Jugador();
	Imagen* imagen;

	// Se setean los atributos del JUGADOR
	jugador->setId(UtilTiposDatos::getEntero((*itJugador)->getAtributo("id")));
	jugador->setNombre((*itJugador)->getAtributo("nombre"));
	
	// Se agregan las propiedades del JUGADOR
	for(list<Elemento*>::iterator itElemento = (*itJugador)->getHijos()->begin(); itElemento != (*itJugador)->getHijos()->end(); itElemento++) 
	{
		if (MensajesUtil::sonIguales(XML_IMAGEN, (*itElemento)->getNombre()))
		{
			// Se genera la IMAGEN y se la carga al JUGADOR
			imagen = new Imagen((*itElemento)->getAtributo("nombre"));
			imagen->setTamanio(UtilTiposDatos::getEntero((*itElemento)->getAtributo("tamanio")));
			imagen->setAncho(UtilTiposDatos::getEntero((*itElemento)->getAtributo("ancho")));
			imagen->setAlto(UtilTiposDatos::getEntero((*itElemento)->getAtributo("alto")));
			jugador->setImagen(imagen);
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
			// Se genera las CARTAS
			for(list<Elemento*>::iterator itCarta = (*itElemento)->getHijos()->begin(); itCarta != (*itElemento)->getHijos()->end(); itCarta++) 
			{
				Carta* carta = generarCarta(itCarta);
				jugador->setCarta(carta);
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

Carta* FabricaDeElementosGraficos::generarCarta(list<Elemento*>::iterator itCarta)
{
	Carta* carta = new Carta();

	carta->setNumero((*itCarta)->getAtributo("numero"));
	carta->setPalo((*itCarta)->getAtributo("palo"));
	carta->setPosicion(UtilTiposDatos::getEntero((*itCarta)->getAtributo("posicion")));
	
	if (MensajesUtil::sonIguales("true", (*itCarta)->getAtributo("visible")))
		carta->setVisible(true);
	else
		carta->setVisible(false);
	
	 return carta;
}
