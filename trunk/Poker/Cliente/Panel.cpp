#include "Panel.h"

Panel::Panel(void)
{
}

Panel::~Panel(void)
{
}

void Panel::dibujarSobreSup(SDL_Surface* superficie){
	// TODO: FALTA IMPLEMENTAR

	for (list<ElementoGrafico*>::iterator it = this->elementos.begin();
		it != this->elementos.end(); it++) {
			(*it)->dibujar(superficie);
	}
}
