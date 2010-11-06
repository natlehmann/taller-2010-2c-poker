#ifndef OPERACION_JUGADORVIRTUAL_H_
#define OPERACION_JUGADORVIRTUAL_H_

#include "Operacion.h"
#include <string>


using namespace std;

class OpJugadorVirtual : public Operacion
{
public:
	OpJugadorVirtual(int idCliente);
	~OpJugadorVirtual();

	/* Metodo NO sincronizado */
    virtual bool ejecutar(Socket* socket);

	virtual bool ejecutarAccion(Socket* socket) = 0;

};

#endif //OPERACION_JUGADORVIRTUAL_H_

