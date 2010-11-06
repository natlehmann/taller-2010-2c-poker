#include "OpJugadorVirtual.h"

OpJugadorVirtual::OpJugadorVirtual(int idCliente) : Operacion(idCliente)
{
}

OpJugadorVirtual::~OpJugadorVirtual()
{
}

bool OpJugadorVirtual::ejecutar(Socket* socket){

	return this->ejecutarAccion(socket);
}