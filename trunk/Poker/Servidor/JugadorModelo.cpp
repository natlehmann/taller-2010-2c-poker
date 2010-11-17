#include "JugadorModelo.h"
#include "PokerException.h"
#include "ContextoJuego.h"
#include "RecursosServidor.h"
#include "UtilTiposDatos.h"
#include "MensajesUtil.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "Jugada.h"

#define NIVEL_DE_CONFIANZA_MAXIMO 1
#define NIVEL_DE_CONFIANZA_MUY_ALTO 0.9
#define NIVEL_DE_CONFIANZA_ALTO 0.8
#define NIVEL_DE_CONFIANZA_MEDIO_ALTO 0.7
#define NIVEL_DE_CONFIANZA_MEDIO 0.6
#define NIVEL_DE_CONFIANZA_BAJO 0.3
#define NIVEL_DE_CONFIANZA_MUY_BAJO 0.15
#define COEF_CONFIANZA_PARA_SUBIR 0.85
#define COEF_PARA_ALL_IN 0.8
#define PORC_MAX_FICHAS_POCA_CONFIANZA 0.01


JugadorModelo::JugadorModelo(int id, int posicion)
{
	this->id = id;
	this->nombre = "";
	this->fichas = 0;
	this->posicion = posicion;
	this->password = "";
	this->nombreImagen = "";
	this->carta1 = NULL;
	this->carta2 = NULL;
	this->apuesta = 0;
	this->activo = false;
	this->jugandoRonda = false;
	this->ausente = true;
	this->dealer = false;
	this->esVirtual = false;
	this->observador = false;
	this->allIn = false;
	this->timer.iniciar();

	srand ((unsigned int)(time(NULL)));

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
	this->ausente = false; // TODO: esta bien que sea false?
	this->dealer = false;
	this->esVirtual = false;
	this->observador = false;
	this->allIn = false;
	this->timer.iniciar();

	srand ((unsigned int)(time(NULL)));

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

	if (this->fichas == 0) {
		this->allIn = true;
	}
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

bool JugadorModelo::isObservador(){
	return this->observador;
}

void JugadorModelo::setObservador(bool observador){
	this->observador = observador;
}

bool JugadorModelo::isAllIn(){
	return this->allIn;
}

void JugadorModelo::setAllIn(bool allIn){
	this->allIn = allIn;
}

void JugadorModelo::jugar()
{
	if (this->isVirtual() && !this->isAllIn()) {
		
		list<CartaModelo*> cartas = ((ContextoJuego::getInstancia())->getCartasComunitarias())->getCartas();

		double confianza = 0;

		if (cartas.empty()) {

			if (this->carta1->getValorNumerico() > 11 && this->carta1->getValorNumerico() == this->carta2->getValorNumerico())
				confianza = NIVEL_DE_CONFIANZA_MAXIMO;
			else
			if (this->carta1->getValorNumerico() > 10 && this->carta2->getValorNumerico() > 10)
				confianza = NIVEL_DE_CONFIANZA_MUY_ALTO;
			else 
			if (this->carta1->getValorNumerico() == this->carta2->getValorNumerico())
				confianza = NIVEL_DE_CONFIANZA_ALTO;
			else 
			if (MensajesUtil::sonIguales(this->carta1->getPalo(), this->carta2->getPalo())
				|| this->carta1->getValorNumerico() > 10 
				|| this->carta2->getValorNumerico() > 10)
				confianza = NIVEL_DE_CONFIANZA_MEDIO_ALTO;
			else 
				confianza = NIVEL_DE_CONFIANZA_MEDIO;

			tomarDecision(confianza);

		} else {

			Jugada* jugada = new Jugada();
			jugada->agregarCartas(cartas);
			jugada->agregarCarta(this->getCarta1());
			jugada->agregarCarta(this->getCarta2());
			
			double valorDeJugada = 	jugada->getValorJugada();
			double valorDeJugadaComun = 0;

			if (cartas.size() == 5) {
				Jugada* jugadaComun = new Jugada();
				jugadaComun->agregarCartas(cartas);
				
				valorDeJugadaComun = jugadaComun->getValorJugada();
			}

			if (valorDeJugada > valorDeJugadaComun) {

				if (jugada->isEscaleraColor() || jugada->isPoker() || jugada->isFull()) 
					confianza = NIVEL_DE_CONFIANZA_MAXIMO;
				else
				if (jugada->isColor() || jugada->isEscalera()) 
					confianza = NIVEL_DE_CONFIANZA_MUY_ALTO;
				else
				if (jugada->isPierna())
					confianza = NIVEL_DE_CONFIANZA_ALTO;
				else
				if (jugada->isParDoble())
					if (valorDeJugada > Jugada::valorParDoblePromedio)
						confianza = NIVEL_DE_CONFIANZA_ALTO;
					else
						confianza = NIVEL_DE_CONFIANZA_MEDIO_ALTO;
				else
				if (jugada->isPar())
					if (valorDeJugada > Jugada::valorParPromedio)
						confianza = NIVEL_DE_CONFIANZA_MEDIO_ALTO;
					else
						confianza = NIVEL_DE_CONFIANZA_MEDIO;
				else
				if (cartas.size() == 5)
					if (valorDeJugada > Jugada::valorJugadaPromedio)
						confianza = NIVEL_DE_CONFIANZA_BAJO;
					else
						confianza = NIVEL_DE_CONFIANZA_MUY_BAJO;
				else
					confianza = NIVEL_DE_CONFIANZA_MEDIO;

			} else {
				confianza = NIVEL_DE_CONFIANZA_MEDIO_ALTO;
			}

			tomarDecision(confianza);
		}
	} else {
		throw PokerException("Se solicito el metodo jugar() a un jugador no virtual.");
	}
}

void JugadorModelo::tomarDecision(double confianza) {

	int apuestaARealizar = 0;
	double azar = (double)(rand() / (double)RAND_MAX);

	if (azar < confianza) {	
		if (ContextoJuego::getInstancia()->puedeSubirApuesta(this->getId()) 
			&& subeApuesta(confianza, apuestaARealizar)) {
			ContextoJuego::getInstancia()->subirApuesta(ContextoJuego::getInstancia()->idJugadorToIdCliente(this->getId()), apuestaARealizar);
		} else {
			ContextoJuego::getInstancia()->igualarApuesta(ContextoJuego::getInstancia()->idJugadorToIdCliente(this->getId()));
		}
	} else {
		if (this->getApuesta() < ContextoJuego::getInstancia()->getMontoAIgualar()) {
			int diferencia = ContextoJuego::getInstancia()->getMontoAIgualar() - this->getApuesta();
			if (diferencia > this->getFichas() * PORC_MAX_FICHAS_POCA_CONFIANZA) {
				ContextoJuego::getInstancia()->noIr(ContextoJuego::getInstancia()->idJugadorToIdCliente(this->getId()));
			} else {
				ContextoJuego::getInstancia()->igualarApuesta(ContextoJuego::getInstancia()->idJugadorToIdCliente(this->getId()));
			}
		} else {
			// Pasar
			ContextoJuego::getInstancia()->igualarApuesta(ContextoJuego::getInstancia()->idJugadorToIdCliente(this->getId()));
		}
	}
}

bool JugadorModelo::subeApuesta(double confianza, int &apuestaTotal)
{
	double confianzaParaSubir = confianza * COEF_CONFIANZA_PARA_SUBIR;
	double azar = (double)(rand() / (double)RAND_MAX);

	if (azar < confianzaParaSubir) {

		int limiteSuperior = this->getFichas();
		int limiteInferior = ContextoJuego::getInstancia()->getMontoAIgualar() - this->getApuesta();
		int montoMaximo = limiteSuperior - limiteInferior;

		if (montoMaximo > ContextoJuego::getInstancia()->getMesa()->getApuestaMaxima()) {
			montoMaximo = ContextoJuego::getInstancia()->getMesa()->getApuestaMaxima();
			limiteInferior = 0;
		}

		int fichasAApostar = 0;
		double azarParaSubir = (double)(rand() / (double)RAND_MAX);
		if (confianza == NIVEL_DE_CONFIANZA_MAXIMO || confianza == NIVEL_DE_CONFIANZA_MUY_ALTO) {
			fichasAApostar = (int)(montoMaximo * confianza * azar * azarParaSubir);
		} else {
			double azarParaSubir2 = (double)(rand() / (double)RAND_MAX);
			fichasAApostar = (int)(montoMaximo * confianzaParaSubir * azar * azarParaSubir * azarParaSubir2);
		}

		apuestaTotal = (int)(fichasAApostar + limiteInferior);

		if (apuestaTotal >= COEF_PARA_ALL_IN * limiteSuperior) {
			apuestaTotal = limiteSuperior;
		} else {
			if (apuestaTotal == 0) {
				apuestaTotal = 1;
			}
		}

		return true;
	} else {
		return false;
	}
}

void JugadorModelo::resetTimer() {
	this->timer.iniciar();
}

int JugadorModelo::getSegundosTurno(){
	return this->timer.getSegundos();
}

