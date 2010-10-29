#include "OpUIClienteDejarMesa.h"

OpUIClienteDejarMesa::OpUIClienteDejarMesa(void)
{
}

OpUIClienteDejarMesa::~OpUIClienteDejarMesa(void)
{
}

bool OpUIClienteDejarMesa::ejecutarAccion(Ventana* ventana) {

	return this->enviarPedido("OpDejarMesa", ventana);
}
