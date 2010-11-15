#include "OpGetCantidadFichas.h"
#include "AccesoDatos.h"
#include "JugadorModelo.h"
#include "GeneradorRespuesta.h"
#include "Resultado.h"
#include "UtilTiposDatos.h"

OpGetCantidadFichas::OpGetCantidadFichas(int idCliente, vector<string> parametros): Operacion(idCliente)
{
	this->parametros = parametros;
}

OpGetCantidadFichas::~OpGetCantidadFichas(void)
{
}


bool OpGetCantidadFichas::ejecutarAccion(Socket* socket)
{
	bool error = false;
	bool ok = true;
	string respuesta = "";
	
	string usuario = this->parametros.at(0);
	
	AccesoDatos ad;
	JugadorModelo* jugador = ad.obtenerJugador(usuario);
	
	string msjRetorno = "";
	GeneradorRespuesta generador = GeneradorRespuesta();

	Resultado* resultado = new Resultado("", UtilTiposDatos::enteroAString(jugador->getFichas()), 
		"OpGetCantidadFichas");
	generador.agregarRespuesta(resultado);
	
	string resul = generador.obtenerRespuesta();

	if (socket != NULL && !MensajesUtil::esVacio(resul))
	{
		if(!socket->enviar(resul)) {
			error = true;
		}
	} else { 
		error = true;
	}
	
	return error;	
}

