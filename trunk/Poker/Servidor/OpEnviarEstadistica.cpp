#include "OpEnviarEstadistica.h"
#include "Resultado.h"
#include "FabricaOperacionesServidor.h"
#include "MensajesUtil.h"
#include "AccesoDatos.h"
#include "GeneradorRespuesta.h"
#include "Respuesta.h"


using namespace std;


OpEnviarEstadistica::OpEnviarEstadistica(int idCliente, vector<string> parametros):Operacion(idCliente)
{
	this->parametros = parametros;
}

OpEnviarEstadistica::~OpEnviarEstadistica(void)
{
}

bool OpEnviarEstadistica::ejecutarAccion(Socket* socket)
{	

	string anio = "";
	string mes = "";
	string dia = "";
	
	string tipoDeEstadistica = this->parametros.at(0); //
	anio = this->parametros.at(1); //formato AAAA
	if (parametros.size() > 2)
	{
		mes = this->parametros.at(2); //formato MM
		
		if (parametros.size() > 3) 
			dia = this->parametros.at(3); //formato DD
	}
	
	AccesoDatos ad;
	bool error;
	bool ok = true;
	string respuesta = "";
	string estadistica = "";
	

	if (MensajesUtil::sonIguales(tipoDeEstadistica, "ConsultaEvolucionUsuarios"))
	{
		estadistica = ad.obtenerEvolucionUsuariosRegistrados(dia, mes, anio);
		if (estadistica.length() > 0)
			respuesta = "OK";
		else
			respuesta = "Error al realizar la estadistica";
	}
	else if (MensajesUtil::sonIguales(tipoDeEstadistica, "ConsultaEvolucionUsuariosConectados"))
	{
		estadistica = ad.obtenerEvolucionUsuariosConectados(dia, mes, anio);
		if (estadistica.length() > 0)
			respuesta = "OK";
		else
			respuesta = "Error al realizar la estadistica";
	}
	else if (MensajesUtil::sonIguales(tipoDeEstadistica, "ConsultaListadoUsuariosConectados"))
	{
		estadistica = ad.obtenerListadoUsuariosConectados(dia, mes, anio);
		if (estadistica.length() > 0)
			respuesta = "OK";
		else
			respuesta = "Error al realizar la estadistica";
	}
	else if (MensajesUtil::sonIguales(tipoDeEstadistica, "ConsultaListadoUsuariosRegistrados"))
	{
		estadistica = ad.obtenerListadoUsuariosRegistrados(dia, mes, anio);
		if (estadistica.length() > 0)
			respuesta = "OK";
		else
			respuesta = "Error al realizar la estadistica";
	}
	else if (MensajesUtil::sonIguales(tipoDeEstadistica, "ConsultaRanking"))
	{
		estadistica = ad.obtenerRankingUsuarios();
		if (estadistica.length() > 0)
			respuesta = "OK";
		else
			respuesta = "Error al realizar la estadistica";
	}
	else
	{
		ok = false;
		respuesta = "Estadistica desconocida.";
	}


	GeneradorRespuesta generador = GeneradorRespuesta();

	if (ok)
	{
		Resultado* resultado = new Resultado("", respuesta, "OpEnviarEstadistica");
		generador.agregarRespuesta(resultado);

		
		if (estadistica.length() > 0) 
		{
			// Se envia la estadistica
			resultado = new Resultado("", estadistica, "OpLogin");
			generador.agregarRespuesta(resultado);
		}
	}
	else
	{
		Error* error1 = new Error("", respuesta, "OpEnviarEstadistica");
		generador.agregarRespuesta(error1);
	}
	
	string resul = generador.obtenerRespuesta();
	

	if (socket != NULL && !MensajesUtil::esVacio(resul))
	{
		if(!socket->enviar(resul)) 
			error = true;
	}
	else 
		error = true;

	return error;
}
