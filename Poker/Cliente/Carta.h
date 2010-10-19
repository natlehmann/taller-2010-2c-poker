#ifndef _CARTA_H__
#define _CARTA_H__


#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

#include "ElementoGrafico.h"
#include "Imagen.h"

class Carta : public ElementoGrafico {
	
	private:
		string numero;
		string palo;
		bool visible;

		Imagen* imagen;

		string getIdPalo();

	public:
		Carta(void);
		virtual ~Carta(void);

		virtual void dibujarSobreSup(SDL_Surface* superficie);

		string getNumero();
		void setNumero(string numero);
		string getPalo();
		void setPalo(string palo);
		bool getVisible();
		void setVisible(bool visible);

		virtual bool equals(ElementoGrafico* otro);

};

#endif //_CARTA_H__
