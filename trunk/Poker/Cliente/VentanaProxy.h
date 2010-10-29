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
/*
	void chequearBloquear();
	void chequearDesbloquear();


protected:
	virtual void dibujar(SDL_Surface* superficie);
	virtual void dibujarSobreSup(SDL_Surface* superficie);
*/
public:
	VentanaProxy(void);
	virtual ~VentanaProxy(void);

	virtual void bloquear();
	virtual void desbloquear();
/*
	virtual void iniciar();
	virtual void limpiar();

	virtual Panel* getPanelComando();
	virtual void setPanelComando(Panel* panel);

	virtual ElementoGrafico* getElementoPorId(string id);

	virtual void borrarElementoPorId(string id);

	virtual void borrarElemento(ElementoGrafico* elemento);

	virtual void forzarRefresh(ElementoGrafico* elemento);


	virtual void agregarElementoGrafico(ElementoGrafico* elemento);

	virtual int getAncho();
	virtual int getAlto();
*/
};

#endif //_VENTANAPROXY_H__