#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

#include <set>
#include "Elemento.h"
#include "ParserException.h"
#include "MensajesUtil.h"
#include "DomTree.h"
#include "DomTreeFactory.h"
#include "XmlParser.h"
#include "Parser.h"


using namespace std;


int main (int argc, char** argv)
{

	try {
		DomTree* tree = new DomTree();
		cout << "arbol creado" << endl;

		Elemento* e = tree->agregarElemento("pedido");
		cout << "elemento pedido creado" << endl;

		Elemento* e2 = e->agregarHijo("operacion");
		cout << "elemento operacion creado" << endl;

		e2->agregarAtributo("id","S");
		cout << "atributo id agregado" << endl;

		Elemento* e3 = e->agregarHijo("parametros");
		Elemento* e4 = e3->agregarHijo("parametro");
		e4->agregarAtributo("nombre","sum");
		e4->setTexto("15.4");
		Elemento* e5 = e3->agregarHijo("parametro");
		e5->agregarAtributo("nombre","sum");
		e5->setTexto("4");

		try {
			e->agregarHijo("otro");

		} catch(ParserException& ex ) {
			cout<< ex.getMensaje() <<endl;
		}

		try {
			e->agregarAtributo("uno", "dos");

		} catch(ParserException& ex ) {
			cout<< ex.getMensaje() <<endl;

		} catch(exception& ex ) {
			cout<< ex.what() <<endl;
		}

		Parser* parser = new XmlParser();
		cout << parser->toString(tree) << endl;


		delete(tree);
		delete(parser);

	} catch(exception& ex ) {
		cout<< ex.what() <<endl;
	}

	return 0;


 }

