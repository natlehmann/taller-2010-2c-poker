#include "OpIgualarJugadorVirtual.h"

OpIgualarJugadorVirtual::OpIgualarJugadorVirtual(int idCliente): OpJugadorVirtual(idCliente)
{
}

OpIgualarJugadorVirtual::~OpIgualarJugadorVirtual()
{
}

void OpIgualarJugadorVirtual::ejecutarAccion()
{
	ContextoJuego::getInstancia()->igualarApuesta(this->getIdCliente());
}
