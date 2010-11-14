#include "OpLogoff.h"
#include "Resultado.h"
#include "FabricaOperacionesServidor.h"
#include "MensajesUtil.h"
#include "AccesoDatos.h"
#include "GeneradorRespuesta.h"
#include "Respuesta.h"
#include "UtilTiposDatos.h"

OpLogoff::OpLogoff(int idCliente, vector<string> parametros): Operacion(idCliente)
{
	this->parametros = parametros;
}

OpLogoff::~OpLogoff(void)
{
}

bool OpLogoff::ejecutarAccion(Socket* socket)
{
	bool error = false;
	bool ok = true;
	string respuesta = "";

	string usuario = this->parametros.at(0);
	string idsesion = this->parametros.at(1);
	
	AccesoDatos ad;
	if (ad.grabarFinSesion(UtilTiposDatos::stringAEntero(idsesion)))
	{
		respuesta = "OK";
	}
	else
	{
		respuesta = "Se ha producido un error al intentar finalizar sesion: " + ad.getMensajeError();
		ok = false;
	}

	/******************************************************************/
	string msjRetorno = "";
	GeneradorRespuesta generador = GeneradorRespuesta();

	if (ok)
	{
		// Se envia el "OK"
		Resultado* resultado = new Resultado("", respuesta, "OpLogin");
		generador.agregarRespuesta(resultado);
	}
	else
	{
		Error* error1 = new Error("", respuesta, "OpLogin");
		generador.agregarRespuesta(error1);
	}
	
	string resul = generador.obtenerRespuesta();
	/******************************************************************/

	if (socket != NULL && !MensajesUtil::esVacio(resul))
	{
		if(!socket->enviar(resul)) 
			error = true;
	}
	else 
		error = true;

	return error;	
}
