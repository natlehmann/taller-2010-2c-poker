#include "ServiciosGraficos.h"
#include "UIException.h"
#include "RecursosCliente.h"
#include "UtilTiposDatos.h"
#include "MensajesUtil.h"
#include "UIException.h"
#include <list>
#include <math.h>

#define M_PI       3.14159265358979323846

const SDL_VideoInfo* ServiciosGraficos::videoInfo = NULL;

int ServiciosGraficos::bordeSuperior = -1;
int ServiciosGraficos::bordeInferior = -1;
int ServiciosGraficos::bordeDerecho = -1;
int ServiciosGraficos::bordeIzquierdo = -1;

int ServiciosGraficos::altoVentana = -1;
int ServiciosGraficos::anchoVentana = -1;


ServiciosGraficos::ServiciosGraficos(void)
{
}

ServiciosGraficos::~ServiciosGraficos(void)
{
}

void ServiciosGraficos::lock(SDL_Surface* superficie) {
	if ( SDL_MUSTLOCK(superficie) ) {
		if ( SDL_LockSurface(superficie) < 0 ) {
			throw UIException("No se pudo bloquear la pantalla para dibujo", "E");
		}
	}
}

void ServiciosGraficos::unlock(SDL_Surface* superficie) {
	if ( SDL_MUSTLOCK(superficie) ){
		SDL_UnlockSurface(superficie);
	}
}

void ServiciosGraficos::dibujarContorno(SDL_Surface* superficie, 
			SDL_Rect* offset, Color* color){

	lock(superficie);

	Uint32 colorUint32 = color->toUint32(superficie);

	// linea superior e inferior
	for(int x = offset->x; x < (offset->x + offset->w); x++) {
		ServiciosGraficos::putPixel(superficie, x, offset->y, colorUint32);
		ServiciosGraficos::putPixel(superficie, x, offset->y + offset->h - 1, colorUint32);
	}

	// en el medio
	for (int y = offset->y + 1; y < (offset->y + offset->h - 1); y++) {
		ServiciosGraficos::putPixel(superficie, offset->x, y, colorUint32);
		ServiciosGraficos::putPixel(superficie, offset->x + offset->w - 1, y, colorUint32);
	}

	unlock(superficie);
}

void ServiciosGraficos::dibujarElipse(SDL_Surface* superficie, 
			SDL_Rect* offset, Color* color){

	lock(superficie);

	int radioX = offset->w / 2;
	int radioY = offset->h / 2;
	int xMedio = radioX + offset->x;
	int yMedio = radioY + offset->y;

	int angulo = 0;

	while (angulo <= 180) {

		int coordX = (int)(radioX * cos((double)(M_PI * angulo / 180))) + xMedio;
		int coordY = yMedio - (int)(radioY * sin((double)(M_PI * angulo / 180)));

		ServiciosGraficos::putPixel(superficie, coordX, coordY, color->toUint32(superficie));

		// se calcula la coordY para la mitad inferior de la elipse
		coordY = offset->y + offset->h - (coordY - offset->y);
		ServiciosGraficos::putPixel(superficie, coordX, coordY, color->toUint32(superficie));

		angulo++;
	}

	unlock(superficie);
}



void ServiciosGraficos::merge(SDL_Surface* origen, SDL_Surface* destino, 
	SDL_Rect* offsetDestino, Uint32 colorMascara){

	   lock(origen);
	   lock(destino);

	   for (int y = 0; y < origen->h; y++) {

		   for (int x = 0; x < origen->w; x++) {

			   Uint32 pixel = ServiciosGraficos::getPixel(origen, x, y);
			   if (pixel != colorMascara) {

				   ServiciosGraficos::putPixel(destino, x + offsetDestino->x, 
					   y + offsetDestino->y, pixel);
			   }
		   }
	   }

	   unlock(origen);
	   unlock(destino);
}

void ServiciosGraficos::copiarDentro(SDL_Surface* origen, 
									 SDL_Surface* destino, Color* colorFigura){

	 lock(origen);
	 lock(destino);

	 int linea = 0;

	 Uint32 pixelLimite = colorFigura->toUint32(destino);

	 int memoriaInicio = -1;
	 int memoriaFin = -1;

	 while (linea < destino->h) {
		 
		 int inicio = ServiciosGraficos::findFirstPorLinea(
			 destino, 0, destino->w, linea, pixelLimite);

		 // correccion para lineas en las que no encuentra el pixel limite: se toma el mismo
		 // de la linea anterior
		 if (inicio >= 0) {
			 memoriaInicio = inicio;
		 
		 } else {
			 if (memoriaInicio >= 0) {
				inicio = memoriaInicio;
			}
		 }

		 if (inicio >= 0 && inicio < destino->w) {

			 Uint32 pixelInicio = ServiciosGraficos::getPixel(destino, inicio, linea);
			 // avanzo todos los pixels del color
			 while(inicio < destino->w && pixelInicio == pixelLimite) {
				 inicio++;
				 pixelInicio = ServiciosGraficos::getPixel(destino, inicio, linea);
			 }

			 if (inicio < destino->w) {

				 int fin = ServiciosGraficos::findLastPorLinea(
					 destino, inicio, destino->w, linea, pixelLimite);

				 // correccion para lineas en las que no encuentra el pixel limite: se toma el mismo
				 // de la linea anterior
				 if (fin >= 0) {
					 memoriaFin = fin;
				 
				 } else {
					 if (memoriaFin >= 0) {
						fin = memoriaFin;
					}
				 }

				 if (fin > 0) {

					 //copiar pixels de origen a destino entre inicio y fin
					 for (int x = inicio; x < fin; x++) {
						 ServiciosGraficos::putPixel(destino, x, linea, 
							 ServiciosGraficos::getPixel(origen, x, linea));
					 }
				 
				 }
			 }
		 }

		 linea++;
	 }

	 unlock(origen);
	 unlock(destino);
}

/**
* Busca un pixel dentro de una linea de una superficie y devuelve la posicion del primer
* match, si es que existe. Si no, devuelve -1.
* Busca desde xDesde inclusive hasta xHasta exclusive.
*/
int ServiciosGraficos::findFirstPorLinea(SDL_Surface* superficie, 
			int xDesde, int xHasta, int linea, Uint32 pixel){

	int posX = -1;
	int x = xDesde;

	while (x < xHasta && posX == -1) {
		Uint32 pixelEnc = ServiciosGraficos::getPixel(superficie, x, linea);
		if (pixelEnc == pixel) {
			posX = x;
		}
		x++;
	}

	return posX;
}

/**
* Busca un pixel dentro de una linea de una superficie comenzando desde el final
* y devuelve la posicion del primer
* match, si es que existe. Si no, devuelve -1.
* Busca desde xDesde inclusive hasta xHasta exclusive.
*/
int ServiciosGraficos::findLastPorLinea(SDL_Surface* superficie, 
			int xDesde, int xHasta, int linea, Uint32 pixel){

	int posX = -1;
	int x = xHasta - 1;

	while (x >= xDesde && posX == -1) {
		Uint32 pixelEnc = ServiciosGraficos::getPixel(superficie, x, linea);
		if (pixelEnc == pixel) {
			posX = x;
		}
		x--;
	}

	return posX;
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


Uint32 ServiciosGraficos::getPixel(SDL_Surface* surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;

    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        return *p;

    case 2:
        return *(Uint16 *)p;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;

    case 4:
        return *(Uint32 *)p;

    default:
        return 0;
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

	if (ServiciosGraficos::anchoVentana < 0) {

		string configPantalla = RecursosCliente::getConfig()->get("cliente.configuracion.pantalla");
		list<string> medidas = MensajesUtil::split(configPantalla, "x");

		if (medidas.size() != 2) {
			throw UIException("La configuracion de pantalla esta incorrectamente seteada en el archivo 'config.ini'.", "V");
		}

		ServiciosGraficos::anchoVentana = UtilTiposDatos::getEntero(medidas.front());
		ServiciosGraficos::altoVentana = UtilTiposDatos::getEntero(medidas.back());
	}

	return ServiciosGraficos::anchoVentana;
}

int ServiciosGraficos::getAltoVentana() {

	if (ServiciosGraficos::altoVentana < 0) {

		string configPantalla = RecursosCliente::getConfig()->get("cliente.configuracion.pantalla");
		list<string> medidas = MensajesUtil::split(configPantalla, "x");

		if (medidas.size() != 2) {
			throw UIException("La configuracion de pantalla esta incorrectamente seteada en el archivo 'config.ini'.", "V");
		}

		ServiciosGraficos::anchoVentana = UtilTiposDatos::getEntero(medidas.front());
		ServiciosGraficos::altoVentana = UtilTiposDatos::getEntero(medidas.back());
	}

	return ServiciosGraficos::altoVentana;

}

int ServiciosGraficos::getBordeSuperior() {
	if (ServiciosGraficos::bordeSuperior < 0) {

		ServiciosGraficos::bordeSuperior = UtilTiposDatos::getEntero(
			RecursosCliente::getConfig()->get(
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
			RecursosCliente::getConfig()->get(
			"cliente.configuracion.pantalla.borde.inferior"));

		if (ServiciosGraficos::getAltoVentana() >= ALTO_PANTALLA_LIMITE 
			&& ServiciosGraficos::getAnchoVentana() >= ANCHO_PANTALLA_LIMITE) {
				ServiciosGraficos::bordeInferior += CORRECCION_BORDE_VERTICAL;
		}

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
			RecursosCliente::getConfig()->get(
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
			RecursosCliente::getConfig()->get(
			"cliente.configuracion.pantalla.borde.izquierdo"));

		if (ServiciosGraficos::bordeIzquierdo < 0) {
			throw UIException(
				"No se encuentra el valor del borde izquierdo en el archivo de configuracion o no es un entero.","V");
		}
	}

	return ServiciosGraficos::bordeIzquierdo;
}

SDL_Surface* ServiciosGraficos::resizeSuperficie(SDL_Surface* superficie, int ancho, int alto)
{
	if (ancho == 0 || alto == 0 || superficie == NULL || superficie->w == 0 || superficie->h == 0)
		return NULL;

    SDL_Surface* superficieModificada = crearSuperficie(ancho, alto);
    if (superficieModificada == NULL)
		return NULL;

	double factorX = (static_cast<double>(ancho) / static_cast<double>(superficie->w));
	double factorY = (static_cast<double>(alto) / static_cast<double>(superficie->h));

    for (Sint32 y = 0; y < superficie->h; y++)
        for (Sint32 x = 0; x < superficie->w; x++)
            for (Sint32 j = 0; j < factorY; ++j)
                for (Sint32 i = 0; i < factorX; ++i)
					putPixel(superficieModificada, static_cast<Sint32>(factorX * x) + i, static_cast<Sint32>(factorY * y) + j, getPixel(superficie, x, y));

    return superficieModificada;
}
