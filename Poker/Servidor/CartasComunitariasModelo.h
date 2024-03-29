#ifndef _CARTAS_COMUNITARIAS_MODELO_H_
#define _CARTAS_COMUNITARIAS_MODELO_H_

#include <list>
#include "CartaModelo.h"

class CartasComunitariasModelo
{
private:
	int id;
	list<CartaModelo*> cartas;

public:
	CartasComunitariasModelo(int id);
	virtual ~CartasComunitariasModelo(void);

	int getId();

	void agregarCarta(CartaModelo* carta);
	list<CartaModelo*> getCartas();
	void limpiar();
};

#endif //_CARTAS_COMUNITARIAS_MODELO_H_
