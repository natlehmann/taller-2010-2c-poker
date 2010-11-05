#ifndef _ESTADOJUEGO_H_
#define _ESTADOJUEGO_H_

#include <string>
#include "Elemento.h"
#include "DomTree.h"

using namespace std;

class EstadoJuego
{
protected:
	EstadoJuego(void);

	DomTree* crearArbolEscenario();
	void agregarMesa(DomTree* arbol);
	void agregarBote(DomTree* arbol);
	void agregarMensaje(DomTree* arbol, string mensaje);
	void agregarJugadores(DomTree* arbol, int idJugador);
	void agregarCartasComunitarias(DomTree* arbol);
	void agregarPanelBotones(DomTree* arbol, int idJugador);
	void borrarMensaje(DomTree* arbol);

	string arbolToString(DomTree* arbol);
	string getEscenarioEstandar(int idJugador);
	string getEscenarioConMensaje(int idJugador, string mensaje);

public:
	virtual ~EstadoJuego(void);

	virtual EstadoJuego* getSiguienteEstado() = 0;

	virtual string getEscenarioJuego(int idJugador) = 0;
	virtual string getEscenarioJuego(int idJugador, string mensaje) = 0;
};

#endif //_ESTADOJUEGO_H_
