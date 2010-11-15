#include "OpUIClienteComprarFichas.h"
#include "DomTree.h"
#include "UICliente.h"
#include "Cliente.h"
#include "XmlParser.h"
#include "RecursosCliente.h"
#include "FabricaOperacionesCliente.h"
#include "MensajesUtil.h"

OpUIClienteComprarFichas::OpUIClienteComprarFichas(vector<string> parametros): OperacionUICliente()
{
	this->parametros = parametros;
}

OpUIClienteComprarFichas::~OpUIClienteComprarFichas(void)
{
}

bool OpUIClienteComprarFichas::ejecutarAccion(Ventana* ventana)
{
	bool ok = false;

	string usuario = this->parametros.at(0);
	string cantFichas = this->parametros.at(1);
	
	DomTree* tree = new DomTree("operaciones");
	Elemento* pedido = tree->agregarElemento("pedido");

	Elemento* operacion = pedido->agregarHijo("operacion");
	operacion->agregarAtributo("id", "OpComprarFichas");

	Elemento* params = operacion->agregarHijo("parametros");
	Elemento* param1 = params->agregarHijo("parametro");
	Elemento* param2 = params->agregarHijo("parametro");
	
	param1->agregarAtributo("nombre", "usuario");
	param1->setTexto(usuario);
	param2->agregarAtributo("nombre", "cantfichas");
	param2->setTexto(cantFichas);
	
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
		RecursosCliente::getLog()->escribir("El servidor no devolvio respuesta al intentar comprar fichas.");
	}

	delete(parser);
	delete(tree);

	return ok;

}

string OpUIClienteComprarFichas::getError()
{
	return this->error;
}

