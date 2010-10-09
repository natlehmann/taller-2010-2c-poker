#ifndef _JUGADORAUSENTE_H__
#define _JUGADORAUSENTE_H__


#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

#include "Jugador.h"

class JugadorAusente : public Jugador
{
public:
	JugadorAusente(void);
	virtual ~JugadorAusente(void);
};

#endif //_JUGADORAUSENTE_H__
