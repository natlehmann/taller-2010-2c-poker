#ifndef _ADMINISTRADOR_JUGADORES_H_
#define _ADMINISTRADOR_JUGADORES_H_

#include <string>
#include "JugadorModelo.h"
#include "IteradorRonda.h"
#include "IteradorRondaActivos.h"
#include "IteradorRondaJugando.h"


using namespace std;

class AdministradorJugadores
{
private:
	JugadorModelo* jugadores[MAX_CANTIDAD_JUGADORES];

	// vector que se usa para mapear los ids de Cliente con los ids de Jugadores
	// Los indices del array (de 0 a 5) representan los ids de Jugador
	int idsJugadores[MAX_CANTIDAD_JUGADORES];

	// indice al array de jugadores (comenzando en 0)
	int jugadorTurno;

	int dealer;
	int dealerAnterior;

	void agregarJugadorAusente(int idJugador);
	JugadorModelo* getPrimerJugadorAusente();


public:
	AdministradorJugadores(void);
	virtual ~AdministradorJugadores(void);

	JugadorModelo* getJugador(int idCliente);
	JugadorModelo* getJugadorPorPosicion(int posicion);
	JugadorModelo** getJugadores();

	int idClienteToIdJugador(int idCliente);
	int idJugadorToIdCliente(int idJugador);

	void resetearJugadorTurno();
	IteradorRonda* getIteradorRonda();
	IteradorRondaActivos* getIteradorRondaActivos();
	IteradorRondaJugando* getIteradorRondaJugando();
	IteradorRondaJugando* getIteradorRondaJugando(int indiceInicial);
	void incrementarTurno();
	int getIndiceJugadorMano();

	void resetearDealer();
	void incrementarDealer();

	/* Se incrementa el dealer temporalmente, hasta que termine la ronda.
	   Para restituir el valor original se debe ejecutar resetearDealer(). */
	void incrementarDealerTemp();

	bool hayLugar();
	void agregarJugador(int idCliente, string nombreJugador, 
		string nombreImagen, int fichas, bool esVirtual);
	int getCantidadJugadoresActivos();

	bool isTurnoJugador(int idJugador);
	bool isTurnoCliente(int idCliente);
	bool isDealerJugador(int idJugador);

};

#endif //_ADMINISTRADOR_JUGADORES_H_

