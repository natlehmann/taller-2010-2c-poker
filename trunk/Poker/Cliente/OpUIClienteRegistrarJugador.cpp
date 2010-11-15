#include "OpUIClienteRegistrarJugador.h"
#include "DomTree.h"
#include "UICliente.h"
#include "Cliente.h"
#include "XmlParser.h"
#include "RecursosCliente.h"
#include "FabricaOperacionesCliente.h"
#include "MensajesUtil.h"

OpUIClienteRegistrarJugador::OpUIClienteRegistrarJugador(vector<string> parametros): OperacionUICliente()
{
	this->parametros = parametros;
}

OpUIClienteRegistrarJugador::~OpUIClienteRegistrarJugador(void)
{
}

bool OpUIClienteRegistrarJugador::ejecutarAccion(Ventana* ventana)
{
	bool ok = false;

	string usuario = this->parametros.at(0);
	string password = this->parametros.at(1);
	string nombre = this->parametros.at(2);
	string apellido = this->parametros.at(3);

	DomTree* tree = new DomTree("operaciones");
	Elemento* pedido = tree->agregarElemento("pedido");

	Elemento* operacion = pedido->agregarHijo("operacion");
	operacion->agregarAtributo("id", "OpRegistrarJugador");

	Elemento* params = operacion->agregarHijo("parametros");
	Elemento* param1 = params->agregarHijo("parametro");
	Elemento* param2 = params->agregarHijo("parametro");
	Elemento* param3 = params->agregarHijo("parametro");
	Elemento* param4 = params->agregarHijo("parametro");

	param1->agregarAtributo("nombre", "usuario");
	param1->setTexto(usuario);
	param2->agregarAtributo("nombre", "password");
	param2->setTexto(password);
	param3->agregarAtributo("nombre", "nombre");
	param3->setTexto(nombre);
	param4->agregarAtributo("nombre", "apellido");
	param4->setTexto(apellido);

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
		RecursosCliente::getLog()->escribir("El servidor no devolvio respuesta al intentar loguear el usuario.");
	}

	delete(parser);
	delete(tree);

	return ok;

}

string OpUIClienteRegistrarJugador::getError()
{
	return this->error;
}