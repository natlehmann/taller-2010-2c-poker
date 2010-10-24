#ifndef _BOTE_H_
#define _BOTE_H_

#include "ElementoGrafico.h"
#include "Imagen.h"
#include "Etiqueta.h"
#include "ServiciosGraficos.h"
#include "RecursosAplicacion.h"

#define BOTE_ALTO_ETIQUETA 0.18
#define RELACION_ANCHO 0.8
#define RELACION_ALTO 0.4

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

#endif //_BOTE_H_
