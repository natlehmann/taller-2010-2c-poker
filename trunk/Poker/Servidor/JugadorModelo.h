#ifndef _JUGADOR_MODELO_H_
#define _JUGADOR_MODELO_H_

#include <string>
#include "CartaModelo.h"
#include "TimerServidor.h"

#define NOMBRE_IMAGEN ""

using namespace std;

class JugadorModelo
{
private:
	int id;
	string nombre;
	int fichas;
	int posicion;
	string password;
	string nombreImagen;
	CartaModelo* carta1;
	CartaModelo* carta2;
	int apuesta;
	bool activo;
	bool ausente;
	bool jugandoRonda;
	bool dealer;
	bool esVirtual;
	bool observador;
	bool allIn;
	TimerServidor timer;

public:

	JugadorModelo(int id, int posicion);
	JugadorModelo(int id, string nombre, int fichas, int posicion, string password, string nombreImagen = NOMBRE_IMAGEN);
	virtual ~JugadorModelo(void);

	int getId();
	void setId(int id);

	string getNombre();
	void setNombre(string nombre);

	int getFichas();
	void setFichas(int fichas);

	int getPosicion();
	void setPosicion(int posicion);

	string getPassword();
	void setPassword(string Password);

	string getNombreImagen();
	void setNombreImagen(string nombreImagen);

	CartaModelo* getCarta1();
	void setCarta1(CartaModelo* carta);

	CartaModelo* getCarta2();
	void setCarta2(CartaModelo* carta);

	int getApuesta();
	void setApuesta(int apuesta);

	bool isActivo();
	void setActivo(bool activo);

	bool isAusente();
	void setAusente(bool ausente);

	bool isJugandoRonda();
	void setJugandoRonda(bool jugandoRonda);

	bool isDealer();
	void setDealer(bool esDealer);

	bool isVirtual();
	void setVirtual(bool esVirtual);

	bool isObservador();
	void setObservador(bool orbservador);

	bool isAllIn();
	void setAllIn(bool allIn);

	void jugar();
	void apostar(int fichas);
	void incrementarFichas(int cantidad);

	void tomarDecision(double confianza);
	bool subeApuesta(double confianzaEnJugada, int &fichas);

	void resetTimer();
	int getSegundosTurno();

};

#endif //_JUGADOR_MODELO_H_
