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
		sql += "fechaUltCompraFichas varchar(10));";
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

	string sql = "INSERT INTO jugadores (usuario, password, nombre, apellido, nombreImagen, cantFichas, fechaRegistro) VALUES ('";
	sql += usuario + "', '";
	sql += password + "', '";
	sql += nombre + "', '";
	sql += apellido + "',";
	sql += "'', ";
	sql += "2000, '";				// se crea cada jugador con 2.000 fichas
	sql += fechaActual +  "');";

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

