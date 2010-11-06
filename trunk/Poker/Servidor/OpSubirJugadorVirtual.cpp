#include "OpSubirJugadorVirtual.h"
#include "ContextoJuego.h"
#include "UtilTiposDatos.h"

OpSubirJugadorVirtual::OpSubirJugadorVirtual(int idCliente): OpJugadorVirtual(idCliente)
{
}

OpSubirJugadorVirtual::~OpSubirJugadorVirtual(void)
{
}

bool OpSubirJugadorVirtual::ejecutarAccion(Socket* socket){
	
	string fichasTxt = this->parametros.at(0);
	int fichas = UtilTiposDatos::getEntero(fichasTxt);
	ContextoJuego::getInstancia()->subirApuesta(this->getIdCliente(), fichas);
	return true;
}
