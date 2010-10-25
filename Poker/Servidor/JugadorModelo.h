#ifndef _JUGADOR_MODELO_H_
#define _JUGADOR_MODELO_H_

#include <string>
#include "CartaModelo.h"

#define NOMBRE_IMAGEN ""

using namespace std;

class JugadorModelo
{
private:
	int id;
	string nombre;
	int fichas;
	int posicion;
	string nombreImagen;
	CartaModelo* carta1;
	CartaModelo* carta2;
	int apuesta;
	bool activo;
	bool jugandoRonda;

public:
	JugadorModelo(int id, string nombre, int fichas, int posicion, string nombreImagen = NOMBRE_IMAGEN);
	virtual ~JugadorModelo(void);

	int getId();
	void setId(int id);

	string getNombre();
	void setNombre(string nombre);

	int getFichas();
	void setFichas(int fichas);

	int getPosicion();
	void setPosicion(int posicion);

	string getNombreImagen();
	void setNombreImagen(string nombreImagen);

	CartaModelo* getCarta1();
	void setCarta1(CartaModelo* carta);

	CartaModelo* getCarta2();
	void setCarta2(CartaModelo* carta);

	int getApuesta();
	void setApuesta(int apuesta);

	bool isActivo();
	void setActivo(bool activo);

	bool isJugandoRonda();
	void setJugandoRonda(bool jugandoRonda);

	void apostar(int fichas);
	void incrementarFichas(int cantidad);
};

#endif //_JUGADOR_MODELO_H_
