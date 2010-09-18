#ifndef UTILTIPOSDATOS_H_
#define UTILTIPOSDATOS_H_

#define _SI_  "S"
#define _NO_ "N"
#define _si_  "s"
#define _no_ "n"
#define _ERROR_ -1
#define _PUNTO_ '.'
#define _MENOS_ '-'

#include <string>
using namespace std;

class UtilTiposDatos {
public:
	UtilTiposDatos();
	virtual ~UtilTiposDatos();

	static string doubleAString(double numero);

	static double stringADouble(string numero);

	static bool esEntero(double numero);

	static bool esEntero(string numero);

	static int getEntero(string numero);

	static bool esDouble(string numero);

	static bool validarSiNo(string valor);

private:
	static bool esDigito(int caracter);
};

#endif /* UTILTIPOSDATOS_H_ */
