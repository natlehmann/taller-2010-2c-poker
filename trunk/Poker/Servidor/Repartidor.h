#ifndef _REPARTIDOR_H__
#define _REPARTIDOR_H__

#include <list>
#include <string>
#include "CartaModelo.h"

using namespace std;

class Repartidor
{
private:
	list<CartaModelo*> cartas;
	int cantidadCartasDisponibles;

public:
	Repartidor(void);
	virtual ~Repartidor(void);

	CartaModelo* getCarta();
	void mezclar();

private:
	string intToNumeroCarta(int numero);
	void instanciarCartas();
	void borrarCartas();
};

#endif //_REPARTIDOR_H__
