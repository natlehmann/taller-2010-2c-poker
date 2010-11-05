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
#include "AdministradorJugadores.h"
#include <windows.h>


using namespace std;

class ContextoJuego
{
private:
	HANDLE mutex;
	TimerServidor timerEsperandoJugadores;

	AdministradorJugadores* admJugadores;

	MesaModelo* mesa;
	BoteModelo* bote;
	MensajeModelo* mensaje;
	CartasComunitariasModelo* cartasComunitarias;
	Repartidor* repartidor;

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

	void chequearRondaTerminada();

public:	
	virtual ~ContextoJuego(void);

	static ContextoJuego* getInstancia();

	HANDLE getMutex();

	MesaModelo* getMesa();
	BoteModelo* getBote();
	MensajeModelo* getMensaje();
	CartasComunitariasModelo* getCartasComunitarias();

	JugadorModelo** getJugadores();

	bool hayLugar();
	void agregarJugador(int idCliente);
	int getCantidadJugadoresActivos();
	int getCantidadJugadoresJugandoRonda();

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

};

#endif //_CONTEXTOJUEGO_H_
