#include "JugadorAusente.h"
#include "Imagen.h"
#include "RecursosAplicacion.h"
#include "UtilTiposDatos.h"

JugadorAusente::JugadorAusente(void)
{
	this->setImagen(new Imagen(RecursosAplicacion::getClienteConfigProperties()->get(
		"cliente.tema.default.jugador.ausente.imagen")));
	this->getImagen()->setAlto(UtilTiposDatos::getEntero(
		RecursosAplicacion::getClienteConfigProperties()->get(
		"cliente.tema.default.jugador.ausente.imagen.alto")));
	this->getImagen()->setAncho(UtilTiposDatos::getEntero(
		RecursosAplicacion::getClienteConfigProperties()->get(
		"cliente.tema.default.jugador.ausente.imagen.ancho")));
}

JugadorAusente::~JugadorAusente(void)
{
}
