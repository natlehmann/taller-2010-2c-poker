#ifndef _ESTADO_ESPERANDOJUGADORES_H_
#define _ESTADO_ESPERANDOJUGADORES_H_

#include "EstadoJuego.h"

class EstadoEsperandoJugadores : public EstadoJuego
{
public:
	EstadoEsperandoJugadores(void);
	virtual ~EstadoEsperandoJugadores(void);

	virtual EstadoJuego* getSiguienteEstado();

	virtual string getEscenarioJuego(int idJugador);
};

#endif //_ESTADO_ESPERANDOJUGADORES_H_
