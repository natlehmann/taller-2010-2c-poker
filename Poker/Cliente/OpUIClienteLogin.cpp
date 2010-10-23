#include "OpUIClienteLogin.h"
#include "FabricaOperacionesCliente.h"

OpUIClienteLogin::OpUIClienteLogin(void)
{
}

OpUIClienteLogin::~OpUIClienteLogin(void)
{
}

bool OpUIClienteLogin::ejecutar(Ventana* ventana){

	// TODO: ACA HACER LOGIN !!!!

	FabricaOperacionesCliente fab;
	// TODO: REEMPLAZAR PARAMETRO POR EL NOMBRE DEL JUGADOR
	OperacionUICliente* operacion = fab.newOperacion("OpUIClienteAgregarJugador", "fulanito");
	bool resultado = operacion->ejecutar(ventana);
	delete(operacion);

	return resultado;
}
