
#include "DomTreeFactory.h"
#include "DomTree.h"
#include "Elemento.h"
#include "ArrayUtil.h"
#include "MensajesUtil.h"
#include "ParserException.h"
#include "DomTreeFactoryInstance.h"
#include "RecursosAplicacion.h"
#include "Properties.h"


// Inicializacion de Miembros estaticos
map<string, DomTreeFactoryInstance> DomTreeFactory::configuraciones;
string DomTreeFactory::defaultConfig = "";

SDL_sem* DomTreeFactory::semaforo = SDL_CreateSemaphore(1);


DomTreeFactory::DomTreeFactory(void)
{
}

DomTreeFactory* DomTreeFactory::config(string nombreConfig){

	DomTreeFactory* resultado = NULL;

	SDL_SemWait(DomTreeFactory::semaforo);

	if (DomTreeFactory::configuraciones.empty()) {
		DomTreeFactory::inicializar();
	}

	map<string, DomTreeFactoryInstance>::iterator it = DomTreeFactory::configuraciones.find(nombreConfig);
	if (it != DomTreeFactory::configuraciones.end()) {
		resultado = &(it->second);	
	}

	SDL_SemPost(DomTreeFactory::semaforo);

	if (resultado == NULL) {
		throw ParserException("La configuracion del parser " + nombreConfig + " no es valida.", "V");
	}

	return resultado;
}

void DomTreeFactory::finalizar() {
	SDL_DestroySemaphore(DomTreeFactory::semaforo);
}

void DomTreeFactory::inicializar(){

	Properties* prop = RecursosAplicacion::getParserConfigProperties();
	string configs = prop->get("parser.configs");
	list<string> listaConfigs = MensajesUtil::split(configs);

	for (list<string>::iterator it = listaConfigs.begin(); it != listaConfigs.end(); it++) {

		DomTreeFactoryInstance instance(*it);

		string elementos = prop->get("parser." + (*it) + ".elementos");
		list<string> listaElementos = MensajesUtil::split(elementos);
		instance.setElementos(listaElementos);

		map<string,string> hijosPorElemento;
		map<string,string> attPorElemento;

		for (list<string>::iterator itElem = listaElementos.begin(); 
			itElem != listaElementos.end(); itElem++) {

				string hijos = prop->get("parser." + (*it) + "." + (*itElem) + ".hijos");
				hijosPorElemento.insert(pair<string,string>((*itElem), hijos));

				string atributos = prop->get("parser." + (*it) + "." + (*itElem) + ".atributos");
				attPorElemento.insert(pair<string,string>((*itElem), atributos));
		}

		instance.setHijosPorElemento(hijosPorElemento);
		instance.setAttPorElemento(attPorElemento);

		DomTreeFactory::configuraciones.insert(pair<string,DomTreeFactoryInstance>((*it), instance));
	}

	DomTreeFactory::defaultConfig = prop->get("parser.default.config");
}


Elemento* DomTreeFactory::crearElemento(string nombre) {

	if (DomTreeFactory::configuraciones.empty()) {
		DomTreeFactory::inicializar();
	}

	return DomTreeFactory::config(DomTreeFactory::defaultConfig)->elemento(nombre);	
}


// Este metodo debe ser redefinido en las subclases
Elemento* DomTreeFactory::elemento(string nombre){
	return NULL;
}


