#ifndef _ESTADO_RONDATURN_H_
#define _ESTADO_RONDATURN_H_

#include "EstadoJuego.h"
#include "EstadoRondaRiver.h"

class EstadoRondaTurn : public EstadoJuego
{
private:
	EstadoRondaRiver* rondaRiver;

public:
	EstadoRondaTurn(EstadoRondaRiver* rondaRiver);
	virtual ~EstadoRondaTurn(void);

	void setEstadoRondaRiver(EstadoRondaRiver* rondaRiver);

	virtual EstadoJuego* getSiguienteEstado();

	virtual string getEscenarioJuego(int idJugador);
};

#endif //_ESTADO_RONDATURN_H_

