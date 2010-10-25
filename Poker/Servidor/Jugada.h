#ifndef _JUGADA_H__
#define _JUGADA_H__

#include <vector>
#include <list>
#include "CartaModelo.h"

using namespace std;

class Jugada
{
private:
	vector<CartaModelo*> cartas;

	static const int valorPoker = 7;
	static const int valorFull = 6;
	static const int valorColor = 5;
	static const int valorEscalera = 4;
	static const int valorPierna = 3;
	static const int valorParDoble = 2;
	static const int valorPar = 1;

public:
	Jugada(void);
	Jugada(vector<CartaModelo*> cartas);
	virtual ~Jugada(void);

	vector<CartaModelo*> getCartas() const;
	void setCartas(vector<CartaModelo*> cartas);

	void agregarCarta(CartaModelo* carta);
	void agregarCartas(list<CartaModelo*> cartas);

	double getValorJugada();

private:
	static bool compararCartas(CartaModelo* carta1, CartaModelo* carta2);
	double calcularValorJugada(int, int=0, int=0, int=0, int=0, int=0);

	double isPoker();
	double isFull();
	double isColor(bool& escaleraColor);
	double isEscalera(vector<CartaModelo*>& cartas);
	double isPierna();
	double isParDoble();
	double isPar();
	double getCartaMasAlta();

};

#endif //_JUGADA_H__
