#include "OpJugadorVirtual.h"
#include "ContextoJuego.h"

class OpIgualarJugadorVirtual :	public OpJugadorVirtual
{
protected:
	virtual void ejecutarAccion();
public:
	OpIgualarJugadorVirtual(int idCliente);
	~OpIgualarJugadorVirtual();
};
