#include "OpIgualarJugadorVirtual.h"
#include "ContextoJuego.h"

OpIgualarJugadorVirtual::OpIgualarJugadorVirtual(int idCliente): OpJugadorVirtual(idCliente)
{
}

OpIgualarJugadorVirtual::~OpIgualarJugadorVirtual()
{
}

bool OpIgualarJugadorVirtual::ejecutarAccion(Socket* socket){
	ContextoJuego::getInstancia()->igualarApuesta(this->getIdCliente());
	return true;
}
