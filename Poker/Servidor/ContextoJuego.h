#ifndef _CONTEXTOJUEGO_H_
#define _CONTEXTOJUEGO_H_

#include <list>
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
	TimerServidor timerMostrandoGanador;

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
	bool rondaTerminada;
	bool mostrandoCartas;
	bool sePuedePasar;
	bool rondaAllIn;
	list<string> nombresGanadores;
	static int segsTimeoutJugadores;

	static ContextoJuego* instancia;
	ContextoJuego(void);

	void chequearRondaTerminada();
	void chequearRondaAllIn();
	void chequearTimeoutJugador(int idJugador);

	void evaluarGanador();


public:	
	virtual ~ContextoJuego(void);

	static ContextoJuego* getInstancia();

	HANDLE getMutex();

	MesaModelo* getMesa();
	BoteModelo* getBote();
	MensajeModelo* getMensaje();
	CartasComunitariasModelo* getCartasComunitarias();

	JugadorModelo** getJugadores();
	JugadorModelo* getJugador(int idJugador);

	bool hayLugar();
	JugadorModelo* agregarJugador(int idCliente, string nombreJugador, 
		string nombreImagen, int fichas, bool esVirtual, bool esObservador);
	void quitarJugador(int idCliente);
	int getCantidadJugadoresActivos();
	int getCantidadJugadoresJugandoRonda();

	bool isTurnoJugador(int idJugador);
	bool isTurnoCliente(int idCliente);

	string getEscenarioJuego(int idCliente);
	string getEscenarioJuego(int idCliente, string mensaje);

	void iniciarRonda();
	void iniciarJuego();
	void mostrarFlop();
	void mostrarTurn();
	void mostrarRiver();
	void finalizarRonda();

	void igualarApuesta(int idCliente);
	bool puedeSubirApuesta(int idCliente, int fichas);
	bool puedeSubirApuesta(int idCliente);
	bool esApuestaValida(int idCliente, int fichas);
	void subirApuesta(int idCliente, int fichas);
	void noIr(int idCliente);
	bool puedePasar();
	void pasar(int idCliente);

	bool isRondaTerminada();
	bool isRondaAllIn();
	void setMostrandoCartas(bool mostrandoCartas);
	bool getMostrandoCartas();
	list<string> getNombresGanadores();
	int getMontoAIgualar();
	void chequearJugadorVirtual(int idCliente);

	int getTiempoEsperandoJugadores();
	void resetTimerEsperandoJugadores();
	bool isTiempoMostrandoGanadorCumplido();

	int idClienteToIdJugador(int idCliente);
	int idJugadorToIdCliente(int idJugador);


	/**
	* Para ser llamado al finalizar la aplicacion
	*/
	void finalizar();

};

#endif //_CONTEXTOJUEGO_H_
