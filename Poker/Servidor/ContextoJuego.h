#ifndef _CONTEXTOJUEGO_H_
#define _CONTEXTOJUEGO_H_

#include <string>
#include "MesaModelo.h"
#include "BoteModelo.h"


using namespace std;

class ContextoJuego
{
private:
	static ContextoJuego instancia;

protected:
	ContextoJuego(void);
	MesaModelo* mesa;

public:	
	virtual ~ContextoJuego(void);

	static ContextoJuego* getInstancia();

	int getCantidadJugadoresActivos();
	void iniciarJuego();
	MesaModelo* getMesa();
	BoteModelo* getBote();

};

#endif //_CONTEXTOJUEGO_H_
