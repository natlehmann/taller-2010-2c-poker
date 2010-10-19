#ifndef _VENTANAPROXY_H__
#define _VENTANAPROXY_H__

#include "SDL_Thread.h"
#include "Ventana.h"

class VentanaProxy : public Ventana
{
private:
	SDL_sem* semaforo;
	bool bloqueada;
	bool bloqueoExterno;

	void chequearBloquear();
	void chequearDesbloquear();

public:
	VentanaProxy(void);
	virtual ~VentanaProxy(void);

	virtual void bloquear();
	virtual void desbloquear();

	virtual void iniciar();
	virtual void limpiar();

	virtual Panel* getPanelComando();
	virtual void setPanelComando(Panel* panel);

	virtual ElementoGrafico* getElementoPorId(string id);

	virtual void borrarElementoPorId(string id);

	virtual void borrarElemento(ElementoGrafico* elemento);



	/* Metodos de Contenedor */
	virtual void agregarElementoGrafico(ElementoGrafico* elemento);

	
	/* Metodos de ElementoGrafico */
	virtual int getAncho();
	virtual int getAlto();
};

#endif //_VENTANAPROXY_H__