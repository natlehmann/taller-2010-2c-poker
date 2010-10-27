#include <vld.h>
#include "UIServidor.h"
#include "ContextoJuego.h"


int main (int argc, char** argv)
{
	UIServidor ui;

	ui.iniciarAplicacion();
	ContextoJuego::getInstancia()->finalizar();

	return 0;
}
