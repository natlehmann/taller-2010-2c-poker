#ifndef _ESTADO_RONDACIEGA_H_
#define _ESTADO_RONDACIEGA_H_

#include "EstadoJuego.h"

class EstadoRondaCiega : public EstadoJuego
{
public:
	EstadoRondaCiega(void);
	virtual ~EstadoRondaCiega(void);

	virtual EstadoJuego* getSiguienteEstado();

	virtual string getEscenarioJuego(int idJugador);
};

#endif //_ESTADO_RONDACIEGA_H_

