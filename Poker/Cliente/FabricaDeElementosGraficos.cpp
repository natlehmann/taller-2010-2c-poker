#include "FabricaDeElementosGraficos.h"

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
					mesa->setFondo("..\\Cliente\\recursos\\imagenes\\mesa640x480.bmp");
					ventana->agregarElementoGrafico(mesa);
				}
				else if (MensajesUtil::sonIguales(XML_JUGADORES, (*itElementosVentana)->getNombre()))
				{
					// Se genera los JUGADORES
					for(list<Elemento*>::iterator itJugador = (*itElementosVentana)->getHijos()->begin(); itJugador != (*itElementosVentana)->getHijos()->end(); itJugador++) 
					{
						Jugador* jugador = generarJugador(itJugador);
						ventana->agregarElementoGrafico(jugador);
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
			string pathImagen = "..\\Servidor\\recursos\\imagenes\\";
		    imagen = new Imagen(pathImagen + (*itElemento)->getAtributo("nombre"));
			imagen->setTamanio(UtilTiposDatos::getEntero((*itElemento)->getAtributo("tamanio")));
			imagen->setAncho(UtilTiposDatos::getEntero((*itElemento)->getAtributo("ancho")));
			imagen->setAlto(UtilTiposDatos::getEntero((*itElemento)->getAtributo("alto")));
			jugador->setImagen(imagen);
		}
		else if (MensajesUtil::sonIguales(XML_FICHAS, (*itElemento)->getNombre()))
		{
			// Se genera las FICHAS
			int cantidadFichas = UtilTiposDatos::getEntero((*itElemento)->getTexto());
		}
		else if (MensajesUtil::sonIguales(XML_APUESTA, (*itElemento)->getNombre()))
		{
			// Se genera la APUESTA
			int cantidadApuesta = UtilTiposDatos::getEntero((*itElemento)->getTexto());
		}
		else if (MensajesUtil::sonIguales(XML_CARTAS, (*itElemento)->getNombre()))
		{
			// Se genera las CARTAS
			for(list<Elemento*>::iterator itCarta = (*itElemento)->getHijos()->begin(); itCarta != (*itElemento)->getHijos()->end(); itCarta++) 
			{
				Carta* carta = generarCarta(itCarta);
				//jugador->setCarta(carta);
			}
		}
	}

	// La posicion se debe setear luego de cargar la imagen del jugador
	jugador->setPosicion(UtilTiposDatos::getEntero((*itJugador)->getAtributo("posicion")));

	return jugador;
}

Carta* FabricaDeElementosGraficos::generarCarta(list<Elemento*>::iterator itCarta)
{
	Carta* carta = new Carta();

	carta->setNumero((*itCarta)->getAtributo("numero"));
	carta->setPalo((*itCarta)->getAtributo("palo"));
	
	if (MensajesUtil::sonIguales("true", (*itCarta)->getAtributo("visible")))
		carta->setVisible(true);
	else
		carta->setVisible(false);
	
	 return carta;
}
