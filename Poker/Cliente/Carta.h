#include "ElementoGrafico.h"
#include "Imagen.h"

class Carta : public ElementoGrafico {
	
	private:
		string numero;
		string palo;
		bool visible;

		Imagen* imagen;

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

};
