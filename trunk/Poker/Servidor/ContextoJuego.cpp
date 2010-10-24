#include "ContextoJuego.h"

ContextoJuego ContextoJuego::instancia;

ContextoJuego::ContextoJuego(void)
{
}

ContextoJuego::~ContextoJuego(void)
{
}

ContextoJuego* ContextoJuego::getInstancia(){
	return &ContextoJuego::instancia;
}

int ContextoJuego::getCantidadJugadoresActivos(){
	//TODO: IMPLEMENTAR
	return 0;
}

void ContextoJuego::iniciarJuego(){
	//TODO: IMPLEMENTAR
}

MesaModelo* ContextoJuego::getMesa(){
	//TODO: IMPLEMENTAR
	return NULL;
}

BoteModelo* ContextoJuego::getBote() {
	//TODO: IMPLEMENTAR
	return NULL;
}
