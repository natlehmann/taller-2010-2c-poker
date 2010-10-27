#ifndef _CONTEXTOJUEGO_H_
#define _CONTEXTOJUEGO_H_

#include <vector>
#include <string>
#include "MesaModelo.h"
#include "BoteModelo.h"
#include "MensajeModelo.h"
#include "JugadorModelo.h"
#include "CartasComunitariasModelo.h"
#include "Repartidor.h"
#include "EstadoJuego.h"

#define MAX_CANTIDAD_JUGADORES	6

using namespace std;

class ContextoJuego
{
private:
	MesaModelo* mesa;
	BoteModelo* bote;
	MensajeModelo* mensaje;
	CartasComunitariasModelo* cartasComunitarias;
	vector<JugadorModelo*> jugadores;
	Repartidor* repartidor;

	// vector que se usa para mapear los ids de Cliente con los ids de Jugadores
	// Los indices del array (de 0 a 5) representan los ids de Jugador
	int idsJugadores[MAX_CANTIDAD_JUGADORES];

	EstadoJuego* estado;

	int montoAIgualar;
	int cantidadJugadoresRonda;
	int posicionJugadorTurno;
	int posicionJugadorQueAbre;
	int posicionJugadorQueCierra;

	static ContextoJuego instancia;
	ContextoJuego(void);

	void agregarJugadorAusente(int idJugador);
	int idClienteToIdJugador(int idCliente);
	int idJugadorToIdCliente(int idJugador);
	JugadorModelo* getPrimerJugadorAusente();

public:	
	virtual ~ContextoJuego(void);

	static ContextoJuego* getInstancia();

	MesaModelo* getMesa();
	BoteModelo* getBote();
	MensajeModelo* getMensaje();
	CartasComunitariasModelo* getCartasComunitarias();

	JugadorModelo* getJugador(int idCliente);
	JugadorModelo* getJugadorPorPosicion(int posicion);
	vector<JugadorModelo*> getJugadores();

	bool hayLugar();
	void agregarJugador(int idCliente);
	int getCantidadJugadoresActivos();
	int getCantidadJugadoresJugandoRonda();
	int getTurnoJugador();
	bool isTurnoJugador(int idCliente);

	string getEscenarioJuego(int idCliente);

	void iniciarJuego();
	void mostrarFlop();
	void mostrarTurn();
	void mostrarRiver();
	int evaluarGanador();
	void finalizarRonda();

	void igualarApuesta(int idCliente);
	void subirApuesta(int idCliente, int fichas);
	void noIr(int idCliente);

private:
	void calcularPosicionJugadorTurno();
	void calcularPosicionJugadorQueAbre();

};

#endif //_CONTEXTOJUEGO_H_
