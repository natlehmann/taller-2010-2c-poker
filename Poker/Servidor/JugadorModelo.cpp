#include "JugadorModelo.h"
#include "PokerException.h"
#include "ContextoJuego.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>


JugadorModelo::JugadorModelo(int id, int posicion)
{
	this->id = id;
	this->posicion = posicion;
	this->carta1 = NULL;
	this->carta2 = NULL;
	this->nombre = "";
	this->apuesta = 0;
	this->fichas = 0;
	this->activo = false;
	this->jugandoRonda = false;
	this->ausente = true;
	this->dealer = false;

	srand ((unsigned int)(time(NULL)));

	this->apuestaPatron = APUESTA_PATRON;
	this->nivelDeConfianza = CONFIANZA;
}

JugadorModelo::JugadorModelo(int id, string nombre, int fichas, int posicion, string password, string nombreImagen)
{
	this->id = id;
	this->nombre = nombre;
	this->fichas = fichas;
	this->posicion = posicion;
	this->password = password;
	this->nombreImagen = nombreImagen;
	this->carta1 = NULL;
	this->carta2 = NULL;
	this->apuesta = 0;
	this->activo = false;
	this->jugandoRonda = false;
	this->ausente = false;

	srand ((unsigned int)(time(NULL)));

	this->apuestaPatron = APUESTA_PATRON;
	this->nivelDeConfianza = CONFIANZA;
}

JugadorModelo::~JugadorModelo(void)
{
}

int JugadorModelo::getId()
{
	return this->id;
}

void JugadorModelo::setId(int id)
{
	this->id = id;
}

string JugadorModelo::getNombre()
{
	return this->nombre;
}

void JugadorModelo::setNombre(string nombre)
{
	this->nombre = nombre;
}

int JugadorModelo::getFichas()
{
	return this->fichas;
}

void JugadorModelo::setFichas(int fichas)
{
	this->fichas = fichas;
}

int JugadorModelo::getPosicion()
{
	return this->posicion;
}

void JugadorModelo::setPosicion(int posicion)
{
	this->posicion = posicion;
}

string JugadorModelo::getPassword()
{
	return this->password;
}

void JugadorModelo::setPassword(string password)
{
	this->password = password;
}


string JugadorModelo::getNombreImagen()
{
	return this->nombreImagen;
}

void JugadorModelo::setNombreImagen(string nombreImagen)
{
	this->nombreImagen = nombreImagen;
}

CartaModelo* JugadorModelo::getCarta1() 
{
	return this->carta1;
}

void JugadorModelo::setCarta1(CartaModelo* carta1)
{
	this->carta1 = carta1;
}

CartaModelo* JugadorModelo::getCarta2()
{
	return this->carta2;
}

void JugadorModelo::setCarta2(CartaModelo* carta2)
{
	this->carta2 = carta2;
}

int JugadorModelo::getApuesta()
{
	return this->apuesta;
}

void JugadorModelo::setApuesta(int apuesta)
{
	this->apuesta = apuesta;
}

bool JugadorModelo::isActivo()
{
	return !this->ausente && this->activo;
}

void JugadorModelo::setActivo(bool activo)
{
	this->activo = activo;
}

bool JugadorModelo::isAusente(){
	return this->ausente;
}

void JugadorModelo::setAusente(bool ausente){
	this->ausente = ausente;
}

bool JugadorModelo::isJugandoRonda()
{
	return !this->ausente && this->jugandoRonda;
}

void JugadorModelo::setJugandoRonda(bool jugandoRonda)
{
	this->jugandoRonda = jugandoRonda;
}

void JugadorModelo::apostar(int fichas)
{
	if (fichas > this->fichas)
		throw PokerException("No tiene suficientes fichas.");

	this->apuesta += fichas;
	this->fichas -= fichas;
}

void JugadorModelo::incrementarFichas(int cantidad)
{
	this->fichas += cantidad;
}

bool JugadorModelo::isDealer(){
	return this->dealer;
}

void JugadorModelo::setDealer(bool esDealer){
	this->dealer = esDealer;
}

bool JugadorModelo::isVirtual(){
	return this->esVirtual;
}

void JugadorModelo::setVirtual(bool esVirtual){
	this->esVirtual = esVirtual;
}

void JugadorModelo::jugar()
{
	if (this->isVirtual()) {

		int azar = rand();
cout << "numero al azar " << azar << endl;

		// se divide el rango en 5 partes para privilegiar la operacion de Igualar
		int rango = (int)(RAND_MAX / 5);

		if (azar < rango) {
			// caso 1: Subir apuesta

			int limiteSuperior = this->getFichas();
			if (ContextoJuego::getInstancia()->getMesa()->getApuestaMaxima() < limiteSuperior) {
				limiteSuperior = ContextoJuego::getInstancia()->getMesa()->getApuestaMaxima();
			}

			int limiteInferior = ContextoJuego::getInstancia()->getMontoAIgualar() - this->getApuesta();

			// TODO: Aca se podria afectar este valor por otro criterio, que no sea simplemente al azar
			int fichas = (int)(rand() % (limiteSuperior - limiteInferior) + limiteInferior);

			ContextoJuego::getInstancia()->subirApuesta(
				ContextoJuego::getInstancia()->idJugadorToIdCliente(this->getId()), fichas);


		} else if (azar < rango * 4) {

			// caso 2: Igualar apuesta
			if (ContextoJuego::getInstancia()->puedePasar()) {
				ContextoJuego::getInstancia()->pasar(
					ContextoJuego::getInstancia()->idJugadorToIdCliente(this->getId()));

			} else {

				ContextoJuego::getInstancia()->igualarApuesta(
					ContextoJuego::getInstancia()->idJugadorToIdCliente(this->getId()));
			}
			

		} else {
			//caso 3: No ir
			ContextoJuego::getInstancia()->noIr(
				ContextoJuego::getInstancia()->idJugadorToIdCliente(this->getId()));
		}

	} else {
		throw PokerException("Se solicito el metodo jugar() a un jugador no virtual.");
	}
}
