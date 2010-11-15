#include "OpUIClienteSolicitarEstadistica.h"
#include "DomTree.h"
#include "UICliente.h"
#include "Cliente.h"
#include "XmlParser.h"
#include "RecursosCliente.h"
#include "FabricaOperacionesCliente.h"
#include "MensajesUtil.h"
#include <iostream>
#include <string>
#include <fstream>
#include <time.h>

OpUIClienteSolicitarEstadistica::OpUIClienteSolicitarEstadistica(vector<string> parametros)
{
	this->parametros = parametros;
}

OpUIClienteSolicitarEstadistica::~OpUIClienteSolicitarEstadistica(void)
{
}

bool OpUIClienteSolicitarEstadistica::ejecutarAccion(Ventana* ventana)
{
	bool ok = false;
	
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

	DomTree* tree = new DomTree("operaciones");
	Elemento* pedido = tree->agregarElemento("pedido");

	Elemento* operacion = pedido->agregarHijo("operacion");
	operacion->agregarAtributo("id", "OpEnviarEstadistica");

	Elemento* params = operacion->agregarHijo("parametros");
	Elemento* param1 = params->agregarHijo("parametro");
	param1->agregarAtributo("nombre","tipoDeEstadistica");
	param1->setTexto(tipoDeEstadistica);

	Elemento* param2 = params->agregarHijo("parametro");
	param2->agregarAtributo("nombre","anio");
	param2->setTexto(anio);

	if(mes != "")
	{
		Elemento* param3 = params->agregarHijo("parametro");
		param3->agregarAtributo("nombre", "mes");
		param3->setTexto(mes);
	}

	if(dia != "")
	{
		Elemento* param4 = params->agregarHijo("parametro");
		param4->agregarAtributo("nombre", "dia");
		param4->setTexto(dia);
	}

	XmlParser* parser = new XmlParser();

	// Se envia el pedido al servidor
	Cliente* cliente = UICliente::getCliente();
	string msjRecibido;

	if (cliente->enviarRecibir(parser->toString(tree), msjRecibido)) 
	{
		try 
		{
			if (this->cargarRespuestaServidor(msjRecibido))
			{
				if (MensajesUtil::sonIguales(this->parametrosRecibidos.at(0), "OK"))
				{
					ok = true;		

					if (parametrosRecibidos.size() > 1)
					{
						this->estadistica = parametrosRecibidos.at(1);

						string pathOrigen = "";
						this->archivo = tipoDeEstadistica + fecha + ".txt";
						string pathCompleto = pathOrigen + this->archivo;
						ofstream* archivo = new ofstream(pathCompleto.c_str(), ios::out | ios::app);
						if (archivo->is_open())
							*(archivo) << this->estadistica << endl;

						archivo->close();
						delete(archivo);
					}

					//TODO: GRABAR ARCHIVO CON LA ESTADISTICA
				}
				else
				{
					if (parametrosRecibidos.size() > 0)
						this->error = parametrosRecibidos.at(0);
				}
			}
		} 
		catch (PokerException& e) 
		{
			RecursosCliente::getLog()->escribir(&(Respuesta)e.getError());
		}
	}
	else
	{
		RecursosCliente::getLog()->escribir("El servidor no devolvio respuesta al intentar loguear el usuario.");
	}

	delete(parser);
	delete(tree);

	return ok;
}

string OpUIClienteSolicitarEstadistica::getError()
{
	return this->error;
}

string OpUIClienteSolicitarEstadistica::getArchivo()
{
	return this->archivo;
}

string OpUIClienteSolicitarEstadistica::getFechaActual()
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

string OpUIClienteSolicitarEstadistica::getHoraActual()
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