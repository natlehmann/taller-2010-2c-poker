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

	string tipoDeEstadistica = this->parametros.at(0); 
	anio = this->parametros.at(1); //formato AAAA
	if (parametros.size() > 2)
	{
		mes = this->parametros.at(2); //formato MM
		
		if (parametros.size() > 3) 
			dia = this->parametros.at(3); //formato DD
	}

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
						this->estadistica = UtilTiposDatos::getEntero(parametrosRecibidos.at(1));

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