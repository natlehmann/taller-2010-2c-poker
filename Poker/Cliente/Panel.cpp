#include "Panel.h"

Panel::Panel(void)
{
}

Panel::~Panel(void)
{
}

void Panel::dibujar(){
	// TODO: FALTA IMPLEMENTAR

	for (list<ElementoGrafico*>::iterator it = this->elementos.begin();
		it != this->elementos.end(); it++) {
			(*it)->dibujar();
	}
}
