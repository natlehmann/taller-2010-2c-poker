#ifndef _ESTADO_RONDARIVER_H_
#define _ESTADO_RONDARIVER_H_

#include "EstadoJuego.h"
#include "EstadoEvaluandoGanador.h"

class EstadoRondaRiver : public EstadoJuego
{
private:
	EstadoEvaluandoGanador* evaluandoGanador;

public:
	EstadoRondaRiver(EstadoEvaluandoGanador* evaluandoGanador);
	virtual ~EstadoRondaRiver(void);

	void setEstadoEvaluandoGanador(EstadoEvaluandoGanador* evaluandoGanador);

	virtual EstadoJuego* getSiguienteEstado();

	virtual string getEscenarioJuego(int idJugador);
};

#endif //_ESTADO_RONDARIVER_H_

