#ifndef HEADERPASSAGEM_H_
#define HEADERPASSAGEM_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

typedef struct passagem {
	char codReserva [20];
	char cpf [12];
	char codVoo [20];
	int poltrona;
	int status;
}TPass;

TPass * CadastroPassagem (char origem[], char destino[], char data[], char cpf[]);   //  CONFERIR  VARIAVEIS DE ENTRADA
void CadastrarPassagem (FILE * arq, char origem[], char destino[], char data[]);
void ConsultarPassagem (FILE * arq, char cpf []);
void CancelarPassagem (FILE * arq, char cod[]);
void ConsultarVoo (FILE * arq, char cod[]);  //  CONSULTA PASSAGEIROS DE UM VOO

#endif /* HEADERPASSAGEM_H_ */
