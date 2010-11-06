#include "OpJugadorVirtual.h"

class OpNoIrJugadorVirtual : public OpJugadorVirtual
{
protected:
	virtual void ejecutarAccion();
public:
	OpNoIrJugadorVirtual(int idCliente);
	~OpNoIrJugadorVirtual(void);
};
