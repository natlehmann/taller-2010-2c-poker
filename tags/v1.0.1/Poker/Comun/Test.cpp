
#include <vld.h>
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
#include "XmlParserArchivo.h"



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

	

	list<string> archivos;

	archivos.push_back("..\\tests\\test1.txt");
	archivos.push_back("..\\tests\\test2.txt");
	archivos.push_back("..\\tests\\test3.txt");
	archivos.push_back("..\\tests\\test4.txt");
	archivos.push_back("..\\tests\\test5.txt");
	archivos.push_back("..\\tests\\test6.txt");
	archivos.push_back("..\\tests\\test7.txt");
	archivos.push_back("..\\tests\\test8.txt");
	archivos.push_back("..\\tests\\test9.txt");
	archivos.push_back("..\\tests\\test10.txt");
	archivos.push_back("..\\tests\\test11.txt");
	archivos.push_back("..\\tests\\test12.txt");
	archivos.push_back("..\\tests\\test13.txt");
	archivos.push_back("..\\tests\\test14.txt");
	archivos.push_back("..\\tests\\test15.txt");
	archivos.push_back("..\\tests\\test16.txt");
	archivos.push_back("..\\tests\\test17.txt");
	archivos.push_back("..\\tests\\test18.txt");
	archivos.push_back("..\\tests\\test19.txt");
	archivos.push_back("..\\tests\\test20.txt");


	for (list<string>::iterator itt = archivos.begin(); itt != archivos.end(); itt++) {
		
		cout << "Procesando archivo " << *itt << endl;
		XmlParserArchivo* parserArch = new XmlParserArchivo(*itt);
		int contPedido = 1;

		try {
			DomTree* dt = parserArch->getSiguiente();

			while (dt != NULL) {	
				cout << "Pedido " << contPedido++ << endl;
				cout << parser->toString(dt) << endl;

				delete (dt);
				dt = parserArch->getSiguiente();
			}

		} catch (PokerException& e){
			cout << e.getMensaje() << endl;
		}

		
		cout << endl << endl;
		delete (parserArch);
	}



	delete (parser);

	return 0;


 }

