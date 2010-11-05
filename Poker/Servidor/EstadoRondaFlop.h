#ifndef _ESTADO_RONDAFLOP_H_
#define _ESTADO_RONDAFLOP_H_

#include "EstadoJuego.h"
#include "EstadoRondaTurn.h"

class EstadoRondaFlop : public EstadoJuego
{
private:
	EstadoRondaTurn* rondaTurn;

public:
	EstadoRondaFlop(EstadoRondaTurn* rondaTurn);
	virtual ~EstadoRondaFlop(void);

	void setEstadoRondaTurn(EstadoRondaTurn* rondaTurn);

	virtual EstadoJuego* getSiguienteEstado();

	virtual string getEscenarioJuego(int idJugador);
	virtual string getEscenarioJuego(int idJugador, string mensaje);
};

#endif //_ESTADO_RONDAFLOP_H_

