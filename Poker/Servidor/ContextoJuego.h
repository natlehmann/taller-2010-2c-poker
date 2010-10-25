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

	int montoAIgualar;
	int cantidadJugadoresRonda;
	int posicionJugadorTurno;
	int posicionJugadorQueAbre;
	int posicionJugadorQueCierra;

	static ContextoJuego instancia;
	ContextoJuego(void);

public:	
	virtual ~ContextoJuego(void);

	static ContextoJuego* getInstancia();

	MesaModelo* getMesa();
	BoteModelo* getBote();
	MensajeModelo* getMensaje();
	CartasComunitariasModelo* getCartasComunitarias();
	JugadorModelo* getJugador(int idJugador);

	void agregarJugador(int idJugador);
	int getCantidadJugadoresActivos();
	int getCantidadJugadoresJugandoRonda();
	int getTurnoJugador();
	bool isTurnoJugador(int idJugador);

	void iniciarJuego();
	void mostrarFlop();
	void mostrarTurn();
	void mostrarRiver();
	int evaluarGanador();

	void igualarApuesta(int idJugador);
	void subirApuesta(int idJugador, int fichas);
	void noIr(int idJugador);

private:
	void calcularPosicionJugadorTurno();
	void calcularPosicionJugadorQueAbre();

};

#endif //_CONTEXTOJUEGO_H_
