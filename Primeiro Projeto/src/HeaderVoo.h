#ifndef HEADERVOO_H_
#define HEADERVOO_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#define ANO 2017

typedef struct voo {
	char codVoo [8];
	char origem [100];
	char destino [100];
	char dia [3];
	char mes [3];
	char hora [3];
	char min [3];
	int poltronas;
	char mapaPoltronas [6][6];
	float valor;
	int status;
}TVoo;

void gerarCodigo (TVoo * v);
int BuscarVoo(FILE * arq, char cod[]);
int RecebeCOD(char cod[]);
void CadastrarData (Data * d);
void CadastrarHorarioNaEstrutura (TVoo * v);
void CadastrarHorario (Horario * h);
void CadastrarVoo (FILE * arq);
int BuscarTodosVoos (FILE * arq, int origem, int destino, Data d , int pos);
void ProcurarVoo (FILE * arq, int origem, int destino, Data d);
int RecebeCodVoo(char cod[]);
void AlterarValorPassagem (FILE * arq, char cod[]);
void CancelarVoo (FILE * arq, char cod[]);
void menuProcurarVoo (FILE *arqPass, FILE *arqCliente,FILE * arqVoo ,char op);
void MenuVOO (FILE *arqPass, FILE *arqCliente,FILE * arqVoo ,char op);

#endif /* HEADERVOO_H_ */
