#pragma once
#include <string>
#include <time.h>
#include "sqlite3.h"
#include "UtilTiposDatos.h"
#include "JugadorModelo.h"
#include "MensajesUtil.h"


#define _CRT_SECURE_NO_DEPRECATE 1

using namespace std;

class AccesoDatos
{
	private:
		
		// Variable del tipo de bases de datos.
		sqlite3 *db;
		// Variable con el resultado de una consulta.
		sqlite3_stmt *resultado;
		// Variable con el mensaje de error al ejecutar consulta.
		string msgError;

		bool conectar();
		bool desconectar();
		bool ejecutarNonQuery(string sql);
		bool ejecutar(string sql);
		//string getFechaActual();
		
		/* Metodos y funciones generales a las tablas de la BD */
		bool crearTabla(string nombreTabla);
		bool eliminarTabla(string nombreTabla);
		bool borrarDatosTabla(string nombreTabla);
		bool existeTabla(string nombreTabla);

		/* Metodos y funciones aplicados a la tabla "JUGADORES" */
		bool consultarJugador(string usuario);
		bool consultarJugadorById(int idJugador);
		bool grabarJugador(string usuario, string password, string nombre, string apellido, string nombreImagen);

		string getFechaActual();
		string getHoraActual();

	public:
		
		AccesoDatos(void);
		virtual ~AccesoDatos(void);

		string getMensajeError();
		
		// Metodo que valida la existencia de las tablas del sistema.
		void inicializarBaseDatos();
		
		/************************** Metodos y funciones aplicados a la tabla "JUGADORES" **************************/
		// Graba en la tabla un jugador nuevo
		bool agregarJugador(string nickName, string password, string nombre, string apellido, string nombreImagen);
		// Obtiene un jugador segun el nickName. En caso de no existir, devuelve NULL
		JugadorModelo* obtenerJugador(string usuario);
		// Validacion de la fecha de ultima compra respecto de la fecha actual
		bool validarCompraFichas(int idJugador);
		// Graba la compra de las fichas y actualiza la fecha de ultima compra
		bool grabarCompraFichas(int idJugador, int cantiFichasCompradas);
		// Actualizacion de datos de los jugadores
		bool actualizarNombreImagen(int idJugador, string nuevoNombreImagen);
		bool actualizarCantFichas(int idJugador, int cantFichas);
		/*********************************************************************************************************/

		/************************** Metodos y funciones aplicadas a la tabla "SESION" **************************/
		// Graba el inicio de sesion devolviendo el idSesion 
		int grabarInicioSesion(int idJugador, bool esObservador, bool esVirtual, string nombreImagen);
		bool grabarFinSesion(int idSesion);
		/*********************************************************************************************************/
		
};