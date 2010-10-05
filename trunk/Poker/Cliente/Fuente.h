#include <string.h>
#include "SDL_ttf.h"
#include "Color.h"
#include "UIException.h"

using namespace std;

class Fuente
{
	private:
		Color* color;
		int tamanio;
		string estilo;
		TTF_Font* fuente;

	public:
		Fuente(void);
		Fuente(string redgreenblue, int tamanio, string estilo);
		SDL_Surface* Fuente::obtenerSuperficieTexto(string texto, Color* fondo);
		virtual ~Fuente(void);

};

