#include "Planificador.h"
#include "Timer.h"
#include "RecursosAplicacion.h"
#include "FabricaOperacionesCliente.h"
#include "OperacionUICliente.h"

Ventana* Planificador::ventana = NULL;
bool Planificador::enEjecucion = false;
bool Planificador::finalizado = false;

Planificador::Planificador(void)
{
}

Planificador::~Planificador(void)
{
}

int Planificador::planificarOperacion(void* data) {

	Timer timer;
	Planificador::enEjecucion = true;

	string idOperacion = 
		RecursosAplicacion::getClienteConfigProperties()->get("cliente.operacion.planificada.nombre");
	int ms = UtilTiposDatos::getEntero(RecursosAplicacion::getClienteConfigProperties()->get(
		"cliente.operacion.planificada.delayms"));

	FabricaOperacionesCliente fab;
	OperacionUICliente* operacion = NULL;

	while (Planificador::enEjecucion) {

		try {
			timer.iniciar();
			operacion = fab.newOperacion(idOperacion);
			operacion->ejecutar(ventana);

			if (operacion != NULL){
				delete(operacion);
				operacion = NULL;
			}

			if (timer.getMs() < ms) {
				SDL_Delay(ms - timer.getMs());
			}

			// se chequea si se dio por finalizado 
			if (!Planificador::enEjecucion) {
				Planificador::finalizado = true;
			}
		
		} catch (PokerException& e) {
			RecursosAplicacion::getLogErroresCliente()->escribir(&e.getError());
			if (operacion != NULL){
				delete(operacion);
			}
		}
	}

	return 0;
}

void Planificador::setVentana(Ventana* ventana){
	Planificador::ventana = ventana;
}

void Planificador::finalizar(){
	Planificador::enEjecucion = false;
}

bool Planificador::isFinalizado(){
	return Planificador::finalizado;
}