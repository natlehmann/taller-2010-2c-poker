#ifndef _ESTADO_ESPERANDOJUGADORES_H_
#define _ESTADO_ESPERANDOJUGADORES_H_

#include "EstadoJuego.h"
#include "EstadoRondaCiega.h"

class EstadoEsperandoJugadores : public EstadoJuego
{
private:
	EstadoRondaCiega* estadoRondaCiega;

public:
	EstadoEsperandoJugadores(void);
	virtual ~EstadoEsperandoJugadores(void);

	void setEstadoRondaCiega(EstadoRondaCiega* rondaCiega);

	virtual EstadoJuego* getSiguienteEstado();

	virtual string getEscenarioJuego(int idJugador);
	virtual string getEscenarioJuego(int idJugador, string mensaje);
};

#endif //_ESTADO_ESPERANDOJUGADORES_H_
