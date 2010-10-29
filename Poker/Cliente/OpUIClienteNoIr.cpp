#include "OpUIClienteNoIr.h"

OpUIClienteNoIr::OpUIClienteNoIr(void)
{
}

OpUIClienteNoIr::~OpUIClienteNoIr(void)
{
}

bool OpUIClienteNoIr::ejecutarAccion(Ventana* ventana) {

	return this->enviarPedido("OpNoIr", ventana);
}
