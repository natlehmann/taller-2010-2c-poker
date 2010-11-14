#include "AccesoDatos.h"

AccesoDatos::AccesoDatos(void)
{
	this->conectar();
}

AccesoDatos::~AccesoDatos(void)
{
	this->desconectar();
}

string AccesoDatos::getMensajeError()
{
	return this->msgError;
}
bool AccesoDatos::conectar()
{
	// Se establece la conexion con la BD
	sqlite3_open("poker.db",&this->db);
	
	// Se comprueba error de conexion
	if (sqlite3_errcode(this->db)!=0)
	{
		this->msgError = sqlite3_errmsg(this->db);
		return false;
	}
	else
		return true;
}

bool AccesoDatos::desconectar()
{
	// Se cierra la conexion con la BD
	if (sqlite3_close(this->db)!=0)
		{
			this->msgError = sqlite3_errmsg(this->db);
			return false;
		}
	else
		return true;
}

bool AccesoDatos::ejecutarNonQuery(string sql)
{
	sqlite3_exec(this->db, sql.c_str(), NULL, NULL, NULL);
	
	if (sqlite3_errcode(this->db)!=0)
	{
		this->msgError = sqlite3_errmsg(this->db);
		return false;
	}
	else
		return true;
}

bool AccesoDatos::ejecutar(string sql)
{
	sqlite3_prepare(this->db, sql.c_str(), sql.length(), &resultado, NULL);
	
	if (sqlite3_errcode(this->db)!=0)
	{
		this->msgError = sqlite3_errmsg(this->db);
		return false;
	}
	else
		return true;
}

string AccesoDatos::getFechaActual()
{
	time_t tSac = time(NULL);  // instante actual
		
	struct tm* pt1 = localtime(&tSac);
	string dia = UtilTiposDatos::enteroAString(pt1->tm_mday);
	string mes = UtilTiposDatos::enteroAString(pt1->tm_mon+1);
	string anio = UtilTiposDatos::enteroAString(pt1->tm_year+1900);

	if (dia.length() == 1)
		dia = "0" + dia;

	if (mes.length() == 1)
		mes = "0" + mes;

	string fecha = dia + "/" + mes + "/" + anio;
	
	return fecha;	
}

string AccesoDatos::getHoraActual()
{
	time_t tSac = time(NULL);  // instante actual
		
	struct tm* pt1 = localtime(&tSac);
	string horas = UtilTiposDatos::enteroAString(pt1->tm_hour);
	string minutos = UtilTiposDatos::enteroAString(pt1->tm_min);
	string segundos = UtilTiposDatos::enteroAString(pt1->tm_sec);

	if (horas.length() == 1)
		horas = "0" + horas;

	if (minutos.length() == 1)
		minutos = "0" + minutos;

	if (segundos.length() == 1)
		segundos = "0" + segundos;

	string horaActual = horas + ":" + minutos + ":" + segundos;
	
	return horaActual;	
}

int AccesoDatos::getCantDiasDelMes(int mes, int anio)
{
	int resul = 31;

	switch (mes) 
	{
		case 2:
			if ((anio % 4 == 0) && ((anio % 100 != 0) || (anio % 400 == 0)))
				resul = 29;
			else
				resul = 28;
			break;

		case 4:
			resul = 30;
			break;

		case 6:
			resul = 30;
			break;

		case 9:
			resul = 30;
			break;

		case 11:
			resul = 30;
			break;
	
	}

	return resul;
}


bool AccesoDatos::existeTabla(string nombreTabla)
{
	bool bResul = false;
	string sql = "SELECT name FROM sqlite_master WHERE type='table' AND name='" + nombreTabla + "';";

	this->ejecutar(sql);

	if (sqlite3_errcode(db)==0)
	{
		while (sqlite3_step(resultado)==SQLITE_ROW)
		{
			bResul = true;
		}
	}
	
	return bResul;
}

bool AccesoDatos::crearTabla(string nombreTabla)
{
	string sql = "CREATE TABLE " + nombreTabla + " (";

	if (MensajesUtil::sonIguales(nombreTabla, "jugadores"))
	{
		sql += "id integer primary key autoincrement not null, ";
		sql += "usuario varchar(30), ";
		sql += "nombre varchar(30), ";
		sql += "apellido varchar(30), ";
		sql += "password varchar(30), ";
		sql += "nombreImagen varchar(30), ";
		sql += "cantFichas integer, ";
		sql += "fechaRegistro varchar(10), ";
		sql += "horaRegistro varchar(8));";
	}
	else if (MensajesUtil::sonIguales(nombreTabla, "sesion"))
	{
		sql += "id integer primary key autoincrement not null, ";
		sql += "usuario varchar(30), ";
		sql += "fechaInicio varchar(10), ";
		sql += "horaInicio varchar(8), ";
		sql += "fechaFin varchar(10), ";
		sql += "horaFin varchar(8), ";
		sql += "observador varchar(1), ";
		sql += "virtual varchar(1));";
	}
	else if (MensajesUtil::sonIguales(nombreTabla, "fichas"))
	{
		sql += "id integer primary key autoincrement not null, ";
		sql += "usuario varchar(30), ";
		sql += "fechaCompra varchar(10), ";
		sql += "cantComprada integer);";
	}

	return this->ejecutarNonQuery(sql);
}

bool AccesoDatos::eliminarTabla(string nombreTabla)
{
	string sql = "DROP TABLE IF EXISTS " + nombreTabla + ";";
	return this->ejecutarNonQuery(sql);
}

bool AccesoDatos::borrarDatosTabla (string nombreTabla)
{
	string sql = "DELETE FROM " + nombreTabla + ";";
	return this->ejecutarNonQuery(sql);
}

void AccesoDatos::inicializarBaseDatos()
{
	//this->eliminarTabla("jugadores");
	//this->eliminarTabla("sesion");
	//this->eliminarTabla("fichas");

	if (!this->existeTabla("jugadores"))
		this->crearTabla("jugadores");

	if (!this->existeTabla("sesion"))
		this->crearTabla("sesion");

	if (!this->existeTabla("fichas"))
		this->crearTabla("fichas");
}

bool AccesoDatos::grabarNuevoJugador(string usuario, string password, string nombre, string apellido)
{
	bool resul = false;

	if (!this->obtenerJugador(usuario))
	{
		resul = this->registrarNuevoJugador(usuario, password, nombre, apellido);
	}
	else
		this->msgError = "No se pudo grabar el Jugador. Ya existe un jugador con ese nombre.";

	return resul;
}

bool AccesoDatos::registrarNuevoJugador(string usuario, string password, string nombre, string apellido)
{
	string fechaActual = this->getFechaActual();
	string horaActual = this->getHoraActual();

	string sql = "INSERT INTO jugadores (usuario, password, nombre, apellido, nombreImagen, cantFichas, fechaRegistro, horaRegistro) VALUES ('";
	sql += usuario + "', '";
	sql += password + "', '";
	sql += nombre + "', '";
	sql += apellido + "',";
	sql += "'', ";
	sql += "2000, '";				// se crea cada jugador con 2.000 fichas
	sql += fechaActual +  "', '";
	sql += horaActual +  "');";

	return this->ejecutarNonQuery(sql);
}

bool AccesoDatos::consultarJugador(string usuario)
{
	string sql = "SELECT id, usuario, nombre, apellido, password, nombreImagen, cantFichas, fechaUltCompraFichas FROM jugadores WHERE usuario = '" + usuario + "';";
	return this->ejecutar(sql);
}

bool AccesoDatos::consultarJugadorById(int idJugador)
{
	string sql = "SELECT id, usuario, nombre, apellido, password, nombreImagen, cantFichas, fechaUltCompraFichas FROM jugadores WHERE id = " + UtilTiposDatos::enteroAString(idJugador) + ";";
	return this->ejecutar(sql);
}

JugadorModelo* AccesoDatos::obtenerJugador(string usuario)
{
	int id;
	string password;
	string nombreImagen;
	int cantFichas;
	JugadorModelo* jugador = NULL;

	if (this->consultarJugador(usuario))
	{
		while (sqlite3_step(resultado)==SQLITE_ROW)
		{
			id = sqlite3_column_int(resultado, 0);
			password = string(reinterpret_cast<const char*>(sqlite3_column_text(resultado, 4)));
			nombreImagen = string(reinterpret_cast<const char*>(sqlite3_column_text(resultado, 5)));
			cantFichas = sqlite3_column_int(resultado, 6);

			jugador = new JugadorModelo(id, usuario, cantFichas, 0, password, nombreImagen);
		}
	}

	return jugador;
}

bool AccesoDatos::grabarCompraFichas(string usuario, int cantFichasAComprar)
{
	int cantFichasActual;
	string sql;
	bool resul = false;

	if (this->consultarJugador(usuario))
	{
		while (sqlite3_step(resultado)==SQLITE_ROW)
		{
			cantFichasActual = sqlite3_column_int(resultado, 6);
			cantFichasActual = cantFichasActual + cantFichasAComprar;
						
			// Se actualiza la cantidad de fichas del jugador en la tabla "JUGADORES"
			if(this->actualizarCantFichas(usuario, cantFichasActual))
			{
				// Se registra la compra en la tabla "FICHAS"
				resul = this->registrarCompraFichas(usuario, cantFichasAComprar);
			}
		}		
	}
	return resul;
}
bool AccesoDatos::actualizarNombreImagen(string usuario, string nuevoNombreImagen)
{
	string sql = "UPDATE jugadores SET nombreImagen = '" + nuevoNombreImagen + "' WHERE usuario = '" + usuario +  "';";
	return this->ejecutarNonQuery(sql);
}

bool AccesoDatos::validarCantFichasJugador(string usuario)
{
	bool resul = false;
	
	if (this->consultarCantFichas(usuario))
	{
		while (sqlite3_step(resultado)==SQLITE_ROW)
		{
			int cantFichas = sqlite3_column_int(resultado, 0);
			
			// Se valida que el jugador tenga menos de 100 fichas
			if (cantFichas <= 100)
				resul = true;
		}		
	}
	return resul;
}
bool AccesoDatos::consultarCantFichas(string usuario)
{
	string sql = "SELECT cantFichas FROM jugadores WHERE usuario = '" + usuario + "';";
	return this->ejecutar(sql);
}

bool AccesoDatos::actualizarCantFichas(string usuario, int cantFichas)
{
	string sql = "UPDATE jugadores SET cantFichas = " + UtilTiposDatos::enteroAString(cantFichas) + " WHERE usuario = '" + usuario +  "';";
	return this->ejecutarNonQuery(sql);
}

int AccesoDatos::grabarInicioSesion(string usuario, string esObservador, string esVirtual)
{
	int resul = -1;
	string fechaInicio = this->getFechaActual();
	string horaInicio = this->getHoraActual();

	// Primero se cierra las sesiones del usuario que podrian haber quedado abiertas por alguna razon
	if (this->cerrarSesionesAnteriores(usuario))
	{
		string sql = "INSERT INTO sesion (usuario, fechaInicio, horaInicio, fechaFin, horaFin, observador, virtual) VALUES ('";
		sql += usuario + "', '";
		sql += fechaInicio + "', '";
		sql += horaInicio + "', '";
		sql += "', '', '";
		sql += esObservador + "', '";
		sql += esVirtual + "');";

		if (this->ejecutarNonQuery(sql))
		{
			string sql = "SELECT MAX(id) FROM sesion WHERE usuario = '" + usuario + "'";
		
			if (this->ejecutar(sql))
			{
				while (sqlite3_step(resultado)==SQLITE_ROW)
				{	
					resul = sqlite3_column_int(resultado, 0);				
				}
			}
		}		
	}

	return resul;
}

bool AccesoDatos::cerrarSesionesAnteriores(string usuario)
{
	string fechaFin = this->getFechaActual();
	string horaFin = this->getHoraActual();

	string sql = "UPDATE sesion SET fechaFin = '" + fechaFin + "', horaFin = '" + horaFin + "' WHERE usuario = '" + usuario + "' AND fechaFin = ''";
	
	return this->ejecutarNonQuery(sql);
}

bool AccesoDatos::grabarFinSesion(int idSesion)
{
	string fechaFin = this->getFechaActual();
	string horaFin = this->getHoraActual();

	string sql = "UPDATE sesion SET fechaFin = '" + fechaFin + "', horaFin = '" + horaFin + "' WHERE id = " + UtilTiposDatos::enteroAString(idSesion);
	
	return this->ejecutarNonQuery(sql);
}

bool AccesoDatos::validarCantFichasCompradasHoy(string usuario, int cantFichasAComprar)
{
	bool resul = false;
	
	if (this->consultarCantFichasCompradasHoy(usuario))
	{
		while (sqlite3_step(resultado)==SQLITE_ROW)
		{
			int cantFichasCompradasHoy = sqlite3_column_int(resultado, 0);
			
			// Se valida que las fichas compradas hoy y las que se desean comprar no superen las 2.0000
			if ((cantFichasCompradasHoy + cantFichasAComprar) <= 2000)
				resul = true;
		}		
	}

	return resul;
}

bool AccesoDatos::registrarCompraFichas(string usuario, int cantFichasCompradas)
{
	string fechaActual = this->getFechaActual();

	string sql = "INSERT INTO fichas (usuario, fechaCompra, cantComprada) VALUES ('";
	sql += usuario + "', '";
	sql += fechaActual + "',";
	sql += UtilTiposDatos::enteroAString(cantFichasCompradas) + ");";

	return this->ejecutarNonQuery(sql);	
}

bool AccesoDatos::consultarCantFichasCompradasHoy(string usuario)
{
	string fechaActual = this->getFechaActual();	
	string sql = "SELECT SUM(cantComprada) FROM fichas WHERE usuario = '" + usuario + "' AND fechaCompra = '" + fechaActual + "';";
	return this->ejecutar(sql);
}


string AccesoDatos::obtenerEvolucionUsuariosRegistrados(string dia, string mes, string anio)
{
	string listado = "";
	
	if (dia.length() == 1)
		dia = "0" + dia;

	if (mes.length() == 1)
		mes = "0" + mes;

	// En el primer caso al existir todos los datos --> se desglosa por horas del dia ingresado
	if ((!MensajesUtil::sonIguales(dia, ""))&&(!MensajesUtil::sonIguales(mes, ""))&&(!MensajesUtil::sonIguales(anio, "")))
	{
		listado = obtenerEvolUsrRegPorHoras(dia, mes, anio);	
	}
	// En el segundo caso al existir mes y anio --> se desglosa por dias del mes ingresado
	else if ((MensajesUtil::sonIguales(dia, ""))&&(!MensajesUtil::sonIguales(mes, ""))&&(!MensajesUtil::sonIguales(anio, "")))
	{
		listado = obtenerEvolUsrRegPorDias(mes, anio);	
	}
	// En el tercer caso al existir solo anio --> se desglosa por meses del anio ingresado
	else if ((MensajesUtil::sonIguales(dia, ""))&&(MensajesUtil::sonIguales(mes, ""))&&(!MensajesUtil::sonIguales(anio, "")))
	{
		listado = obtenerEvolUsrRegPorMeses(anio);	
	}
	
	return listado;
}

string AccesoDatos::obtenerEvolUsrRegPorHoras(string dia, string mes, string anio)
{
	string listado = "";
	string sql = "";
	string diaMesAnio = dia + "/" + mes + "/" + anio;
	string strHora = "";
	int cantRegistrados = 0;
	
	listado = listado + "Hora:" + '\t'+ '\t';
	listado = listado + "Cantidad Usuarios Registrados:" + '\n';
	listado = listado + "-------" + '\t';
	listado = listado + "-----------------------------" + '\n';

	for (int hora = 0; hora <= HORA_MAX; hora++) 
	{
		strHora = MensajesUtil::intToString(hora);
		
		if (strHora.length() == 1)
			strHora = "0" + strHora;

		sql = "SELECT COUNT(*) FROM jugadores WHERE substr(horaregistro,0,3) = '" + strHora + "' AND fechaRegistro = '" + diaMesAnio + "';";
 
		if (this->ejecutar(sql))
		{
			while (sqlite3_step(resultado)==SQLITE_ROW)
			{	
				cantRegistrados = sqlite3_column_int(resultado, 0);	

				listado = listado + MensajesUtil::intToString(hora) + '\t' + '\t' + '\t';
				listado = listado + MensajesUtil::intToString(cantRegistrados) + '\n';
			}
		}
	}

	return listado;
}

string AccesoDatos::obtenerEvolUsrRegPorDias(string mes, string anio)
{
	string listado = "";
	string sql = "";
	string strDia = "";
	string mesAnio = mes + "/" + anio;
	string fecha = "";
	int diaMax = this->getCantDiasDelMes(UtilTiposDatos::stringAEntero(mes), UtilTiposDatos::stringAEntero(anio));
	int cantRegistrados = 0;
		
	listado = listado + "Dia:" + '\t'+ '\t';
	listado = listado + "Cantidad Usuarios Registrados:" + '\n';
	listado = listado + "-------" + '\t';
	listado = listado + "------------------------------" + '\n';

	for (int dia = 1; dia <= diaMax; dia++) 
	{
		strDia = MensajesUtil::intToString(dia);
		
		if (strDia.length() == 1)
			strDia = "0" + strDia;

		fecha = strDia + "/" + mesAnio;

		sql = "SELECT COUNT(*) FROM jugadores WHERE fechaRegistro = '" + fecha + "';";
 
		if (this->ejecutar(sql))
		{
			while (sqlite3_step(resultado)==SQLITE_ROW)
			{	
				cantRegistrados = sqlite3_column_int(resultado, 0);	

				listado = listado + MensajesUtil::intToString(dia) + '\t' + '\t' + '\t';
				listado = listado + MensajesUtil::intToString(cantRegistrados) + '\n';
			}
		}
	}

	return listado;
}

string AccesoDatos::obtenerEvolUsrRegPorMeses(string anio)
{
	string listado = "";
	string sql = "";
	string strMes = "";
	string fecha = "";
	int cantRegistrados = 0;
		
	listado = listado + "Mes:" + '\t'+ '\t';
	listado = listado + "Cantidad Usuarios Registrados" + '\n';
	listado = listado + "-------" + '\t';
	listado = listado + "-----------------------------" + '\n';

	for (int mes = 1; mes <= MES_MAX; mes++) 
	{
		strMes = MensajesUtil::intToString(mes);
		
		if (strMes.length() == 1)
			strMes = "0" + strMes;

		fecha = strMes + "/" + anio;

		sql = "SELECT COUNT(*) FROM jugadores WHERE substr(fechaRegistro, 4, 7) = '" + fecha + "';"; 
 
		if (this->ejecutar(sql))
		{
			while (sqlite3_step(resultado)==SQLITE_ROW)
			{	
				cantRegistrados = sqlite3_column_int(resultado, 0);	

				listado = listado + MensajesUtil::intToString(mes) + '\t' + '\t' + '\t';
				listado = listado + MensajesUtil::intToString(cantRegistrados) + '\n';
			}
		}
	}

	return listado;
}

string AccesoDatos::obtenerEvolucionUsuariosConectados(string dia, string mes, string anio)
{
	string listado = "";
	
	if (dia.length() == 1)
		dia = "0" + dia;

	if (mes.length() == 1)
		mes = "0" + mes;

	// En el primer caso al existir todos los datos --> se desglosa por horas del dia ingresado
	if ((!MensajesUtil::sonIguales(dia, ""))&&(!MensajesUtil::sonIguales(mes, ""))&&(!MensajesUtil::sonIguales(anio, "")))
	{
		listado = obtenerEvolUsrConPorHoras(dia, mes, anio);	
	}
	// En el segundo caso al existir mes y anio --> se desglosa por dias del mes ingresado
	else if ((MensajesUtil::sonIguales(dia, ""))&&(!MensajesUtil::sonIguales(mes, ""))&&(!MensajesUtil::sonIguales(anio, "")))
	{
		listado = obtenerEvolUsrConPorDias(mes, anio);	
	}
	// En el tercer caso al existir solo anio --> se desglosa por meses del anio ingresado
	else if ((MensajesUtil::sonIguales(dia, ""))&&(MensajesUtil::sonIguales(mes, ""))&&(!MensajesUtil::sonIguales(anio, "")))
	{
		listado = obtenerEvolUsrConPorMeses(anio);	
	}
	
	return listado;
}

string AccesoDatos::obtenerEvolUsrConPorHoras(string dia, string mes, string anio)
{
	string listado = "";
	string sql = "";
	string diaMesAnio = dia + "/" + mes + "/" + anio;
	string strHora = "";
	int cantConectados = 0;
	
	listado = listado + "Hora:" + '\t'+ '\t';
	listado = listado + "Cantidad Usuarios Conectados:" + '\n';
	listado = listado + "-------" + '\t';
	listado = listado + "-----------------------------" + '\n';

	for (int hora = 0; hora <= HORA_MAX; hora++) 
	{
		strHora = MensajesUtil::intToString(hora);
		
		if (strHora.length() == 1)
			strHora = "0" + strHora;

		sql = "SELECT COUNT(DISTINCT(USUARIO)) FROM sesion WHERE substr(horaInicio,0,3) = '" + strHora + "' AND fechaInicio = '" + diaMesAnio + "';";
 
		if (this->ejecutar(sql))
		{
			while (sqlite3_step(resultado)==SQLITE_ROW)
			{	
				cantConectados = sqlite3_column_int(resultado, 0);	

				listado = listado + MensajesUtil::intToString(hora) + '\t' + '\t' + '\t';
				listado = listado + MensajesUtil::intToString(cantConectados) + '\n';
			}
		}
	}

	return listado;
}

string AccesoDatos::obtenerEvolUsrConPorDias(string mes, string anio)
{
	string listado = "";
	string sql = "";
	string strDia = "";
	string mesAnio = mes + "/" + anio;
	string fecha = "";
	int diaMax = this->getCantDiasDelMes(UtilTiposDatos::stringAEntero(mes), UtilTiposDatos::stringAEntero(anio));
	int cantConectados = 0;
		
	listado = listado + "Dia:" + '\t'+ '\t';
	listado = listado + "Cantidad Usuarios Conectados:" + '\n';
	listado = listado + "-------" + '\t';
	listado = listado + "------------------------------" + '\n';

	for (int dia = 1; dia <= diaMax; dia++) 
	{
		strDia = MensajesUtil::intToString(dia);
		
		if (strDia.length() == 1)
			strDia = "0" + strDia;

		fecha = strDia + "/" + mesAnio;

		sql = "SELECT COUNT(DISTINCT(usuario)) FROM sesion WHERE fechaInicio = '" + fecha + "';";
 
		if (this->ejecutar(sql))
		{
			while (sqlite3_step(resultado)==SQLITE_ROW)
			{	
				cantConectados = sqlite3_column_int(resultado, 0);	

				listado = listado + MensajesUtil::intToString(dia) + '\t' + '\t' + '\t';
				listado = listado + MensajesUtil::intToString(cantConectados) + '\n';
			}
		}
	}

	return listado;	
}

string AccesoDatos::obtenerEvolUsrConPorMeses(string anio)
{
	string listado = "";
	string sql = "";
	string strMes = "";
	string fecha = "";
	int cantConectados = 0;
		
	listado = listado + "Mes:" + '\t'+ '\t';
	listado = listado + "Cantidad Usuarios Conectados" + '\n';
	listado = listado + "-------" + '\t';
	listado = listado + "-----------------------------" + '\n';

	for (int mes = 1; mes <= MES_MAX; mes++) 
	{
		strMes = MensajesUtil::intToString(mes);
		
		if (strMes.length() == 1)
			strMes = "0" + strMes;

		fecha = strMes + "/" + anio;

		sql = "SELECT COUNT(DISTINCT(usuario)) FROM sesion WHERE substr(fechaInicio, 4, 7) = '" + fecha + "';"; 
 
		if (this->ejecutar(sql))
		{
			while (sqlite3_step(resultado)==SQLITE_ROW)
			{	
				cantConectados = sqlite3_column_int(resultado, 0);	

				listado = listado + MensajesUtil::intToString(mes) + '\t' + '\t' + '\t';
				listado = listado + MensajesUtil::intToString(cantConectados) + '\n';
			}
		}
	}

	return listado;
}

string AccesoDatos::obtenerListadoUsuariosRegistrados(string dia, string mes, string anio)
{
	string listado = "";
	
	if (dia.length() == 1)
		dia = "0" + dia;

	if (mes.length() == 1)
		mes = "0" + mes;

	// En el primer caso al existir todos los datos --> se desglosa por horas del dia ingresado
	if ((!MensajesUtil::sonIguales(dia, ""))&&(!MensajesUtil::sonIguales(mes, ""))&&(!MensajesUtil::sonIguales(anio, "")))
	{
		listado = obtenerListUsrRegPorHoras(dia, mes, anio);	
	}
	// En el segundo caso al existir mes y anio --> se desglosa por dias del mes ingresado
	else if ((MensajesUtil::sonIguales(dia, ""))&&(!MensajesUtil::sonIguales(mes, ""))&&(!MensajesUtil::sonIguales(anio, "")))
	{
		listado = obtenerListUsrRegPorDias(mes, anio);	
	}
	// En el tercer caso al existir solo anio --> se desglosa por meses del anio ingresado
	else if ((MensajesUtil::sonIguales(dia, ""))&&(MensajesUtil::sonIguales(mes, ""))&&(!MensajesUtil::sonIguales(anio, "")))
	{
		listado = obtenerListUsrRegPorMeses(anio);	
	}
	
	return listado;
}

string AccesoDatos::obtenerListUsrRegPorHoras(string dia, string mes, string anio)
{
	string listado = "";
	string sql = "";
	string diaMesAnio = dia + "/" + mes + "/" + anio;
	string strHora = "";
	string usuario = "";
	bool hayUsuarios;
	bool imprimioHora;
	
	listado = listado + "Hora:" + '\t'+ '\t';
	listado = listado + "Usuarios Registrados" + '\n';
	listado = listado + "-------" + '\t';
	listado = listado + "--------------------" + '\n';

	for (int hora = 0; hora <= HORA_MAX; hora++) 
	{
		strHora = MensajesUtil::intToString(hora);
		
		if (strHora.length() == 1)
			strHora = "0" + strHora;

		sql = "SELECT distinct(usuario) FROM sesion WHERE substr(horaregistro,0,3) = '" + strHora + "' AND fechaRegistro = '" + diaMesAnio + "';";
 
		if (this->ejecutar(sql))
		{
			imprimioHora = false;
			hayUsuarios = false;
			
			while (sqlite3_step(resultado)==SQLITE_ROW)
			{	
				usuario = string(reinterpret_cast<const char*>(sqlite3_column_text(resultado, 0)));

				if (!imprimioHora)
				{
					listado = listado + MensajesUtil::intToString(hora) + '\t' + '\t' + '\t';
					imprimioHora = true;
				}
				else
					listado = listado +  '\t' + '\t' + '\t';
				
				listado = listado + usuario + '\n';
				
				hayUsuarios = true;
			}

			if (!hayUsuarios)
			{
				listado = listado + MensajesUtil::intToString(hora) + '\t' + '\t' + '\t';
				usuario = "-";
				listado = listado + usuario + '\n';
			}
		}
	}

	return listado;
}

string AccesoDatos::obtenerListUsrRegPorDias(string mes, string anio)
{
	string listado = "";
	string sql = "";
	string strDia = "";
	string mesAnio = mes + "/" + anio;
	string fecha = "";
	int diaMax = this->getCantDiasDelMes(UtilTiposDatos::stringAEntero(mes), UtilTiposDatos::stringAEntero(anio));
	string usuario = "";
	bool hayUsuarios;
	bool imprimioDia;
		
	listado = listado + "Dia:" + '\t'+ '\t';
	listado = listado + "Usuarios Registrados" + '\n';
	listado = listado + "-------" + '\t';
	listado = listado + "--------------------" + '\n';

	for (int dia = 1; dia <= diaMax; dia++) 
	{
		strDia = MensajesUtil::intToString(dia);
		
		if (strDia.length() == 1)
			strDia = "0" + strDia;

		fecha = strDia + "/" + mesAnio;

		sql = "SELECT usuario FROM jugadores WHERE fechaRegistro = '" + fecha + "';";
 
		if (this->ejecutar(sql))
		{
			imprimioDia = false;
			hayUsuarios = false;
			
			while (sqlite3_step(resultado)==SQLITE_ROW)
			{	
				usuario = string(reinterpret_cast<const char*>(sqlite3_column_text(resultado, 0)));

				if (!imprimioDia)
				{
					listado = listado + MensajesUtil::intToString(dia) + '\t' + '\t' + '\t';
					imprimioDia = true;
				}
				else
					listado = listado +  '\t' + '\t' + '\t';
				
				listado = listado + usuario + '\n';
				
				hayUsuarios = true;
			}

			if (!hayUsuarios)
			{
				listado = listado + MensajesUtil::intToString(dia) + '\t' + '\t' + '\t';
				usuario = "-";
				listado = listado + usuario + '\n';
			}
		}
	}

	return listado;
}

string AccesoDatos::obtenerListUsrRegPorMeses(string anio)
{
	string listado = "";
	string sql = "";
	string strMes = "";
	string fecha = "";
	string usuario = "";
	bool hayUsuarios;
	bool imprimioMes;
		
	listado = listado + "Mes:" + '\t'+ '\t';
	listado = listado + "Usuarios Registrados" + '\n';
	listado = listado + "-------" + '\t';
	listado = listado + "--------------------" + '\n';

	for (int mes = 1; mes <= MES_MAX; mes++) 
	{
		strMes = MensajesUtil::intToString(mes);
		
		if (strMes.length() == 1)
			strMes = "0" + strMes;

		fecha = strMes + "/" + anio;

		sql = "SELECT usuario FROM jugadores WHERE substr(fechaRegistro, 4, 7) = '" + fecha + "';"; 
 
		if (this->ejecutar(sql))
		{
			imprimioMes = false;
			hayUsuarios = false;
			
			while (sqlite3_step(resultado)==SQLITE_ROW)
			{	
				usuario = string(reinterpret_cast<const char*>(sqlite3_column_text(resultado, 0)));

				if (!imprimioMes)
				{
					listado = listado + MensajesUtil::intToString(mes) + '\t' + '\t' + '\t';
					imprimioMes = true;
				}
				else
					listado = listado +  '\t' + '\t' + '\t';
				
				listado = listado + usuario + '\n';
				
				hayUsuarios = true;
			}

			if (!hayUsuarios)
			{
				listado = listado + MensajesUtil::intToString(mes) + '\t' + '\t' + '\t';
				usuario = "-";
				listado = listado + usuario + '\n';
			}
		}
	}

	return listado;
}

string AccesoDatos::obtenerListadoUsuariosConectados(string dia, string mes, string anio)
{
	string listado = "";
	
	if (dia.length() == 1)
		dia = "0" + dia;

	if (mes.length() == 1)
		mes = "0" + mes;

	// En el primer caso al existir todos los datos --> se desglosa por horas del dia ingresado
	if ((!MensajesUtil::sonIguales(dia, ""))&&(!MensajesUtil::sonIguales(mes, ""))&&(!MensajesUtil::sonIguales(anio, "")))
	{
		listado = obtenerListUsrConPorHoras(dia, mes, anio);	
	}
	// En el segundo caso al existir mes y anio --> se desglosa por dias del mes ingresado
	else if ((MensajesUtil::sonIguales(dia, ""))&&(!MensajesUtil::sonIguales(mes, ""))&&(!MensajesUtil::sonIguales(anio, "")))
	{
		listado = obtenerListUsrConPorDias(mes, anio);	
	}
	// En el tercer caso al existir solo anio --> se desglosa por meses del anio ingresado
	else if ((MensajesUtil::sonIguales(dia, ""))&&(MensajesUtil::sonIguales(mes, ""))&&(!MensajesUtil::sonIguales(anio, "")))
	{
		listado = obtenerListUsrConPorMeses(anio);	
	}
	
	return listado;
}

string AccesoDatos::obtenerListUsrConPorHoras(string dia, string mes, string anio)
{
	string listado = "";
	string sql = "";
	string diaMesAnio = dia + "/" + mes + "/" + anio;
	string strHora = "";
	string usuario = "";
	bool hayUsuarios;
	bool imprimioHora;
	
	listado = listado + "Hora:" + '\t'+ '\t';
	listado = listado + "Usuarios Conectados:" + '\n';
	listado = listado + "-------" + '\t';
	listado = listado + "--------------------" + '\n';

	for (int hora = 0; hora <= HORA_MAX; hora++) 
	{
		strHora = MensajesUtil::intToString(hora);
		
		if (strHora.length() == 1)
			strHora = "0" + strHora;

		sql = "SELECT distinct(usuario) FROM sesion WHERE substr(horaInicio,0,3) = '" + strHora + "' AND fechaInicio = '" + diaMesAnio + "';";
 
		if (this->ejecutar(sql))
		{
			imprimioHora = false;
			hayUsuarios = false;
			
			while (sqlite3_step(resultado)==SQLITE_ROW)
			{	
				usuario = string(reinterpret_cast<const char*>(sqlite3_column_text(resultado, 0)));

				if (!imprimioHora)
				{
					listado = listado + MensajesUtil::intToString(hora) + '\t' + '\t' + '\t';
					imprimioHora = true;
				}
				else
					listado = listado +  '\t' + '\t' + '\t';
				
				listado = listado + usuario + '\n';
				
				hayUsuarios = true;
			}

			if (!hayUsuarios)
			{
				listado = listado + MensajesUtil::intToString(hora) + '\t' + '\t' + '\t';
				usuario = "-";
				listado = listado + usuario + '\n';
			}
		}
	}

	return listado;
}

string AccesoDatos::obtenerListUsrConPorDias(string mes, string anio)
{
	string listado = "";
	string sql = "";
	string strDia = "";
	string mesAnio = mes + "/" + anio;
	string fecha = "";
	int diaMax = this->getCantDiasDelMes(UtilTiposDatos::stringAEntero(mes), UtilTiposDatos::stringAEntero(anio));
	string usuario = "";
	bool hayUsuarios;
	bool imprimioDia;
		
	listado = listado + "Dia:" + '\t'+ '\t';
	listado = listado + "Usuarios Conectados" + '\n';
	listado = listado + "-------" + '\t';
	listado = listado + "--------------------" + '\n';

	for (int dia = 1; dia <= diaMax; dia++) 
	{
		strDia = MensajesUtil::intToString(dia);
		
		if (strDia.length() == 1)
			strDia = "0" + strDia;

		fecha = strDia + "/" + mesAnio;

		sql = "SELECT distinct(usuario) FROM sesion WHERE fechaInicio = '" + fecha + "';";
 
		if (this->ejecutar(sql))
		{
			imprimioDia = false;
			hayUsuarios = false;
			
			while (sqlite3_step(resultado)==SQLITE_ROW)
			{	
				usuario = string(reinterpret_cast<const char*>(sqlite3_column_text(resultado, 0)));

				if (!imprimioDia)
				{
					listado = listado + MensajesUtil::intToString(dia) + '\t' + '\t' + '\t';
					imprimioDia = true;
				}
				else
					listado = listado +  '\t' + '\t' + '\t';
				
				listado = listado + usuario + '\n';
				
				hayUsuarios = true;
			}

			if (!hayUsuarios)
			{
				listado = listado + MensajesUtil::intToString(dia) + '\t' + '\t' + '\t';
				usuario = "-";
				listado = listado + usuario + '\n';
			}
		}
	}

	return listado;
}

string AccesoDatos::obtenerListUsrConPorMeses(string anio)
{
	string listado = "";
	string sql = "";
	string strMes = "";
	string fecha = "";
	string usuario = "";
	bool hayUsuarios;
	bool imprimioMes;
		
	listado = listado + "Mes:" + '\t'+ '\t';
	listado = listado + "Usuarios Conectados:" + '\n';
	listado = listado + "-------" + '\t';
	listado = listado + "--------------------" + '\n';

	for (int mes = 1; mes <= MES_MAX; mes++) 
	{
		strMes = MensajesUtil::intToString(mes);
		
		if (strMes.length() == 1)
			strMes = "0" + strMes;

		fecha = strMes + "/" + anio;

		sql = "SELECT distinct(usuario) FROM sesion WHERE substr(fechaInicio, 4, 7) = '" + fecha + "';"; 
 
		if (this->ejecutar(sql))
		{
			imprimioMes = false;
			hayUsuarios = false;
			
			while (sqlite3_step(resultado)==SQLITE_ROW)
			{	
				usuario = string(reinterpret_cast<const char*>(sqlite3_column_text(resultado, 0)));

				if (!imprimioMes)
				{
					listado = listado + MensajesUtil::intToString(mes) + '\t' + '\t' + '\t';
					imprimioMes = true;
				}
				else
					listado = listado +  '\t' + '\t' + '\t';
				
				listado = listado + usuario + '\n';
				
				hayUsuarios = true;
			}

			if (!hayUsuarios)
			{
				listado = listado + MensajesUtil::intToString(mes) + '\t' + '\t' + '\t';
				usuario = "-";
				listado = listado + usuario + '\n';
			}
		}
	}

	return listado;
}

string AccesoDatos::obtenerRankingUsuarios()
{
	string listado = "";
	string usuario  = "";
	int cantFichas = 0;
		
	listado = listado + "Usuario" + '\t'+ '\t';
	listado = listado + "Fichas" + '\n';
	listado = listado + "-------" + '\t' + '\t';
	listado = listado + "-------" + '\n';

	if (this->consultarRankingUsuarios())
	{
		while (sqlite3_step(resultado)==SQLITE_ROW)
		{
			usuario = string(reinterpret_cast<const char*>(sqlite3_column_text(resultado, 0)));
			cantFichas = sqlite3_column_int(resultado, 1);
			
			listado = listado + usuario + '\t' + '\t';
			listado = listado + MensajesUtil::intToString(cantFichas) + '\n';
		}
	}

	//cout << listado;

	return listado;
}

bool AccesoDatos::consultarRankingUsuarios()
{
	string sql = "SELECT usuario, cantFichas FROM jugadores order by cantFichas desc;";
	return this->ejecutar(sql);
}
