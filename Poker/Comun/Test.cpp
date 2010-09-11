
//#include <vld.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

#include <set>
#include <stack>
#include <map>
#include <list>

#include "Elemento.h"
#include "ParserException.h"
#include "MensajesUtil.h"
#include "DomTree.h"
#include "DomTreeFactory.h"
#include "XmlParser.h"
#include "Parser.h"
#include "PokerException.h"



using namespace std;


int main (int argc, char** argv)
{
	Parser* parser = new XmlParser();
	DomTree* tree;
	list<pair<string,bool>> pruebas;


	string xml01 = string("<pedido>\n</pedido>");
	string xml02 = string("<pedido>\n<parametros>\n</parametros>\n</pedido>");
	string xml03 = string("<pedido>\n<operacion id=\"S\"/>\n<parametros>\n<parametro nombre=\"sum\">\n3\n</parametro>")
		+ string("\n<parametro nombre=\"sum\">\n21\n</parametro>\n</parametros>\n</pedido>");
	string xml04 = string("<pedido>\n<operacion \n id=\"S\" \n/>\n</pedido>");
	string xml05 = string("<pedido>\n<\noperacion \n id=\"S\" \n/>\n</pedido>");
	string xml06 = string("\n<pedido/>\n\n\n");
	string xml07 = string("<pedido>\n<\n operacion \n id=\"S\"  \n/>\n<parametros>\n<parametro \n nombre=\"sum\"> \n  3 \n</parametro>")
		+ string("\n<parametro \n nombre=\"sum\" \n >\n 21\n</parametro>\n\n\n</parametros>\n</pedido>");
	
	string xml08 = string("<pedido>\n</pedido></pedido>");
	string xml09 = string("<pedido>\n</pedido><pedido>");
	string xml10 = string("<pedi\n</pedido><pedido>");
	string xml11 = string("<pedi/pedido><pedido>");
	string xml12 = string("<pedido\n></pedido>");
	string xml13 = string("</pedido>");
	string xml14 = string("</>");
	string xml15 = string("<pedido></pe di do>");
	string xml16 = string("<pedido></ pedido >");
	string xml17 = string("<   pedido \n></\n pedido >");
	string xml18 = string("<   pedido \n></pedido\n>");
	string xml19 = string("<pedido>/");
	string xml20 = string("<pedido/");

	// el valor booleano representa si el string se debe procesar bien (true) 
	// o lanzar una excepcion (false)

	pruebas.insert(pruebas.end(), pair<string,bool>(xml01, true));
	pruebas.insert(pruebas.end(), pair<string,bool>(xml02, true));
	pruebas.insert(pruebas.end(), pair<string,bool>(xml03, true));
	pruebas.insert(pruebas.end(), pair<string,bool>(xml04, true));
	pruebas.insert(pruebas.end(), pair<string,bool>(xml05, true));
	pruebas.insert(pruebas.end(), pair<string,bool>(xml06, true));
	pruebas.insert(pruebas.end(), pair<string,bool>(xml07, true));
	
	pruebas.insert(pruebas.end(), pair<string,bool>(xml08, false));
	pruebas.insert(pruebas.end(), pair<string,bool>(xml09, false));
	pruebas.insert(pruebas.end(), pair<string,bool>(xml10, false));
	pruebas.insert(pruebas.end(), pair<string,bool>(xml11, false));
	pruebas.insert(pruebas.end(), pair<string,bool>(xml12, true));
	pruebas.insert(pruebas.end(), pair<string,bool>(xml13, false));
	pruebas.insert(pruebas.end(), pair<string,bool>(xml14, false));
	
	pruebas.insert(pruebas.end(), pair<string,bool>(xml15, false));
	pruebas.insert(pruebas.end(), pair<string,bool>(xml16, true));
	pruebas.insert(pruebas.end(), pair<string,bool>(xml17, true));
	pruebas.insert(pruebas.end(), pair<string,bool>(xml18, false));
	pruebas.insert(pruebas.end(), pair<string,bool>(xml19, false));
	pruebas.insert(pruebas.end(), pair<string,bool>(xml20, false));

	int contador = 1;
	for (list<pair<string,bool>>::iterator it = pruebas.begin(); it != pruebas.end(); it++) {

		cout << "TEST NUMERO " << contador++ << endl;
		bool resReal = true;
		tree = NULL;

		try {
			tree = parser->toDom((*it).first);

		} catch (PokerException& e){
			resReal = false;
			cout << e.getMensaje() << endl;
		}

		if (resReal == (*it).second) {
			cout << "resultado: OK" << endl;

		} else {
			cout << "resultado: ERROR!!!!!" << endl;
		}

		if (tree != NULL) {
			cout << parser->toString(tree);
			delete(tree);
		}

		cout << endl;
	}

	

	delete (parser);






/*
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
}


try {
DomTree* otroArbol = parser->toDom("            <pedido  />");
cout << "ok <pedido  />" << endl;
delete(otroArbol);

} catch(ParserException& ex10 ) {
	cout<< ex10.getMensaje() <<endl;
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
	cout<< "LANZO Excepcion " << ex13.getMensaje() <<endl;
}

try {
DomTree* otroArbol = parser->toDom("<pedido id>");
cout << "ok <pedido id>" << endl;
delete(otroArbol);

} catch(ParserException& ex13 ) {
	cout<< "LANZO Excepcion " << ex13.getMensaje() <<endl;
}

try {
DomTree* otroArbol = parser->toDom("<pedido =\">");
cout << "ok <pedido =\">" << endl;
delete(otroArbol);

} catch(ParserException& ex13 ) {
	cout<< "LANZO Excepcion " << ex13.getMensaje() <<endl;
}

try {
DomTree* otroArbol = parser->toDom("<pedido =\"\">");
cout << "ok <pedido =\"\">" << endl;
delete(otroArbol);

} catch(ParserException& ex13 ) {
	cout<< "LANZO Excepcion " << ex13.getMensaje() <<endl;
}

try {
DomTree* otroArbol = parser->toDom("<pedido id=>");
cout << "ok <pedido id=>" << endl;
delete(otroArbol);

} catch(ParserException& ex13 ) {
	cout<< "LANZO Excepcion " << ex13.getMensaje() <<endl;
}

try {
DomTree* otroArbol = parser->toDom("<pedido id=\">");
cout << "ok <pedido id=\">" << endl;
delete(otroArbol);

} catch(ParserException& ex13 ) {
	cout<< "LANZO Excepcion " << ex13.getMensaje() <<endl;
}

try {
DomTree* otroArbol = parser->toDom("<pedido id=\"S>");
cout << "ok <pedido id=\"S>" << endl;
delete(otroArbol);

} catch(ParserException& ex13 ) {
	cout<< "LANZO Excepcion " << ex13.getMensaje() <<endl;
}

try {
DomTree* otroArbol = parser->toDom("<pedido id=\"S\">");
cout << "ok <pedido id=\"S\">" << endl;
delete(otroArbol);

} catch(ParserException& ex13 ) {
	cout<< "LANZO Excepcion " << ex13.getMensaje() <<endl;
}





cout << "3 espacios " << MensajesUtil::esVacio("   ") << endl;
cout << "1 espacio " << MensajesUtil::esVacio(" ") << endl;
cout << "0 espacios " << MensajesUtil::esVacio("") << endl;
string prueba = "0123456789";
cout << prueba.substr(0,3) << endl;

cout << "1 caracter : x --" << MensajesUtil::trim("x") << "--" << endl;
cout << "1 caracter y espacios a izq: --" << MensajesUtil::trim(" x") << "--" << endl;
cout << "1 caracter y espacios a der: --" << MensajesUtil::trim("x ") << "--" << endl;
cout << "1 caracter y espacios a ambos lados: --" << MensajesUtil::trim(" x ") << "--" << endl;
cout << "1 caracter y espacios a izq: --" << MensajesUtil::trim("    x") << "--" << endl;
cout << "1 caracter y espacios a der: --" << MensajesUtil::trim("x     ") << "--" << endl;
cout << "1 caracter y espacios a ambos lados: --" << MensajesUtil::trim("    x ") << "--" << endl;

cout << "1 caracter : x --" << MensajesUtil::trim("x") << "--" << endl;
cout << "1 caracter y espacios a izq: --" << MensajesUtil::trim(" \nx") << "--" << endl;
cout << "1 caracter y espacios a der: --" << MensajesUtil::trim("x ") << "--" << endl;
cout << "1 caracter y espacios a ambos lados: --" << MensajesUtil::trim("\nx ") << "--" << endl;
cout << "1 caracter y espacios a izq: --" << MensajesUtil::trim("    x\n") << "--" << endl;
cout << "1 caracter y espacios a der: --" << MensajesUtil::trim("x    \n") << "--" << endl;
cout << "1 caracter y espacios a ambos lados: --" << MensajesUtil::trim("\n    x ") << "--" << endl;

	delete(tree);
	delete(parser);
*/	

	return 0;


 }

