#ifndef _FUENTE_H__
#define _FUENTE_H__

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

		void setColor(Color* color);
		Color* getColor();
		void setTamanio(int tamanio);
		int getTamanio();

};

#endif //_FUENTE_H__

