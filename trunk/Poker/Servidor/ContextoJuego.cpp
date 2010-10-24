#include "ContextoJuego.h"

const ContextoJuego ContextoJuego::instancia;

ContextoJuego::ContextoJuego(void)
{
}

ContextoJuego::~ContextoJuego(void)
{
}

const ContextoJuego* ContextoJuego::getInstancia(){
	return &ContextoJuego::instancia;
}
