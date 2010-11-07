#include "OpUIClientePasar.h"

OpUIClientePasar::OpUIClientePasar(void)
{
}

OpUIClientePasar::~OpUIClientePasar(void)
{
}

bool OpUIClientePasar::ejecutarAccion(Ventana* ventana) {

	return this->enviarPedido("OpPasar", ventana);
}
