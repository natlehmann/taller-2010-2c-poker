#ifndef _ESTADOJUEGO_H_
#define _ESTADOJUEGO_H_

#include <string>


using namespace std;

class EstadoJuego
{
protected:
	EstadoJuego(void);

public:
	virtual ~EstadoJuego(void);

	virtual EstadoJuego* getSiguienteEstado() = 0;

	virtual string getEscenarioJuego(int idJugador) = 0;
};

#endif //_ESTADOJUEGO_H_
