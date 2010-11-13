#ifndef _COMPONENTE_PANEL_H__
#define _COMPONENTE_PANEL_H__

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

#include "ElementoGrafico.h"
#include "Imagen.h"
#include "Fuente.h"


#define MAXIMO_ANCHO_PANTALLA_PROP_TXT 800
#define MAXIMO_ALTO_PANTALLA_PROP_TXT 600

#define ALINEACION_HORIZ_DERECHA 1
#define ALINEACION_HORIZ_IZQUIERDA -1
#define ALINEACION_HORIZ_CENTRO 0

#define ALINEACION_VERT_ABAJO 1
#define ALINEACION_VERT_ARRIBA -1
#define ALINEACION_VERT_CENTRO 0

#define PADDING_HORIZ   20
#define PADDING_VERT	10

class Panel;

class ComponentePanel : public ElementoGrafico
{
protected:
	string texto;
	bool ajustarAlTexto;
	Fuente* fuente;
	bool habilitado;

	string idOperacion;
	string idComponentePanelRelacionado;

	Panel* panel;

	string colorFuente;
	int tamanioFuenteMax;
	string estiloFuente;

	void setearFuente();

public:
	ComponentePanel(string texto);
	virtual ~ComponentePanel(void);

	virtual ComponentePanel* clonar() = 0;

	string getTexto();
	virtual void setTexto(string texto);

	bool estaSobre();
	bool esClickIzquierdo();
	bool esClickDerecho();

	bool isHabilitado();
	void setHabilitado(bool habilitado);

	string getIdOperacion();
	void setIdOperacion(string idOperacion);

	string getIdComponentePanelRelacionado();
	void setIdComponentePanelRelacionado(string idComponentePanelRelacionado);

	void setPanel(Panel* panel);

	virtual bool checkClick(SDL_Surface* superficie) = 0;
	virtual bool checkOver(SDL_Surface* superficie) = 0;
	virtual bool checkWrite(SDL_Surface* superficie, SDL_Event* evento, int pressed) = 0;

	virtual void dibujarDown(SDL_Surface* superficie) = 0;
	virtual void dibujarUp(SDL_Surface* superficie) = 0;

};

#endif //_COMPONENTE_PANEL_H__
