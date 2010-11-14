#include "OpEnviarEstadistica.h"
#include "Resultado.h"
#include "FabricaOperacionesServidor.h"
#include "MensajesUtil.h"
#include "AccesoDatos.h"
#include "GeneradorRespuesta.h"
#include "Respuesta.h"

OpEnviarEstadistica::OpEnviarEstadistica(int idCliente, vector<string> parametros):Operacion(idCliente)
{
	this->parametros = parametros;
}

OpEnviarEstadistica::~OpEnviarEstadistica(void)
{
}

bool OpEnviarEstadistica::ejecutarAccion(Socket* socket)
{	
	//cout << "Enviando estadistica a cliente " << this->getIdCliente() << endl;
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
	

	if (MensajesUtil::sonIguales(tipoDeEstadistica, "ConsultaEvolucionUsuarios"))
	{
		
		//aca se consulta a AccesoDatos y se guarda en un archivo con nombre relacionado cno la consulta
		// ejemplo estadistica_ConsultaEvolucionUsuarios_10_11_2010.txt
	}
	if (MensajesUtil::sonIguales(tipoDeEstadistica, "ConsultaEvolucionUsuariosConectados"))
	{

	}
	if (MensajesUtil::sonIguales(tipoDeEstadistica, "ConsultaListadoUsuariosConectados"))
	{

	}
	if (MensajesUtil::sonIguales(tipoDeEstadistica, "ConsultaListadoUsuariosRegistrados"))
	{

	}
	if (MensajesUtil::sonIguales(tipoDeEstadistica, "ConsultaRanking"))
	{

	}

	GeneradorRespuesta generador = GeneradorRespuesta();

	if (ok)
	{
		Resultado* resultado = new Resultado("", respuesta, "OpEnviarEstadistica");
		generador.agregarRespuesta(resultado);
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


	return true;
}