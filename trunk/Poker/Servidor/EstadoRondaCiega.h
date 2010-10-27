#ifndef _ESTADO_RONDACIEGA_H_
#define _ESTADO_RONDACIEGA_H_

#include "EstadoJuego.h"
#include "EstadoRondaFlop.h"

class EstadoRondaCiega : public EstadoJuego
{
private:
	EstadoRondaFlop* rondaFlop;

public:
	EstadoRondaCiega(EstadoRondaFlop* rondaFlop);
	virtual ~EstadoRondaCiega(void);

	void setEstadoRondaFlop(EstadoRondaFlop* rondaFlop);

	virtual EstadoJuego* getSiguienteEstado();

	virtual string getEscenarioJuego(int idJugador);
};

#endif //_ESTADO_RONDACIEGA_H_

