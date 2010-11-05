#ifndef _MESA_MODELO_H_
#define _MESA_MODELO_H_

#include <string>

#define SMALL_BLIND 1
#define FONDO ""

using namespace std;

class MesaModelo
{
private:
	int id;
	int smallBlind;
	int apuestaMaxima;
	string fondo;

public:
	MesaModelo(int id, int smallBlind = SMALL_BLIND, string fondo = FONDO);
	virtual ~MesaModelo(void);

	int getId();
	int getSmallBlind();
	string getFondo();

	void setApuestaMaxima(int apuestaMaxima);
	int getApuestaMaxima();

};

#endif //_MESA_MODELO_H_
