#ifndef UTILTIPOSDATOS_H_
#define UTILTIPOSDATOS_H_

#include <string>
using namespace std;

class UtilTiposDatos {
public:
	UtilTiposDatos();
	virtual ~UtilTiposDatos();

	static string doubleToString(double numero);

	static double stringToDouble(string numero);

	static bool isInteger(double numero);
};

#endif /* UTILTIPOSDATOS_H_ */
