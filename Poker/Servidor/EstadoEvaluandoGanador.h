#ifndef _ESTADO_EVALUANDOGANADOR_H_
#define _ESTADO_EVALUANDOGANADOR_H_

#include "EstadoJuego.h"

class EstadoEsperandoJugadores;
class EstadoRondaCiega;

class EstadoEvaluandoGanador : public EstadoJuego
{
private:
	EstadoEsperandoJugadores* esperandoJugadores;
	EstadoRondaCiega* rondaCiega;

public:
	EstadoEvaluandoGanador(void);
	virtual ~EstadoEvaluandoGanador(void);

	void setEstadoEsperandoJugadores(EstadoEsperandoJugadores* esperandoJugadores);
	void setEstadoRondaCiega(EstadoRondaCiega* rondaCiega);

	virtual EstadoJuego* getSiguienteEstado();

	virtual string getEscenarioJuego(int idJugador);
	virtual string getEscenarioJuego(int idJugador, string mensaje);
};

#endif //_ESTADO_EVALUANDOGANADOR_H_

