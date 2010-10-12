#include "JugadorAusente.h"
#include "Imagen.h"
#include "RecursosAplicacion.h"
#include "UtilTiposDatos.h"

JugadorAusente::JugadorAusente(void)
{
	this->setImagen(new Imagen(RecursosAplicacion::getClienteConfigProperties()->get(
		"cliente.tema.default.jugador.ausente.imagen")));
}

JugadorAusente::~JugadorAusente(void)
{
}
