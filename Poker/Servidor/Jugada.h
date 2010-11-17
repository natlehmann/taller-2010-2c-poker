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

	bool escaleraColor;
	bool poker;
	bool full;
	bool color;
	bool escalera;
	bool pierna;
	bool parDoble;
	bool par;

public:
	static const double valorJugadaPromedio;
	static const double valorParPromedio;
	static const double valorParDoblePromedio;

	Jugada(void);
	Jugada(vector<CartaModelo*> cartas);
	virtual ~Jugada(void);

	vector<CartaModelo*> getCartas() const;
	void setCartas(vector<CartaModelo*> cartas);

	void agregarCarta(CartaModelo* carta);
	void agregarCartas(list<CartaModelo*> cartas);

	double getValorJugada();

	bool isEscaleraColor();
	bool isPoker();
	bool isFull();
	bool isColor();
	bool isEscalera();
	bool isPierna();
	bool isParDoble();
	bool isPar();

private:
	static bool compararCartas(CartaModelo* carta1, CartaModelo* carta2);
	double calcularValorJugada(int, int=0, int=0, int=0, int=0, int=0);

	double getPoker();
	double getFull();
	double getColor(bool& escaleraColor);
	double getEscalera(vector<CartaModelo*>& cartas);
	double getPierna();
	double getParDoble();
	double getPar();
	double getCartaMasAlta();

};

#endif //_JUGADA_H__
