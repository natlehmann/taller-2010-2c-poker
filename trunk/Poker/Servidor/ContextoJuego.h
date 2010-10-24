#ifndef _CONTEXTOJUEGO_H_
#define _CONTEXTOJUEGO_H_

#include <string>


using namespace std;

class ContextoJuego
{
private:
	static const ContextoJuego instancia;

protected:
	ContextoJuego(void);

public:	
	virtual ~ContextoJuego(void);

	static const ContextoJuego* getInstancia();
};

#endif //_CONTEXTOJUEGO_H_
