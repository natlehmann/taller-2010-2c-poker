#include "Fuente.h"

Fuente::Fuente(void)
{
	this->fuente = NULL;
	this->estilo = "";
	this->color = NULL;
	this->tamanio = 0;
}

Fuente::Fuente(string redgreenblue, int tamanio, string estilo)
{
	this->fuente = TTF_OpenFont(estilo.c_str(), tamanio);
	
	if (!this->fuente)
		throw UIException("Estilo invalido al construir la fuente del texto","E");

	this->estilo = estilo;
	this->tamanio = tamanio;
	this->color = new Color(redgreenblue);
}

SDL_Surface* Fuente::obtenerSuperficieTexto(string texto, Color* fondo)
{
	if (fondo)
		return TTF_RenderText_Shaded(this->fuente, texto.c_str(), this->color->toSDL_Color(), fondo->toSDL_Color());
	else
		return TTF_RenderText_Solid(this->fuente, texto.c_str(), this->color->toSDL_Color());
}

Fuente::~Fuente(void)
{

}
