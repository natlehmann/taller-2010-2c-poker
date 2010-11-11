#include <time.h>
#include "Repartidor.h"
#include "UtilTiposDatos.h"

Repartidor::Repartidor(void)
{
	srand((unsigned int)time(NULL));
	instanciarCartas();
}

Repartidor::~Repartidor(void)
{
	borrarCartas();
}

CartaModelo* Repartidor::getCarta()
{
	if (!this->cantidadCartasDisponibles)
		return NULL;

	int numero = rand() % this->cantidadCartasDisponibles;
	
	list<CartaModelo*>::iterator it = this->cartas.begin();
	for (int i=0 ; i < numero ; i++) {
		it++;
	}
	CartaModelo* carta = *it;
	this->cartasQueSalieron.push_back(carta);
	this->cartas.erase(it);
	this->cantidadCartasDisponibles--;

	return carta;
}

string Repartidor::intToNumeroCarta(int numero)
{
	if (numero > 1 && numero < 11) {
		return UtilTiposDatos::enteroAString(numero);
	}
	switch (numero) {
		case 1:
			return "a";
		case 11:
			return "j";
		case 12:
			return "q";
		case 13:
			return "k";
	}
	return "";
}

void Repartidor::mezclar()
{
	borrarCartas();
	instanciarCartas();
}

void Repartidor::instanciarCartas()
{
	for (int i=1 ; i<14 ; i++) {
		this->cartas.push_back(new CartaModelo(intToNumeroCarta(i), "Corazon"));
	}
	for (int i=1 ; i<14 ; i++) {
		this->cartas.push_back(new CartaModelo(intToNumeroCarta(i), "Trebol"));
	}
	for (int i=1 ; i<14 ; i++) {
		this->cartas.push_back(new CartaModelo(intToNumeroCarta(i), "Diamante"));
	}
	for (int i=1 ; i<14 ; i++) {
		this->cartas.push_back(new CartaModelo(intToNumeroCarta(i), "Pica"));
	}
	this->cantidadCartasDisponibles = 52;
}

void Repartidor::borrarCartas()
{
	for (list<CartaModelo*>::iterator it = this->cartas.begin(); it != this->cartas.end(); ++it) {
		delete *it;
	}
	for (list<CartaModelo*>::iterator it = this->cartasQueSalieron.begin(); it != this->cartasQueSalieron.end(); ++it) {
		delete *it;
	}
	this->cartas.clear();
	this->cartasQueSalieron.clear();
	this->cantidadCartasDisponibles = 0;
}
