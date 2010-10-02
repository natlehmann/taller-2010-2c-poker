#include "ServiciosGraficos.h"
#include "UIException.h"
#include "RecursosAplicacion.h"
#include "UtilTiposDatos.h"
#include "UIException.h"

#include <math.h>

#define M_PI       3.14159265358979323846

const SDL_VideoInfo* ServiciosGraficos::videoInfo = NULL;

int ServiciosGraficos::bordeSuperior = -1;
int ServiciosGraficos::bordeInferior = -1;
int ServiciosGraficos::bordeDerecho = -1;
int ServiciosGraficos::bordeIzquierdo = -1;


ServiciosGraficos::ServiciosGraficos(void)
{
}

ServiciosGraficos::~ServiciosGraficos(void)
{
}

void ServiciosGraficos::dibujarElipse(SDL_Surface* superficie, 
			SDL_Rect* offset, Uint8 red, Uint8 green, Uint8 blue){

	Uint32 color = SDL_MapRGB(superficie->format, red, green, blue);

	if ( SDL_MUSTLOCK(superficie) ) {
		if ( SDL_LockSurface(superficie) < 0 ) {
			throw UIException("No se pudo bloquear la pantalla para dibujo", "E");
		}
	}

	int radioX = offset->w / 2;
	int radioY = offset->h / 2;
	int xMedio = radioX + offset->x;
	int yMedio = radioY + offset->y;

	int angulo = 0;

	while (angulo <= 180) {

		int coordX = (int)(radioX * cos((double)(M_PI * angulo / 180))) + xMedio;
		int coordY = yMedio - (int)(radioY * sin((double)(M_PI * angulo / 180)));

		ServiciosGraficos::putPixel(superficie, coordX, coordY, color);

		// se calcula la coordY para la mitad inferior de la elipse
		coordY = offset->y + offset->h - (coordY - offset->y);
		ServiciosGraficos::putPixel(superficie, coordX, coordY, color);

		angulo++;
	}

	if ( SDL_MUSTLOCK(superficie) ){
		SDL_UnlockSurface(superficie);
	}
}

const SDL_VideoInfo* ServiciosGraficos::getVideoInfo() {
	if (ServiciosGraficos::videoInfo == NULL) {
		ServiciosGraficos::videoInfo = SDL_GetVideoInfo();
	}
	return ServiciosGraficos::videoInfo;
}

SDL_Surface* ServiciosGraficos::crearSuperficie(int ancho, int alto) {

	return SDL_CreateRGBSurface (SDL_SWSURFACE, 
		ancho, alto,
		ServiciosGraficos::getVideoInfo()->vfmt->BitsPerPixel, 
        ServiciosGraficos::getVideoInfo()->vfmt->Rmask, 
		ServiciosGraficos::getVideoInfo()->vfmt->Gmask,
        ServiciosGraficos::getVideoInfo()->vfmt->Bmask, 
		ServiciosGraficos::getVideoInfo()->vfmt->Amask);
}

void ServiciosGraficos::putPixel(SDL_Surface* superficie, int x, int y, Uint32 pixel) {

	int bpp = superficie->format->BytesPerPixel;
	Uint8 *p = (Uint8 *)superficie->pixels + y * superficie->pitch + x * bpp;

	switch(bpp) {
	case 1:
		*p = pixel;
		break;
	case 2:
		*(Uint16 *)p = pixel;
		break;
	case 3:
		if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
			p[0] = (pixel >> 16) & 0xff;
			p[1] = (pixel >> 8) & 0xff;
			p[2] = pixel & 0xff;
		} else {
			p[0] = pixel & 0xff;
			p[1] = (pixel >> 8) & 0xff;
			p[2] = (pixel >> 16) & 0xff;
		}
		break;
	case 4:
		*(Uint32 *)p = pixel;
		break;
	}
}

int ServiciosGraficos::getTamanioCeldaHoriz() {
	int anchoReal = ServiciosGraficos::getVideoInfo()->current_w 
		- ServiciosGraficos::getBordeDerecho() - ServiciosGraficos::getBordeIzquierdo();
	return (int)(anchoReal / CELDAS_HORIZ);
}

int ServiciosGraficos::getTamanioCeldaVert() {
	int altoReal = ServiciosGraficos::getVideoInfo()->current_h 
		- ServiciosGraficos::getBordeSuperior() - ServiciosGraficos::getBordeInferior();
	return (int)(altoReal / CELDAS_VERT);
}

int ServiciosGraficos::getAnchoVentana() {
	return ServiciosGraficos::getVideoInfo()->current_w;
}

int ServiciosGraficos::getAltoVentana() {
	return ServiciosGraficos::getVideoInfo()->current_h;
}

int ServiciosGraficos::getBordeSuperior() {
	if (ServiciosGraficos::bordeSuperior < 0) {

		ServiciosGraficos::bordeSuperior = UtilTiposDatos::getEntero(
			RecursosAplicacion::getClienteConfigProperties()->get(
			"cliente.configuracion.pantalla.borde.superior"));

		if (ServiciosGraficos::bordeSuperior < 0) {
			throw UIException(
				"No se encuentra el valor del borde superior en el archivo de configuracion o no es un entero.","V");
		}
	}

	return ServiciosGraficos::bordeSuperior;
}

int ServiciosGraficos::getBordeInferior() {
	if (ServiciosGraficos::bordeInferior < 0) {

		ServiciosGraficos::bordeInferior = UtilTiposDatos::getEntero(
			RecursosAplicacion::getClienteConfigProperties()->get(
			"cliente.configuracion.pantalla.borde.inferior"));

		if (ServiciosGraficos::bordeInferior < 0) {
			throw UIException(
				"No se encuentra el valor del borde inferior en el archivo de configuracion o no es un entero.","V");
		}
	}

	return ServiciosGraficos::bordeInferior;
}

int ServiciosGraficos::getBordeDerecho() {
	if (ServiciosGraficos::bordeDerecho < 0) {

		ServiciosGraficos::bordeDerecho = UtilTiposDatos::getEntero(
			RecursosAplicacion::getClienteConfigProperties()->get(
			"cliente.configuracion.pantalla.borde.derecho"));

		if (ServiciosGraficos::bordeDerecho < 0) {
			throw UIException(
				"No se encuentra el valor del borde derecho en el archivo de configuracion o no es un entero.","V");
		}
	}

	return ServiciosGraficos::bordeDerecho;
}

int ServiciosGraficos::getBordeIzquierdo() {
	if (ServiciosGraficos::bordeIzquierdo < 0) {

		ServiciosGraficos::bordeIzquierdo = UtilTiposDatos::getEntero(
			RecursosAplicacion::getClienteConfigProperties()->get(
			"cliente.configuracion.pantalla.borde.izquierdo"));

		if (ServiciosGraficos::bordeIzquierdo < 0) {
			throw UIException(
				"No se encuentra el valor del borde izquierdo en el archivo de configuracion o no es un entero.","V");
		}
	}

	return ServiciosGraficos::bordeIzquierdo;
}