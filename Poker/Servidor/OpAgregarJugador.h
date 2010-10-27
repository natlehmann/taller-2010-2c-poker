#ifndef _OP_AGREGARJUGADOR_H_
#define _OP_AGREGARJUGADOR_H_

#include "Operacion.h"

using namespace std;

class OpAgregarJugador : public Operacion
{
public:
	OpAgregarJugador(int idCliente, vector<string> parametros);
	virtual ~OpAgregarJugador(void);

	bool ejecutar(Socket* socket);
};

#endif //_OP_AGREGARJUGADOR_H_
