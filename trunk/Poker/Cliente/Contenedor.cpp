#include "Contenedor.h"

Contenedor::Contenedor(void)
{
}

Contenedor::~Contenedor(void)
{
	for (list<ElementoGrafico*>::iterator it = this->elementos.begin();
		it != this->elementos.end(); it++) {
			delete(*it);
	}
	this->elementos.clear();
}

void Contenedor::agregarElementoGrafico(ElementoGrafico* elemento) {
	this->elementos.push_back(elemento);
}
