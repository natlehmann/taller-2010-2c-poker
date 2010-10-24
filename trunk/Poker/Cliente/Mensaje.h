#ifndef _MENSAJE_H_
#define _MENSAJE_H_

#include "ElementoGrafico.h"
#include "Etiqueta.h"
#include "ServiciosGraficos.h"
#include "RecursosAplicacion.h"

class Mensaje : public ElementoGrafico
{
private:
	Etiqueta* etiqueta;
	bool visible;

public:
	Mensaje(string texto);
	virtual ~Mensaje(void);

	virtual void dibujarSobreSup(SDL_Surface* superficie);

	string getTexto();
	void setTexto(string texto);

	bool isVisible();
	void setVisible(bool visible);
};

#endif //_MENSAJE_H_
