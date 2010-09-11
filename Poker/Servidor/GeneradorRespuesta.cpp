
#include "GeneradorRespuesta.h"
#include "DomTree.h"
#include "DomTreeFactory.h"
#include "MensajesUtil.h"

using namespace std;

GeneradorRespuesta::GeneradorRespuesta(void)
{
}

GeneradorRespuesta::~GeneradorRespuesta(){
	this->limpiar();
}

void GeneradorRespuesta::agregarRespuesta(Respuesta* respuesta)
{
	if (respuesta->isError()) {
		listaErrores.push_back(respuesta);

	} else {
		listaResultados.push_back(respuesta);
	}
}

void GeneradorRespuesta::agregarRespuestas(vector<Respuesta*> respuestas) {
	for (vector<Respuesta*>::iterator it = respuestas.begin() ;
		it != respuestas.end(); it++) {
			this->agregarRespuesta(*it);
	}
}

void GeneradorRespuesta::limpiar() {

	if (!this->listaErrores.empty()) {
		for (list<Respuesta*>::iterator it = this->listaErrores.begin() ;
			it != this->listaErrores.end(); it++) {
				delete (*it);
		}
	}

	if (!this->listaResultados.empty()) {
		for (list<Respuesta*>::iterator it = this->listaResultados.begin() ;
			it != this->listaResultados.end(); it++) {
				delete (*it);
		}
	}
}


string GeneradorRespuesta::obtenerRespuesta()
{
	Parser* parser = new XmlParser();		
	DomTree* tree = new DomTree();
	Elemento* raiz = tree->agregarElemento("respuesta");

	if (!this->listaErrores.empty()) {

		// se procesan errores

		list<Respuesta*>::iterator it = this->listaErrores.begin();
		Respuesta* respuesta = *it;

		Elemento* elem = raiz->agregarHijo("operacion");

		if(MensajesUtil::esVacio(respuesta->getIdOperacion())) {
			elem->agregarAtributo("id","");
		} else {
			elem->agregarAtributo("id",respuesta->getIdOperacion());
		}

		elem = raiz->agregarHijo("errores");

		for (it = listaErrores.begin(); it != listaErrores.end(); it++) {

			Elemento* error = elem->agregarHijo("error");
			error->agregarAtributo("tipo",respuesta->getId());
			error->setTexto(respuesta->getValor());
		}


	} else {

		// se procesan resultados
		
		list<Respuesta*>::iterator it = this->listaResultados.begin();
		Respuesta* respuesta = *it;

		Elemento* elem = raiz->agregarHijo("operacion");
		elem->agregarAtributo("id",respuesta->getIdOperacion());

		elem = raiz->agregarHijo("resultados");

		for (it = listaResultados.begin(); it != listaResultados.end(); it++) {

			Elemento* resul = elem->agregarHijo("resultado");
			resul->agregarAtributo("nombre",respuesta->getId());
			resul->setTexto(respuesta->getValor());
		}
	}


	string respuesta = parser->toString(tree);

	delete(parser);
	delete(tree);

	return respuesta;
}