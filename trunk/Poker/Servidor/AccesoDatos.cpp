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

	string fecha = anio + "/" + mes + "/" + dia;
	
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
		sql += "idJugador integer, ";
		sql += "fechaInicio varchar(10), ";
		sql += "horaInicio varchar(8), ";
		sql += "fechaFin varchar(10), ";
		sql += "horaFin varchar(8), ";
		sql += "observador varchar(1), ";
		sql += "virtual varchar(1));";
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

	if (!this->existeTabla("jugadores"))
		this->crearTabla("jugadores");

	if (!this->existeTabla("sesion"))
		this->crearTabla("sesion");
}

bool AccesoDatos::agregarJugador(string usuario, string password, string nombre, string apellido, string nombreImagen)
{
	bool resul = false;

	if (!this->obtenerJugador(usuario))
	{
		resul = this->grabarJugador(usuario, password, nombre, apellido, nombreImagen);
	}
	else
		this->msgError = "No se pudo grabar el Jugador. Ya existe un jugador con ese nombre.";

	return resul;
}

bool AccesoDatos::grabarJugador(string usuario, string password, string nombre, string apellido, string nombreImagen)
{
	string fechaActual = this->getFechaActual();

	string sql = "INSERT INTO jugadores (usuario, password, nombre, apellido, nombreImagen, cantFichas, fechaRegistro, fechaUltCompraFichas) VALUES ('";
	sql += usuario + "', '";
	sql += password + "', '";
	sql += nombre + "', '";
	sql += apellido + "', '";
	sql += nombreImagen + "', ";
	sql += "2000, '";				// se crea cada jugador con 2.000 fichas
	sql += fechaActual +  "', ";
	sql += "'2000/01/01');";		// se crea cada jugador con una fecha inicial 
	
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

bool AccesoDatos::validarCompraFichas(int idJugador)
{
	bool resul = false;
	string fechaUltCompraFichas;
	string fechaActual = this->getFechaActual();

	if (this->consultarJugadorById(idJugador))
	{
		while (sqlite3_step(resultado)==SQLITE_ROW)
		{
			fechaUltCompraFichas = string(reinterpret_cast<const char*>(sqlite3_column_text(resultado, 7)));
			
			if (fechaUltCompraFichas < fechaActual)
				resul = true;
		}		
	}

	return resul;
}

bool AccesoDatos::grabarCompraFichas(int idJugador, int cantFichasCompradas)
{
	string fechaActual = this->getFechaActual();
	int cantFichasActual;
	string sql;
	bool resul = false;

	if (this->consultarJugadorById(idJugador))
	{
		while (sqlite3_step(resultado)==SQLITE_ROW)
		{
			cantFichasActual = sqlite3_column_int(resultado, 6);
			cantFichasActual = cantFichasActual + cantFichasCompradas;
			
			sql = "UPDATE jugadores SET cantFichas = " + UtilTiposDatos::enteroAString(cantFichasActual) + " , ";
			sql +="fechaUltCompraFichas = '" + fechaActual + "' ";
			sql +="WHERE id = " + UtilTiposDatos::enteroAString(idJugador) +  ";";
	
			resul = this->ejecutarNonQuery(sql);
		}		
	}

	return resul;
}
bool AccesoDatos::actualizarNombreImagen(int idJugador, string nuevoNombreImagen)
{
	string sql = "UPDATE jugadores SET nombreImagen = '" + nuevoNombreImagen + "' WHERE id = " + UtilTiposDatos::enteroAString(idJugador) +  ";";
	return this->ejecutarNonQuery(sql);
}

bool AccesoDatos::actualizarCantFichas(int idJugador, int cantFichas)
{
	string sql = "UPDATE jugadores SET cantFichas = " + UtilTiposDatos::enteroAString(cantFichas) + " WHERE id = " + UtilTiposDatos::enteroAString(idJugador) +  ";";
	return this->ejecutarNonQuery(sql);
}

int AccesoDatos::grabarInicioSesion(int idJugador, bool esObservador, bool esVirtual, string nombreImagen)
{
	int resul = -1;
	string obs = "N";
	string virt = "N";
	string fechaInicio = this->getFechaActual();
	string horaInicio = this->getHoraActual();

	if (esObservador)
		obs = "S";

	if (esVirtual)
		virt = "S";

	string sql = "INSERT INTO sesion (idJugador, fechaInicio, horaInicio, fechaFin, horaFin, observador, virtual) VALUES (";
	sql += UtilTiposDatos::enteroAString(idJugador) + ", '";
	sql += fechaInicio + "', '";
	sql += horaInicio + "', '";
	sql += "', '', '";
	sql += obs + "', '";
	sql += virt + "');";

	if (this->ejecutarNonQuery(sql))
	{
		string sql = "SELECT MAX(id) FROM sesion WHERE idJugador = " + UtilTiposDatos::enteroAString(idJugador);
	
		if (this->ejecutar(sql))
		{
			while (sqlite3_step(resultado)==SQLITE_ROW)
			{	
				resul = sqlite3_column_int(resultado, 0);				
			}
		}
	}
	
	return resul;
}

bool AccesoDatos::grabarFinSesion(int idSesion)
{
	string fechaFin = this->getFechaActual();
	string horaFin = this->getHoraActual();

	string sql = "UPDATE sesion SET fechaFin = '" + fechaFin + "', horaFin = '" + horaFin + "' WHERE id = " + UtilTiposDatos::enteroAString(idSesion);
	
	return this->ejecutarNonQuery(sql);
}