
#include <vld.h>
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
	DomTree* tree = new DomTree();
	Parser* parser = new XmlParser();


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

		} catch(ParserException& ex1 ) {
			cout<< ex1.getMensaje() <<endl;
		}

		try {
			e->agregarAtributo("uno", "dos");

		} catch(ParserException& ex2 ) {
			cout<< ex2.getMensaje() <<endl;

		} catch(exception& ex3 ) {
			cout<< ex3.what() <<endl;
		}

		
		cout << parser->toString(tree) << endl;


try {
DomTree* otroArbol = parser->toDom("ESTA ES LA PRIMER LINEA.\nEsta es la segunda.\n");
cout << "ANTES DEL DELETE DEL OTRO ARBOL" << endl;
delete(otroArbol);

} catch(ParserException& ex4 ) {
	cout<< ex4.getMensaje() <<endl;
	//delete(ex4);
}

try {
DomTree* otroArbol = parser->toDom("<");
cout << "deberia funcionar" << endl;
delete(otroArbol);

} catch(ParserException& ex5 ) {
	cout<< ex5.getMensaje() <<endl;
	//delete(ex5);
}

try {
DomTree* otroArbol = parser->toDom("            <");
cout << "deberia funcionar con espacios " << endl;
delete(otroArbol);

} catch(ParserException& ex6 ) {
	cout<< ex6.getMensaje() <<endl;
	//delete(ex6);
}




try {
DomTree* otroArbol = parser->toDom("<pedido>");
cout << "ok <pedido>" << endl;
delete(otroArbol);

} catch(ParserException& ex7 ) {
	cout<< ex7.getMensaje() <<endl;
	//delete(ex7);
}

try {
DomTree* otroArbol = parser->toDom("            <pedido");
cout << "ok <pedido" << endl;
delete(otroArbol);

} catch(ParserException& ex8 ) {
	cout<< ex8.getMensaje() <<endl;
	//delete(ex8);
}

try {
DomTree* otroArbol = parser->toDom("            <pedido/>");
cout << "ok <pedido/>" << endl;
delete(otroArbol);

} catch(ParserException& ex9 ) {
	cout<< ex9.getMensaje() <<endl;
	//delete(ex9);
}

try {
DomTree* otroArbol = parser->toDom("            <pedido  />");
cout << "ok <pedido  />" << endl;
delete(otroArbol);

} catch(ParserException& ex10 ) {
	cout<< ex10.getMensaje() <<endl;
	//delete(ex10);
}

try {
DomTree* otroArbol = parser->toDom("            <pedido  >");
cout << "ok <pedido  >" << endl;
delete(otroArbol);

} catch(ParserException& ex11 ) {
	cout<< ex11.getMensaje() <<endl;
	//delete(ex11);
}

try {
DomTree* otroArbol = parser->toDom("            <pedido    ");
cout << "ok <pedido    " << endl;
delete(otroArbol);

} catch(ParserException& ex12 ) {
	cout<< ex12.getMensaje() <<endl;
	//delete(ex12);
}

try {
DomTree* otroArbol = parser->toDom("            <otro    ");
cout << "ok <otro    " << endl;
delete(otroArbol);

} catch(ParserException& ex13 ) {
	cout<< ex13.getMensaje() <<endl;
	//delete(ex13);
}





cout << "3 espacios " << MensajesUtil::esVacio("   ") << endl;
cout << "1 espacio " << MensajesUtil::esVacio(" ") << endl;
cout << "0 espacios " << MensajesUtil::esVacio("") << endl;
string prueba = "0123456789";
cout << prueba.substr(0,3) << endl;

		
		

	

	delete(tree);
	delete(parser);

	return 0;


 }
