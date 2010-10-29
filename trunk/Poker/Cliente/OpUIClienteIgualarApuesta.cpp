#include "OpUIClienteIgualarApuesta.h"
#include "MensajesUtil.h"
#include "PokerException.h"
#include "RecursosCliente.h"
#include "XmlParser.h"
#include "Cliente.h"
#include "UICliente.h"

OpUIClienteIgualarApuesta::OpUIClienteIgualarApuesta(void)
{
}

OpUIClienteIgualarApuesta::~OpUIClienteIgualarApuesta(void)
{
}

bool OpUIClienteIgualarApuesta::ejecutarAccion(Ventana* ventana) {

	return this->enviarPedido("OpIgualarApuesta", ventana);
}
