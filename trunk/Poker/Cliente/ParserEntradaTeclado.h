#ifndef _PARSERENTRADATECLADO_H__
#define _PARSERENTRADATECLADO_H__

#define XML_OP_SUMA "S"
#define XML_OP_RESTA "R"
#define XML_OP_MULT "M"
#define XML_OP_DIV "D"
#define XML_TAG_PEDIDO "pedido"
#define XML_TAG_OPERACION "operacion"
#define XML_TAG_PARAMETROS "parametros"
#define XML_TAG_PARAMETRO "parametro"
#define XML_TAG_ERRORES "errores"
#define XML_TAG_RESULTADOS "resultados"
#define XML_ATR_NOMBRE "nombre"
#define XML_ATR_ID "id"
#define XML_ATR_TIPO_SUM "sum"
#define XML_ATR_TIPO_RES "res"
#define XML_ATR_TIPO_MUL "mul"
#define XML_ATR_TIPO_DIVIDENDO "dividendo"
#define XML_ATR_TIPO_DIVISOR "divisor"

#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <string.h>
#include <sstream>
#include <list>
#include <set>
#include <map>
#include <deque>

#include <list>
#include "DomTree.h"

using namespace std;

class ParserEntradaTeclado
{
private:
	string _codigoOperacion;
	list<string>* _lstOperandos;

	string obtenerTipoParametro(int numeroParametro);
	DomTree* toDom();

public:
	ParserEntradaTeclado(string codigoOperacion, list<string>* lstOperandos);
	virtual ~ParserEntradaTeclado(void);

	string generarMensaje();
	string obtenerRespuesta(string respuesta);


};

#endif
