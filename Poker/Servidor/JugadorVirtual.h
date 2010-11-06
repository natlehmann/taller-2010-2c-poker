#ifndef _JUGADOR_VIRTUAL_H_
#define _JUGADOR_VIRTUAL_H_

#include <string>
#include "JugadorModelo.h"
#include "OpJugadorVirtual.h"
#include "OpIgualarJugadorVirtual.h"
#include "OpNoIrJugadorVirtual.h"

#define CONFIANZA 0.7
#define APUESTA_PATRON 20

using namespace std;

class JugadorVirtual : public JugadorModelo
{
private:
	double nivelDeConfianza;
	int apuestaPatron;
public:
	JugadorVirtual(int id, int posicion);
	JugadorVirtual(int id, string nombre, int fichas, int posicion, string nombreImagen);
	~JugadorVirtual(void);
	OpJugadorVirtual* Jugar();
};


#endif //_JUGADOR_VIRTUAL_H_