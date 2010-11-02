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
#include "EstadoEsperandoJugadores.h"
#include "EstadoRondaCiega.h"
#include "EstadoRondaFlop.h"
#include "EstadoRondaTurn.h"
#include "EstadoRondaRiver.h"
#include "EstadoEvaluandoGanador.h"
#include "TimerServidor.h"
#include <windows.h>

#define MAX_CANTIDAD_JUGADORES	6

using namespace std;

class ContextoJuego
{
private:
	HANDLE mutex;
	TimerServidor timerEsperandoJugadores;

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
	EstadoEsperandoJugadores* esperandoJugadores;
	EstadoRondaCiega* rondaCiega;
	EstadoRondaFlop* rondaFlop;
	EstadoRondaTurn* rondaTurn;
	EstadoRondaRiver* rondaRiver;
	EstadoEvaluandoGanador* evaluandoGanador;

	int montoAIgualar;
	int cantidadJugadoresRonda;
	int posicionJugadorTurno;
	int posicionJugadorQueAbre;
	int posicionJugadorQueCierra;
	bool rondaTerminada;
	bool mostrandoCartas;

	static ContextoJuego instancia;
	ContextoJuego(void);

	void agregarJugadorAusente(int idJugador);
	int idClienteToIdJugador(int idCliente);
	int idJugadorToIdCliente(int idJugador);
	JugadorModelo* getPrimerJugadorAusente();
	void chequearRondaTerminada();

public:	
	virtual ~ContextoJuego(void);

	static ContextoJuego* getInstancia();

	HANDLE getMutex();

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
	bool isTurnoJugador(int idJugador);
	bool isTurnoCliente(int idCliente);

	string getEscenarioJuego(int idCliente);

	void iniciarRonda();
	void iniciarJuego();
	void mostrarFlop();
	void mostrarTurn();
	void mostrarRiver();
	int evaluarGanador();
	void finalizarRonda();

	void igualarApuesta(int idCliente);
	void subirApuesta(int idCliente, int fichas);
	void noIr(int idCliente);

	bool isRondaTerminada();
	void setMostrandoCartas(bool mostrandoCartas);
	bool getMostrandoCartas();

	int getTiempoEsperandoJugadores();

	/**
	* Para ser llamado al finalizar la aplicacion
	*/
	void finalizar();

private:
	void calcularPosicionJugadorTurno();
	void calcularPosicionJugadorQueAbre();

};

#endif //_CONTEXTOJUEGO_H_
