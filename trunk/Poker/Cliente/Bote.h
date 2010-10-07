#include "ElementoGrafico.h"
#include "Imagen.h"
#include "Etiqueta.h"

class Bote: public ElementoGrafico
{
	private:
		int total;

		Imagen* imagen;
		Etiqueta* etiqueta;

	public:
		Bote(void);
		virtual ~Bote(void);

		virtual void dibujarSobreSup(SDL_Surface* superficie);

		int getTotal();
		void setTotal(int total);
};
