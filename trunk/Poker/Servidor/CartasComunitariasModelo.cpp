#include "CartasComunitariasModelo.h"
#include "PokerException.h"

CartasComunitariasModelo::CartasComunitariasModelo(int id)
{
	this->id = id;
}

CartasComunitariasModelo::~CartasComunitariasModelo(void)
{
}

void CartasComunitariasModelo::agregarCarta(CartaModelo* carta)
{
	if (this->cartas.size() > 4) {
		throw PokerException("No se pueden agregar mas cartas.");
	}
	carta->setPosicion(this->cartas.size()+1);
	carta->setVisible(true);
	this->cartas.push_back(carta);
}

list<CartaModelo*> CartasComunitariasModelo::getCartas()
{
	return this->cartas;
}
