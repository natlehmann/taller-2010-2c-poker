#include "ElementoGrafico.h"
#include "ServiciosGraficos.h"
#include "UIException.h"
#include "Carta.h"

#define SEPARACION_ENTRE_CARTAS	 1
#define SEPARACION_CON_BORDE_INF 80
#define SEPARACION_CON_BORDE_SUP 20

class CartasComunitarias: public ElementoGrafico
{
	private:
		
		Carta* carta1;
		Carta* carta2;
		Carta* carta3;
		Carta* carta4;
		Carta* carta5;

		void setearPosicionCartas();
	
	protected:
		virtual void dibujarSobreSup(SDL_Surface* superficie);

	public:
		void CartasComunitarias::setCarta(Carta* carta);
		CartasComunitarias(void);
		virtual ~CartasComunitarias(void);
};
