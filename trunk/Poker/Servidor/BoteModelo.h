#ifndef _BOTE_MODELO_H_
#define _BOTE_MODELO_H_

#include <string>

#define NOMBRE_IMAGEN ""

using namespace std;

class BoteModelo
{
private:
	int id;
	string nombreImagen;
	int cantidad;

public:
	BoteModelo(int id, string nombreImagen = NOMBRE_IMAGEN);
	virtual ~BoteModelo(void);

	int getId();
	string getNombreImagen();
	int getCantidad();

	void incrementar(int cantidad);
	int vaciar();
};

#endif //_BOTE_MODELO_H_
