#include "OpEnviarEstadistica.h"
#include "Resultado.h"
#include "FabricaOperacionesServidor.h"
#include "MensajesUtil.h"
#include "AccesoDatos.h"
#include "GeneradorRespuesta.h"
#include "Respuesta.h"
#include <iostream>
#include <string>
#include <fstream>
#include <time.h>
#include "RecursosServidor.h"

using namespace std;


OpEnviarEstadistica::OpEnviarEstadistica(int idCliente, vector<string> parametros):Operacion(idCliente)
{
	this->parametros = parametros;
}

OpEnviarEstadistica::~OpEnviarEstadistica(void)
{
	this->archivo->close();
	delete(this->archivo);
}

bool OpEnviarEstadistica::ejecutarAccion(Socket* socket)
{	
	cout << "Enviando estadistica a cliente " << this->getIdCliente() << endl;
	string anio = "";
	string mes = "";
	string dia = "";
	
	string fecha = "";

	string tipoDeEstadistica = this->parametros.at(0); //
	anio = this->parametros.at(1); //formato AAAA
	if (parametros.size() > 2)
	{
		mes = this->parametros.at(2); //formato MM
		if (parametros.size() > 3)
		{
			dia = this->parametros.at(3); //formato DD
			fecha = dia + "-";
		}
		fecha += mes + "-";
	}
	fecha += anio;
	bool error = false;
	AccesoDatos ad;
	bool ok = true;
	//los guarda en la misma carpeta que la de las imagenes porque la operacion enviar foto toma de ese
	// directorio
	string pathOrigen = RecursosServidor::getConfig()->get("servidor.pathImagenes");
	string respuesta; //path Archivo
	string nombreArchivo;


	if (MensajesUtil::sonIguales(tipoDeEstadistica, "ConsultaEvolucionUsuarios"))
	{
		//string contenidoEstadistica = ad.obtenerEvolucionUsuariosConectados(dia,mes,anio);
		string contenidoEstadistica = "obtenerEvolucionUsuariosConectados";
		respuesta = "Evolucion_Usuarios_Conectados-" + fecha + ".txt";
		nombreArchivo = pathOrigen + respuesta;
		this->archivo = new ofstream(nombreArchivo.c_str(), ios::out | ios::app);
		*(archivo) << contenidoEstadistica << endl;
		ok = true;
	}
	if (MensajesUtil::sonIguales(tipoDeEstadistica, "ConsultaEvolucionUsuariosConectados"))
	{	
		//string contenidoEstadistica = ad.obtenerEvolucionUsuariosConectados(dia,mes,anio);
		string contenidoEstadistica = "obtenerEvolucionUsuariosConectados";
		respuesta = "Evolucion_Usuarios_Conectados-" + fecha + ".txt";
		nombreArchivo = pathOrigen + respuesta;
		this->archivo  = new ofstream(nombreArchivo.c_str(), ios::out | ios::app);
		*(archivo) << contenidoEstadistica << endl;
		ok = true;
	}
	if (MensajesUtil::sonIguales(tipoDeEstadistica, "ConsultaListadoUsuariosConectados"))
	{
		//string contenidoEstadistica = ad.obtenerListadoUsuariosConectados(dia,mes,anio);
		string contenidoEstadistica = "obtenerListadoUsuariosConectados";
		respuesta = "Listado_Usuarios_Conectados-" + fecha + ".txt";
		nombreArchivo = pathOrigen + respuesta;
		this->archivo  = new ofstream(nombreArchivo.c_str(), ios::out | ios::app);
		*(archivo) << contenidoEstadistica << endl;
		ok = true;
	}
	if (MensajesUtil::sonIguales(tipoDeEstadistica, "ConsultaListadoUsuariosRegistrados"))
	{
		//string contenidoEstadistica = ad.obtenerListadoUsuariosRegistrados(dia,mes,anio);
		string contenidoEstadistica = "obtenerListadoUsuariosRegistrados";
		respuesta = "Listado_Usuarios_Registrados-" + fecha + ".txt";
		nombreArchivo = pathOrigen + respuesta;
		this->archivo  = new ofstream(nombreArchivo.c_str(), ios::out | ios::app);
		*(archivo) << contenidoEstadistica << endl;
		ok = true;
	}
	if (MensajesUtil::sonIguales(tipoDeEstadistica, "ConsultaRanking"))
	{
		string contenidoEstadistica = ad.obtenerRankingUsuarios();
		fecha = getFechaActual()+ "-" + getHoraActual();
		respuesta = "Ranking-" + fecha + ".txt";
		nombreArchivo = pathOrigen + respuesta;
		this->archivo = new ofstream(nombreArchivo.c_str(), ios::out | ios::app);
		*(archivo) << contenidoEstadistica << endl;
		ok = true;
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


string OpEnviarEstadistica::getFechaActual()
{
	time_t tSac = time(NULL);  // instante actual
		
	struct tm* pt1 = localtime(&tSac);
	string dia = UtilTiposDatos::enteroAString(pt1->tm_mday);
	string mes = UtilTiposDatos::enteroAString(pt1->tm_mon+1);
	string anio = UtilTiposDatos::enteroAString(pt1->tm_year+1900);

	if (dia.length() == 1)
		dia = "0" + dia;

	if (mes.length() == 1)
		mes = "0" + mes;

	string fecha = dia + "-" + mes + "-" + anio;
	
	return fecha;	
}

string OpEnviarEstadistica::getHoraActual()
{
	time_t tSac = time(NULL);  // instante actual
		
	struct tm* pt1 = localtime(&tSac);
	string horas = UtilTiposDatos::enteroAString(pt1->tm_hour);
	string minutos = UtilTiposDatos::enteroAString(pt1->tm_min);
	string segundos = UtilTiposDatos::enteroAString(pt1->tm_sec);

	if (horas.length() == 1)
		horas = "0" + horas;

	if (minutos.length() == 1)
		minutos = "0" + minutos;

	if (segundos.length() == 1)
		segundos = "0" + segundos;

	string horaActual = horas + "-" + minutos + "-" + segundos;
	
	return horaActual;	
}