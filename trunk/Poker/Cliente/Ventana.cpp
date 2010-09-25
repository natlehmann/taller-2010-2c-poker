#include "Ventana.h"

Ventana::Ventana(void)
{
}

Ventana::~Ventana(void)
{
}

void Ventana::dibujar(){
	// TODO: FALTA IMPLEMENTAR

	for (list<ElementoGrafico*>::iterator it = this->elementos.begin();
		it != this->elementos.end(); it++) {
			(*it)->dibujar();
	}
}
