#include "OpUIClienteLogin.h"
#include "DomTree.h"
#include "UICliente.h"
#include "Cliente.h"
#include "XmlParser.h"
#include "RecursosCliente.h"
#include "FabricaOperacionesCliente.h"
#include "MensajesUtil.h"

#define XML_TAG_ERRORES "errores"
#define XML_TAG_RESULTADOS "resultados"

OpUIClienteLogin::OpUIClienteLogin(vector<string> parametros): OperacionUICliente()
{
	this->parametros = parametros;
}

OpUIClienteLogin::~OpUIClienteLogin(void)
{
}

bool OpUIClienteLogin::ejecutarAccion(Ventana* ventana)
{
	bool ok = false;

	//// TODO: BORRRAR ESTO
	//string usuario = "pepe";
	//string password = "pass";
	//string esVirtual = "false";
	//string esObservador = "false";
	
	string usuario = this->parametros.at(0);
	string password = this->parametros.at(1);
	string esVirtual = this->parametros.at(2);
	string esObservador = this->parametros.at(3);

	DomTree* tree = new DomTree("operaciones");
	Elemento* pedido = tree->agregarElemento("pedido");

	Elemento* operacion = pedido->agregarHijo("operacion");
	operacion->agregarAtributo("id", "OpLogin");

	Elemento* params = operacion->agregarHijo("parametros");
	Elemento* param1 = params->agregarHijo("parametro");
	Elemento* param2 = params->agregarHijo("parametro");
	Elemento* param3 = params->agregarHijo("parametro");
	Elemento* param4 = params->agregarHijo("parametro");

	param1->agregarAtributo("nombre", "usuario");
	param1->setTexto(usuario);
	param2->agregarAtributo("nombre", "password");
	param2->setTexto(password);
	param3->agregarAtributo("nombre", "virtual");
	param3->setTexto(esVirtual);
	param4->agregarAtributo("nombre", "observador");
	param4->setTexto(esObservador);

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
				else
				{
					// parametrosRecibidos.at(0) TIENE LA DESCRIPCION DEL ERROR AL VALIDAR EL LOGUEO
					// * USUARIO INEXISTENTE
					// * PASSWORD INCORRECTA
					// * ERROR GENERAL
					// PASAR EL MSJ DE ERROR EN EL LOGUEO A LA PANTALLA DEL LOGIN
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

string OpUIClienteLogin::getError()
{
	string error = "";
	if (parametrosRecibidos.size() > 0)
		error = parametrosRecibidos.at(0);
	return error;
}