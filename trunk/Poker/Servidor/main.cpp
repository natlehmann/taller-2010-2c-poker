#include <vld.h>
#include "UIServidor.h"
#include "ContextoJuego.h"
#include "SincronizadorThreads.h"


int main (int argc, char** argv)
{
	UIServidor ui;

	ui.iniciarAplicacion();

	ContextoJuego::getInstancia()->finalizar();
	delete(ContextoJuego::getInstancia());
	//delete(SincronizadorThreads::getInstancia());
	
	return 0;
}
