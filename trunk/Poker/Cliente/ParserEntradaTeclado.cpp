
#include "ParserEntradaTeclado.h"
#include "XmlParser.h"
#include "ParserException.h"
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

string ParserEntradaTeclado::obtenerTipoParametro(int numeroParametro)
{
	string tipoParametro;
	
	if (MensajesUtil::sonIguales(XML_OP_SUMA, this->_codigoOperacion))
		tipoParametro = XML_ATR_TIPO_SUM;
	else if (MensajesUtil::sonIguales(XML_OP_RESTA, this->_codigoOperacion))
		tipoParametro = XML_ATR_TIPO_RES;
	else if (MensajesUtil::sonIguales(XML_OP_MULT, this->_codigoOperacion))
		tipoParametro = XML_ATR_TIPO_MUL;
	else if (MensajesUtil::sonIguales(XML_OP_DIV, this->_codigoOperacion))
	{		
		if (numeroParametro == 0)
			tipoParametro = XML_ATR_TIPO_DIVISOR;
		else
			tipoParametro = XML_ATR_TIPO_DIVIDENDO;
	}

	return tipoParametro;
}

DomTree* ParserEntradaTeclado::toDom() {

	int i = 0;
	DomTree* domTree = new DomTree();

	try {

		Elemento* elementoPedido = domTree->agregarElemento(XML_TAG_PEDIDO);
		Elemento* elementoOperacion = elementoPedido->agregarHijo(XML_TAG_OPERACION);
		elementoOperacion->agregarAtributo(XML_ATR_ID,this->_codigoOperacion);
		Elemento* elementoParametros = elementoPedido->agregarHijo(XML_TAG_PARAMETROS);

		Elemento* elementoParametro;
		for (list<string>::iterator it = this->_lstOperandos->begin(); it != this->_lstOperandos->end(); it++) {
			elementoParametro = elementoParametros->agregarHijo(XML_TAG_PARAMETRO);
			elementoParametro->agregarAtributo(XML_ATR_NOMBRE,this->obtenerTipoParametro(i++));
			elementoParametro->setTexto(*it);
		}

	} catch(ParserException& ex ) {

		delete(domTree);
		throw ex;
	}

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
	//hay que probarlo!!!!
	string mensajeRespuesta;

	XmlParser* xmlParser = new XmlParser();
	DomTree* domTree = xmlParser->toDom(respuesta);
	delete(xmlParser);

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
							it1 != (*it0)->getHijos()->end(); it1++) {					
								mensajeRespuesta = (*it1)->getTexto();

							this->error = true;
						}

					}
					else if (MensajesUtil::sonIguales((*it0)->getNombre(), XML_TAG_RESULTADOS))
					{
						for(list<Elemento*>::iterator it2 = (*it0)->getHijos()->begin(); 
							it2 != (*it0)->getHijos()->end(); it2++) {					
								mensajeRespuesta = (*it2)->getNombre() + ": " + (*it2)->getTexto() + "/n";

							this->error = false;
						}
					}
			}
		}
			
	}

	return mensajeRespuesta;
}

