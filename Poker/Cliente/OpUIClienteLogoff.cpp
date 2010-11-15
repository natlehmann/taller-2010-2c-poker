#include "OpUIClienteLogoff.h"
#include "DomTree.h"
#include "UICliente.h"
#include "Cliente.h"
#include "XmlParser.h"
#include "RecursosCliente.h"
#include "FabricaOperacionesCliente.h"
#include "MensajesUtil.h"

#define XML_TAG_ERRORES "errores"
#define XML_TAG_RESULTADOS "resultados"

OpUIClienteLogoff::OpUIClienteLogoff(vector<string> parametros): OperacionUICliente()
{
	this->parametros = parametros;
}

OpUIClienteLogoff::~OpUIClienteLogoff(void)
{
}

bool OpUIClienteLogoff::ejecutarAccion(Ventana* ventana)
{
	bool ok = false;

	string usuario = this->parametros.at(0);
	string idsesion = this->parametros.at(1);


	DomTree* tree = new DomTree("operaciones");
	Elemento* pedido = tree->agregarElemento("pedido");

	Elemento* operacion = pedido->agregarHijo("operacion");
	operacion->agregarAtributo("id", "OpLogoff");

	Elemento* params = operacion->agregarHijo("parametros");
	Elemento* param1 = params->agregarHijo("parametro");
	Elemento* param2 = params->agregarHijo("parametro");

	param1->agregarAtributo("nombre", "usuario");
	param1->setTexto(usuario);
	param2->agregarAtributo("nombre", "idsesion");
	param2->setTexto(idsesion);

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
				}
			}

			if (!ok){
				if (parametrosRecibidos.size() > 0){
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
		RecursosCliente::getLog()->escribir("El servidor no devolvio respuesta al intentar desconectar el usuario.");
	}

	delete(parser);
	delete(tree);

	return ok;
}

string OpUIClienteLogoff::getError()
{
	return this->error;
}

//int OpUIClienteLogoff::getSesionId()
//{
//	return this->sesionId;
//}
//
//int OpUIClienteLogoff::getCantFichas()
//{
//	return this->cantFichas;
//}