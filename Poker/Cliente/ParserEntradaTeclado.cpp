
#include "ParserEntradaTeclado.h"
#include "XmlParser.h"
#include "DomTree.h"
#include "Elemento.h"
#include "MensajesUtil.h"

ParserEntradaTeclado::ParserEntradaTeclado(string codigoOperacion, list<string>* lstOperandos)
{
	this->_codigoOperacion = codigoOperacion;
	this->_lstOperandos = lstOperandos;
}

ParserEntradaTeclado::~ParserEntradaTeclado(void)
{	
	
}

DomTree* ParserEntradaTeclado::toDom() {

	DomTree* domTree = new DomTree();

	//try {

			Elemento* elementoPedido = domTree->agregarElemento("pedido");
			Elemento* elementoOperacion = elementoPedido->agregarHijo("operacion");
			elementoOperacion->agregarAtributo("id",this->_codigoOperacion);
			Elemento* elementoParametros = elementoPedido->agregarHijo("parametros");

			Elemento* elementoParametro;
			for (list<string>::iterator it = this->_lstOperandos->begin(); it != this->_lstOperandos->end(); it++) {
				elementoParametro = elementoParametros->agregarHijo("parametro");
				elementoParametro->agregarAtributo("nombre","dividendo");
				elementoParametro->setTexto(*it);
			}

	//} catch(Exception ex ) {

	//	delete(domTree);
	//	throw ex;
	//}

	return domTree;
}

string ParserEntradaTeclado::generarMensaje()
{
	DomTree* domTree = this->toDom();

	XmlParser* xmlParser = new XmlParser();
	string mensaje = xmlParser->toString(domTree);
	delete(xmlParser);

	return mensaje;
}

string ParserEntradaTeclado::obtenerRespuesta(string respuesta)
{
	string mensajeRespuesta;

	XmlParser* xmlParser = new XmlParser();
	DomTree* domTree = xmlParser->toDom(respuesta);
	delete(xmlParser);

	if (domTree)
	{
		Elemento* domRespuesta = domTree->getRaiz();
		for(list<Elemento*>::iterator it = domRespuesta->getHijos()->begin(); 
			it != domRespuesta->getHijos()->end(); it++) {
			
				if (MensajesUtil::sonIguales((*it)->getNombre(), "errores"))
				{
					for(list<Elemento*>::iterator it1 = (*it)->getHijos()->begin(); 
						it1 != (*it)->getHijos()->end(); it1++) {					
							mensajeRespuesta = (*it1)->getTexto();
					}
				}
				else if (MensajesUtil::sonIguales((*it)->getNombre(), "resultados"))
				{
					for(list<Elemento*>::iterator it2 = (*it)->getHijos()->begin(); 
						it2 != (*it)->getHijos()->end(); it2++) {					
							mensajeRespuesta = (*it2)->getNombre() + ": " + (*it2)->getTexto() + "/n";
					}
				}
		}
	}

	return mensajeRespuesta;
}

