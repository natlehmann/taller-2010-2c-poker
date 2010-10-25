#include "Jugada.h"
#include "MensajesUtil.h"
#include "PokerException.h"
#include <algorithm>

Jugada::Jugada()
{
}

Jugada::Jugada(vector<CartaModelo*> cartas)
{
	this->cartas = cartas;
}

Jugada::~Jugada(void)
{
	//for (vector<CartaModelo*>::iterator it = this->cartas.begin(); it != this->cartas.end(); ++it) {
	//	delete *it;
	//}
	this->cartas.clear();
}

vector<CartaModelo*> Jugada::getCartas() const
{
	return cartas;
}

void Jugada::setCartas(vector<CartaModelo*> cartas)
{
	this->cartas = cartas;
}

void Jugada::agregarCarta(CartaModelo* carta)
{
	this->cartas.push_back(carta);
}

void Jugada::agregarCartas(list<CartaModelo*> cartas)
{
	for (list<CartaModelo*>::iterator it = cartas.begin(); it != cartas.end(); ++it) {
		this->cartas.push_back(*it);
	}
}

double Jugada::getValorJugada()
{
	if (this->cartas.size() < 5 || this->cartas.size() > 7) {
		throw PokerException("La jugada debe tener entre 5 y 7 cartas.");
	}

	// Ordenamos las cartas por numero, en orden ascendente.
	sort(this->cartas.begin(), this->cartas.end(), compararCartas);

	double valorColor = 0;
	bool escaleraColor = false;
	double valorJugada = isColor(escaleraColor);
	if (escaleraColor) {
		return valorJugada;
	} else {
		valorColor = valorJugada;
	}

	valorJugada = isPoker();
	if (valorJugada) {
		return valorJugada;
	}

	valorJugada = isFull();
	if (valorJugada) {
		return valorJugada;
	}

	if (valorColor) {
		return valorColor;
	}

	valorJugada = isEscalera(this->cartas);
	if (valorJugada) {
		return valorJugada;
	}

	valorJugada = isPierna();
	if (valorJugada) {
		return valorJugada;
	}

	valorJugada = isParDoble();
	if (valorJugada) {
		return valorJugada;
	}

	valorJugada = isPar();
	if (valorJugada) {
		return valorJugada;
	}

	return getCartaMasAlta();
}

bool Jugada::compararCartas(CartaModelo* carta1, CartaModelo* carta2)
{
	return (carta1->getValorNumerico() < carta2->getValorNumerico());
}

double Jugada::isPoker()
{
	int cartaDelPoker = 0;
	int cartaMasAlta = this->cartas.back()->getValorNumerico();
	int cartasConsecutivas = 1;

	int cartaAnterior = -1;
	for (vector<CartaModelo*>::iterator it = this->cartas.begin(); it != this->cartas.end(); ++it) {
		int carta = (*it)->getValorNumerico();
		if (carta == cartaAnterior) {
			cartasConsecutivas++;
			if (cartasConsecutivas > 3) {
				cartaDelPoker = carta;
				if (cartaDelPoker == cartaMasAlta) {
					cartaMasAlta = this->cartas.at(this->cartas.size()-5)->getValorNumerico();
				}
				return calcularValorJugada(valorPoker, cartaDelPoker, cartaMasAlta);
			}
		} else {
			cartasConsecutivas = 1;
		}
		cartaAnterior = carta;
	}
	return 0;
}

double Jugada::isFull()
{
	int cartaDeLaPierna = 0;
	int cartasConsecutivas = 1;
	bool pierna = false;

	int cartaAnterior = -1;
	for (vector<CartaModelo*>::reverse_iterator it = this->cartas.rbegin(); it != this->cartas.rend(); ++it) {
		int carta = (*it)->getValorNumerico();
		if (carta == cartaAnterior) {
			cartasConsecutivas++;
			if (cartasConsecutivas > 2) {
				pierna = true;
				cartaDeLaPierna = carta;
				break;
			}
		} else {
			cartasConsecutivas = 1;
		}
		cartaAnterior = carta;
	}

	if (pierna) {
		cartaAnterior = -1;
		for (vector<CartaModelo*>::reverse_iterator it = this->cartas.rbegin(); it != this->cartas.rend(); ++it) {
			int carta = (*it)->getValorNumerico();
			if (carta == cartaAnterior && carta != cartaDeLaPierna) {
				cartasConsecutivas++;
				if (cartasConsecutivas > 1) {
					return calcularValorJugada(valorFull, cartaDeLaPierna, carta);
				}
			} else {
				cartasConsecutivas = 1;
			}
			cartaAnterior = carta;
		}
	}
	return 0;
}

double Jugada::isColor(bool& escaleraColor)
{
	vector<CartaModelo*> cartasColor;
	string palos[4] = {"Corazon", "Pica", "Trebol", "Diamante"};

	for (int i=0 ; i<4 ; i++) {
		cartasColor.clear();
		for (vector<CartaModelo*>::iterator it = this->cartas.begin(); it != this->cartas.end(); ++it) {
			CartaModelo* carta = *it;
			if (MensajesUtil::sonIguales(carta->getPalo(), palos[i])) {
				cartasColor.push_back(carta);
			}
		}
		if (cartasColor.size() > 4) {
			double valorEscalera = isEscalera(cartasColor);
			if (valorEscalera) {
				escaleraColor = true;
				return valorEscalera + calcularValorJugada(valorColor);
			}
			int valorCarta1 = cartasColor.back()->getValorNumerico();
			cartasColor.pop_back();
			int valorCarta2 = cartasColor.back()->getValorNumerico();
			cartasColor.pop_back();
			int valorCarta3 = cartasColor.back()->getValorNumerico();
			cartasColor.pop_back();
			int valorCarta4 = cartasColor.back()->getValorNumerico();
			cartasColor.pop_back();
			int valorCarta5 = cartasColor.back()->getValorNumerico();
			cartasColor.clear();
			return calcularValorJugada(valorColor, valorCarta1, valorCarta2, valorCarta3, valorCarta4, valorCarta5);
		}
	}
	return 0;
}

double Jugada::isEscalera(vector<CartaModelo*>& vectorCartas)
{
	bool escalera = false;
	int cartaMasAlta = 0;
	int cartasConsecutivas = 1;
	vector<int> numerosDeCartas;

	// Si tengo un as puede hacer escalera con 2, 3, 4, 5 o 10, j, q, k
	if (vectorCartas.back()->getValorNumerico() == 14) {
		numerosDeCartas.push_back(1);
	}
	for (vector<CartaModelo*>::iterator it = vectorCartas.begin(); it != vectorCartas.end(); ++it) {
		numerosDeCartas.push_back((*it)->getValorNumerico());
	}

	int numeroDeCartaAnterior = -1;
	for (vector<int>::iterator it = numerosDeCartas.begin(); it != numerosDeCartas.end(); ++it) {
		int numeroDeCarta = *it;
		if (numeroDeCarta == numeroDeCartaAnterior + 1) {
			cartasConsecutivas++;
			if (cartasConsecutivas > 4) {
				escalera = true;
				cartaMasAlta = numeroDeCarta;
			}
		} else {
			cartasConsecutivas = 1;
		}
		numeroDeCartaAnterior = numeroDeCarta;
	}
	if (escalera) {
		return calcularValorJugada(valorEscalera,cartaMasAlta);
	}
	return 0;
}

double Jugada::isPierna()
{
	int cartaDeLaPierna = 0;
	int cartaMasAlta = this->cartas.at(this->cartas.size()-1)->getValorNumerico();
	int segundaCartaMasAlta = this->cartas.at(this->cartas.size()-2)->getValorNumerico();
	int cartasConsecutivas = 1;

	int cartaAnterior = -1;
	for (vector<CartaModelo*>::iterator it = this->cartas.begin(); it != this->cartas.end(); ++it) {
		int carta = (*it)->getValorNumerico();
		if (carta == cartaAnterior) {
			cartasConsecutivas++;
			if (cartasConsecutivas > 2) {
				cartaDeLaPierna = carta;
				if (cartaDeLaPierna == cartaMasAlta) {
					cartaMasAlta = this->cartas.at(this->cartas.size()-4)->getValorNumerico();;
				}
				if (cartaDeLaPierna == segundaCartaMasAlta) {
					segundaCartaMasAlta = this->cartas.at(this->cartas.size()-5)->getValorNumerico();
				}
				return calcularValorJugada(valorPierna, cartaDeLaPierna, cartaMasAlta, segundaCartaMasAlta);
			}
		} else {
			cartasConsecutivas = 1;
		}
		cartaAnterior = carta;
	}
	return 0;
}

double Jugada::isParDoble()
{
	int cartaParAlto = 0;
	int cartaParBajo = 0;
	int cartaMasAlta = this->cartas.back()->getValorNumerico();
	int cartasConsecutivas = 1;
	bool par = false;

	int cartaAnterior = -1;
	for (vector<CartaModelo*>::reverse_iterator it = this->cartas.rbegin(); it != this->cartas.rend(); ++it) {
		int carta = (*it)->getValorNumerico();
		if (carta == cartaAnterior) {
			cartasConsecutivas++;
			if (cartasConsecutivas > 1) {
				if (par) {
					cartaParBajo = carta;
					if (cartaParAlto == cartaMasAlta) {
						if (cartaParBajo == this->cartas.at(this->cartas.size()-3)->getValorNumerico()) {
							cartaMasAlta = this->cartas.at(this->cartas.size()-5)->getValorNumerico();
						} else {
							cartaMasAlta = this->cartas.at(this->cartas.size()-3)->getValorNumerico();
						}
					}
					return calcularValorJugada(valorParDoble, cartaParAlto, cartaParBajo, cartaMasAlta);
				} else {
					par = true;
					cartaParAlto = carta;
				}
			}
		} else {
			cartasConsecutivas = 1;
		}
		cartaAnterior = carta;
	}
	return 0;
}

double Jugada::isPar()
{
	int cartaPar = 0;
	int cartaMasAlta = this->cartas.at(this->cartas.size()-1)->getValorNumerico();
	int segundaCartaMasAlta = this->cartas.at(this->cartas.size()-2)->getValorNumerico();
	int terceraCartaMasAlta = this->cartas.at(this->cartas.size()-3)->getValorNumerico();
	int cartasConsecutivas = 1;

	int cartaAnterior = -1;
	for (vector<CartaModelo*>::iterator it = this->cartas.begin(); it != this->cartas.end(); ++it) {
		int carta = (*it)->getValorNumerico();
		if (carta == cartaAnterior) {
			cartasConsecutivas++;
			if (cartasConsecutivas > 1) {
				cartaPar = carta;
				if (cartaPar == cartaMasAlta) {
					cartaMasAlta = this->cartas.at(this->cartas.size()-3)->getValorNumerico();
					segundaCartaMasAlta = this->cartas.at(this->cartas.size()-4)->getValorNumerico();
					terceraCartaMasAlta = this->cartas.at(this->cartas.size()-5)->getValorNumerico();
				} else {
					if (cartaPar == segundaCartaMasAlta) {
						segundaCartaMasAlta = this->cartas.at(this->cartas.size()-4)->getValorNumerico();
						terceraCartaMasAlta = this->cartas.at(this->cartas.size()-5)->getValorNumerico();
					} else {
						if (cartaPar == terceraCartaMasAlta) {
							terceraCartaMasAlta = this->cartas.at(this->cartas.size()-5)->getValorNumerico();
						}
					}
				}
				return calcularValorJugada(valorPar, cartaPar, cartaMasAlta, segundaCartaMasAlta, terceraCartaMasAlta);
			}
		} else {
			cartasConsecutivas = 1;
		}
		cartaAnterior = carta;
	}
	return 0;
}

double Jugada::getCartaMasAlta() 
{
	return calcularValorJugada(0, this->cartas.at(this->cartas.size()-1)->getValorNumerico(),
								  this->cartas.at(this->cartas.size()-2)->getValorNumerico(),
								  this->cartas.at(this->cartas.size()-3)->getValorNumerico(),
								  this->cartas.at(this->cartas.size()-4)->getValorNumerico(),
								  this->cartas.at(this->cartas.size()-5)->getValorNumerico());
}

double Jugada::calcularValorJugada(int valorJuego, int valorCarta1, int valorCarta2, 
								int valorCarta3, int valorCarta4, int valorCarta5)
{
	return (double)valorJuego * 10000000000 +
		    (double)valorCarta1 * 100000000 +
			 (double)valorCarta2 *  1000000 +
			  (double)valorCarta3 *   10000 +
			   (double)valorCarta4 *    100 +
			    (double)valorCarta5;
}
