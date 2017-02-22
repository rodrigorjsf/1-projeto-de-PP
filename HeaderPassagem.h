/*
 * HeaderPassagem.h
 *
 *  Created on: 22 de fev de 2017
 *      Author: Rodrigo
 */

#ifndef HEADERPASSAGEM_H_
#define HEADERPASSAGEM_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct passagem {
	char codReserva [20];
	char cpf [12];
	char codVoo [20];
	int poltrona;
	int status;
}TPass;

TPass * CadastroPassagem (char origem[], char destino[], char data[], char cpf[]);   //  CONFERIR  VARIAVEIS DE ENTRADA
void CadastrarPassagem (char origem[], char destino[], char data[]);
void ConsultarPassagem (char cpf []);
void CancelarPassagem (char cod[]);
void codVooAux (char cod[]);  //  CONSULTA PASSAGEIROS DE UM VOO

#endif /* HEADERPASSAGEM_H_ */
