#include "OpUIClienteSolicitarEstadistica.h"
#include "DomTree.h"
#include "UICliente.h"
#include "Cliente.h"
#include "XmlParser.h"
#include "RecursosCliente.h"
#include "FabricaOperacionesCliente.h"
#include "MensajesUtil.h"

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

	string tipoDeEstadistica = this->parametros.at(0); //
	anio = this->parametros.at(1); //formato AAAA
	if (parametros.size() > 2)
	{
		mes = this->parametros.at(2); //formato MM
		if (parametros.size() > 3) dia = this->parametros.at(3); //formato DD
	}

	DomTree* tree = new DomTree("operaciones");
	Elemento* pedido = tree->agregarElemento("pedido");

	Elemento* operacion = pedido->agregarHijo("operacion");
	operacion->agregarAtributo("id", "OpEstadistica");

	Elemento* params = operacion->agregarHijo("parametros");

	Elemento* param1 = params->agregarHijo("parametro");
	param1->agregarAtributo("nombre","tipoDeEstadistica");
	param1->setTexto(tipoDeEstadistica);

	if(anio != "")
	{
		Elemento* param1 = params->agregarHijo("parametro");
		param1->agregarAtributo("nombre","anio");
		param1->setTexto(anio);
	}
	if(mes != "")
	{
		Elemento* param2 = params->agregarHijo("parametro");
		param2->agregarAtributo("nombre", "mes");
		param2->setTexto(mes);
	}
	if(dia != "")
	{
		Elemento* param3 = params->agregarHijo("parametro");
		param3->agregarAtributo("nombre", "dia");
		param3->setTexto(dia);
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
				if (this->parametrosRecibidos.at(0) != "")
				{
					this->pathArchivo = parametrosRecibidos.at(0);
					ok = true;		
				}
				else
				{

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

string OpUIClienteSolicitarEstadistica::getPathArchivo()
{
	return this->pathArchivo;
}

void OpUIClienteSolicitarEstadistica::setPathArchivo(string path)
{
	this->pathArchivo = path;
}