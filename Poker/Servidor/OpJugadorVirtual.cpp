#include "OpJugadorVirtual.h"

OpJugadorVirtual::OpJugadorVirtual(int idCliente)
{
	this->idCliente = idCliente;
}

OpJugadorVirtual::~OpJugadorVirtual()
{
}

int OpJugadorVirtual::getIdCliente()
{
	return this->idCliente;
}
void OpJugadorVirtual::setIdCliente(int idCliente)
{
	this->idCliente = idCliente;
}