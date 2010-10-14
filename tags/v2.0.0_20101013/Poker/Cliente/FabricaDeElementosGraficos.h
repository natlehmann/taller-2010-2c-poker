#include "Ventana.h"
#include "DomTree.h"
#include "MensajesUtil.h"
#include "Mesa.h"
#include "Jugador.h"
#include "Carta.h"
#include "CartasComunitarias.h"
#include "Bote.h"
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

class FabricaDeElementosGraficos
{
	public:

		static void generarEscenario(DomTree* arbolEscenario, Ventana* ventana);
		FabricaDeElementosGraficos(void);
		virtual ~FabricaDeElementosGraficos(void);

	private:
		static Jugador* generarJugador(list<Elemento*>::iterator itJugador);
		static Carta* FabricaDeElementosGraficos::generarCarta(list<Elemento*>::iterator itCarta);
	
};
