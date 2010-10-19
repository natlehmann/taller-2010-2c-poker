#include "Ventana.h"
#include "DomTree.h"
#include "MensajesUtil.h"
#include "Mesa.h"
#include "Jugador.h"
#include "Carta.h"
#include "CartasComunitarias.h"
#include "Bote.h"
#include "Boton.h"
#include "UtilTiposDatos.h"
#include "ParserException.h"

#define XML_MESA "mesa"
#define XML_JUGADORES "jugadores"
#define XML_BOTE "bote"

#define XML_JUGADOR "jugador"

#define XML_IMAGEN "imagen"
#define XML_FICHAS "fichas"
#define XML_APUESTA "apuesta"
#define XML_CARTAS "cartas"
#define XML_CARTASCOMUNITARIAS "cartascomunitarias"

#define XML_PANEL_COMANDO "panelComando"
#define XML_PANEL_BOTON "boton"

class FabricaDeElementosGraficos
{
	public:

		/**
		* Metodo sincronizado que configura a una Ventana de acuerdo a la informacion
		* provista por un escenario.
		*/
		static void generarEscenario(DomTree* arbolEscenario, Ventana* ventana);
		
		virtual ~FabricaDeElementosGraficos(void);

	private:
		FabricaDeElementosGraficos(void);
		static Jugador* generarJugador(list<Elemento*>::iterator itJugador, Ventana* ventana);
		static Carta* FabricaDeElementosGraficos::generarCarta(
			list<Elemento*>::iterator itCarta, ElementoGrafico* elem);
		static Boton* FabricaDeElementosGraficos::generarBoton(
			list<Elemento*>::iterator itBoton, Panel* panel);
	
};
