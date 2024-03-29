#include "OperacionUICliente.h"
#include "PokerException.h"
#include "RecursosCliente.h"
#include "XmlParser.h"
#include "Cliente.h"
#include "UICliente.h"
#include "FabricaDeElementosGraficos.h"
#include "VentanaAuxiliar.h"
#include "Sincronizador.h"

#define XML_TAG_ERRORES "errores"
#define XML_TAG_RESULTADOS "resultados"
#define RESPUESTA_OK "OK"

OperacionUICliente::OperacionUICliente(void)
{
}

OperacionUICliente::~OperacionUICliente(void)
{
}

bool OperacionUICliente::ejecutar(Ventana* ventana){

	bool resultado = false;
	
	Ventana* aux = Sincronizador::getInstancia()->getVentanaAuxiliar();

	try {
		resultado = this->ejecutarAccion(aux);

	} catch(PokerException& e){
		RecursosCliente::getLog()->escribir(&(e.getError()));

	} catch(exception& e){
		RecursosCliente::getLog()->escribir("Se produjo un error ejecutando la operacion. " + string(e.what()));

	} catch(...){
		RecursosCliente::getLog()->escribir("Se produjo un error ejecutando la operacion.");
	}


	Sincronizador::getInstancia()->notificarCambio();

	return resultado;
}

Elemento* OperacionUICliente::agregarOperacion(DomTree* arbol, string nombreOperacion) {

	Elemento* pedido = arbol->agregarElemento("pedido");

	Elemento* operacion = pedido->agregarHijo("operacion");
	operacion->agregarAtributo("id", nombreOperacion);

	return operacion;
}


bool OperacionUICliente::enviarPedido(string nombreOperacion) {
	
	DomTree* tree = new DomTree("operaciones");
	this->agregarOperacion(tree, nombreOperacion);

	bool ok = false;
	XmlParser* parser = new XmlParser();
	
	// se envia el pedido al servidor
	Cliente* cliente = UICliente::getCliente();
	string msjRecibido;

	if (cliente->enviarRecibir(parser->toString(tree), msjRecibido)) 
	{
		if (MensajesUtil::sonIguales(msjRecibido.data(), "OK"))
		{
			ok = true;		
		}
	}
	else
	{
		RecursosCliente::getLog()->escribir("El servidor no respondio a la operacion " + nombreOperacion + ".");
	}

	delete(parser);
	delete(tree);

	return ok;
}

bool OperacionUICliente::enviarPedido(string nombreOperacion, Ventana* ventana) {
	
	DomTree* tree = new DomTree("operaciones");
	this->agregarOperacion(tree, nombreOperacion);

	bool resultado = this->enviarMensaje(tree, ventana);

	delete(tree);

	return resultado;
}

bool OperacionUICliente::enviarMensaje(DomTree* tree, Ventana* ventana) {

	bool ok = true;
	XmlParser* parser = new XmlParser();
	
	// se envia el pedido al servidor
	Cliente* cliente = UICliente::getCliente();
	string msjRecibido;

	if (cliente->enviarRecibir(parser->toString(tree), msjRecibido)) 
	{
		try {
			DomTree* arbolEscenario = parser->toDom(msjRecibido, "escenario");
			FabricaDeElementosGraficos::generarEscenario(arbolEscenario, ventana);
			delete (arbolEscenario);

		} catch (PokerException& e) {
			RecursosCliente::getLog()->escribir(&(Respuesta)e.getError());
			ok = false;
		}
	}
	else
	{
		RecursosCliente::getLog()->escribir("El servidor no devolvio ningun escenario.");
		ok = false;
	}

	delete(parser);
	return ok;
}

bool OperacionUICliente::cargarRespuestaServidor(string respuesta)
{
	bool ok = true;

	try 
	{
		XmlParser* xmlParser = new XmlParser();
		DomTree* domTree = xmlParser->toDom(respuesta);
		delete(xmlParser);
		string mensajeRespuesta;

		if (domTree)
		{
			Elemento* domRaiz = domTree->getRaiz();
			for(list<Elemento*>::iterator it = domRaiz->getHijos()->begin(); 
				it != domRaiz->getHijos()->end(); it++) 
			{
				for(list<Elemento*>::iterator it0 = (*it)->getHijos()->begin(); 
				it0 != (*it)->getHijos()->end(); it0++) 
				{
						if (MensajesUtil::sonIguales((*it0)->getNombre(), XML_TAG_ERRORES))
						{
							for(list<Elemento*>::iterator it1 = (*it0)->getHijos()->begin(); 
								it1 != (*it0)->getHijos()->end(); it1++) 
							{					
									parametrosRecibidos.push_back((*it1)->getTexto());
									ok = false;
							}
						}
						else if (MensajesUtil::sonIguales((*it0)->getNombre(), XML_TAG_RESULTADOS))
						{
							for(list<Elemento*>::iterator it2 = (*it0)->getHijos()->begin(); 
								it2 != (*it0)->getHijos()->end(); it2++) 
							{					
									parametrosRecibidos.push_back((*it2)->getTexto());
							}
						}
				}
			}
		}
	} 
	catch (PokerException& e) 
	{
		RecursosCliente::getLog()->escribir(&(Respuesta)e.getError());
		ok = false;
	}

	return ok;
}

string OperacionUICliente::getError()
{
	return "";
}
