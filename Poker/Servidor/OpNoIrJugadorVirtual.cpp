#include "OpNoIrJugadorVirtual.h"
#include "ContextoJuego.h"

OpNoIrJugadorVirtual::OpNoIrJugadorVirtual(int idCliente):OpJugadorVirtual(idCliente)
{
}

OpNoIrJugadorVirtual::~OpNoIrJugadorVirtual()
{
}

bool OpNoIrJugadorVirtual::ejecutarAccion(Socket* socket){
	ContextoJuego::getInstancia()->noIr(this->getIdCliente());
	return true;
}