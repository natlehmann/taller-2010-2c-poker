#include "ServiciosGraficos.h"
#include "UIException.h"

#include <math.h>

#define M_PI       3.14159265358979323846

const SDL_VideoInfo* ServiciosGraficos::videoInfo = NULL;

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
		coordY = offset->h - coordY;
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
	return (int)(ServiciosGraficos::getVideoInfo()->current_w / CELDAS_HORIZ);
}

int ServiciosGraficos::getTamanioCeldaVert() {
	return (int)(ServiciosGraficos::getVideoInfo()->current_h / CELDAS_VERT);
}

int ServiciosGraficos::getAnchoVentana() {
	return ServiciosGraficos::getVideoInfo()->current_w;
}

int ServiciosGraficos::getAltoVentana() {
	return ServiciosGraficos::getVideoInfo()->current_h;
}