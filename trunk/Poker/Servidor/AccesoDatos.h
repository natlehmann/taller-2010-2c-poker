#pragma once
#include <string>
#include <time.h>
#include "sqlite3.h"
#include "UtilTiposDatos.h"
#include "JugadorModelo.h"
#include "MensajesUtil.h"

#define _CRT_SECURE_NO_DEPRECATE 1
#define MES_MAX 12
#define HORA_MAX 23

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
				
		/* Metodos y funciones generales a las tablas de la BD */
		bool crearTabla(string nombreTabla);
		bool eliminarTabla(string nombreTabla);
		bool borrarDatosTabla(string nombreTabla);
		bool existeTabla(string nombreTabla);

		/* Metodos y funciones aplicados a la tabla "JUGADORES" */
		bool consultarJugador(string usuario);
		bool consultarJugadorById(int idJugador);
		bool consultarCantFichas(string usuario);
		bool registrarNuevoJugador(string usuario, string password, string nombre, string apellido);
		bool actualizarCantFichas(string usuario, int cantFichas);
		
		/* Metodos y funciones aplicados a la tabla "SESION" */		
		bool cerrarSesionesAnteriores(string usuario);

		/* Metodos y funciones aplicados a la tabla "FICHAS" */
		bool consultarCantFichasCompradasHoy(string usuario);
		bool registrarCompraFichas(string usuario, int cantFichasCompradas);

		/* Metodos y funciones aplicados a la obtencion de datos estadisticos */
		/*	EVOLUCION DE USUARIOS REGISTRADOS */
		string obtenerEvolUsrRegPorHoras(string dia, string mes, string anio);	
		string obtenerEvolUsrRegPorDias(string mes, string anio);
		string obtenerEvolUsrRegPorMeses(string anio);
		/*	EVOLUCION DE USUARIOS CONECTADOS */
		string obtenerEvolUsrConPorHoras(string dia, string mes, string anio);
		string obtenerEvolUsrConPorDias(string mes, string anio);
		string obtenerEvolUsrConPorMeses(string anio);
		/*	LISTADO DE USUARIOS REGISTRADOS */
		string obtenerListUsrRegPorHoras(string dia, string mes, string anio);
		string obtenerListUsrRegPorDias(string mes, string anio);
		string obtenerListUsrRegPorMeses(string anio);
		/*	LISTADO DE USUARIOS CONECTADOS */
		string obtenerListUsrConPorHoras(string dia, string mes, string anio);
		string obtenerListUsrConPorDias(string mes, string anio);
		string obtenerListUsrConPorMeses(string anio);
		/*	LISTADO DEL RANKING DE USUARIOS */
		bool consultarRankingUsuarios();

		string getFechaActual();
		string getHoraActual();
		int getCantDiasDelMes(int dia, int anio);

	public:
		
		AccesoDatos(void);
		virtual ~AccesoDatos(void);

		string getMensajeError();
		
		// Metodo que valida la existencia de las tablas del sistema.
		void inicializarBaseDatos();
		
		/************************** Metodos y funciones aplicados a la tabla "JUGADORES" **************************/
		// Obtiene un jugador segun el usuario. En caso de no existir, devuelve NULL
		JugadorModelo* obtenerJugador(string usuario);
		// Graba en la tabla un jugador nuevo
		bool grabarNuevoJugador(string usuario, string password, string nombre, string apellido);
		// Valida que la cantidad de fichas del jugador sea <= 100
		bool validarCantFichasJugador(string usuario);
		// Valida que la cantidad compradas en el dia actual no supere las 2000
		bool validarCantFichasCompradasHoy(string usuario, int cantFichasAComprar);
		// Actualiza la cantidad de fichas del jugador y registra la compra 
		bool grabarCompraFichas(string usuario, int cantFichasAComprar);
		// Actualizacion de datos de los jugadores
		bool actualizarNombreImagen(string usuario, string nuevoNombreImagen);
		bool actualizarFichas(string usuario, int fichas);
		/*********************************************************************************************************/

		/************************** Metodos y funciones aplicadas a la tabla "SESION" *****************************/
		// Graba el inicio de sesion devolviendo el idSesion 
		int grabarInicioSesion(string usuario, string esObservador, string esVirtual);
		bool grabarFinSesion(int idSesion);
		/*********************************************************************************************************/

		/************************** Metodos y funciones para obtener datos ESTADISTICOS *****************************/
		string obtenerEvolucionUsuariosRegistrados(string dia, string mes, string anio);
		string obtenerEvolucionUsuariosConectados(string dia, string mes, string anio);
		string obtenerListadoUsuariosRegistrados(string dia, string mes, string anio);
		string obtenerListadoUsuariosConectados(string dia, string mes, string anio);
		string obtenerRankingUsuarios();
		/************************************************************************************************************/

};