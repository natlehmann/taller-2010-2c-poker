#ifndef _CARTA_MODELO_H_
#define _CARTA_MODELO_H_

#include <stdlib.h>
#include <iostream>
#include <string>

using namespace std;

class CartaModelo {
	
private:
	string numero;
	string palo;
	bool visible;
	int posicion;
	string id;

public:
	CartaModelo(string numero = "", string palo = "");
	virtual ~CartaModelo(void);

	string getNumero();
	void setNumero(string numero);
	string getPalo();
	void setPalo(string palo);
	bool getVisible();
	void setVisible(bool visible);
	int getPosicion();
	void setPosicion(int posicion);

	string getIdPalo();
	int getValorNumerico();
	string getId();

};

#endif //_CARTA_MODELO_H_
