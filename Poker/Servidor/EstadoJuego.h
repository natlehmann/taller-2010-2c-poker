#ifndef _ESTADOJUEGO_H_
#define _ESTADOJUEGO_H_

#include <string>
#include "Elemento.h"


using namespace std;

class EstadoJuego
{
protected:
	EstadoJuego(void);

	Elemento* crearElementoEscenario();
	void agregarMesa(Elemento* elementoEscenario);

public:
	virtual ~EstadoJuego(void);

	virtual EstadoJuego* getSiguienteEstado() = 0;

	virtual string getEscenarioJuego(int idJugador) = 0;
};

#endif //_ESTADOJUEGO_H_
