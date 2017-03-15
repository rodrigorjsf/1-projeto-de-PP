#ifndef HEADERCLIENTE_H_
#define HEADERCLIENTE_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <ctype.h>
#include <time.h>

typedef struct cliente {
	char cpf[12];          //PORUQE TEM QUE SER CHAR?
	char nome [100];
	char telefone [12];
	char email [100];
	int status;
}TCliente;

int RecebeCPF(char cpf[]);
char * gerarMaiusculo (char nome[]);
void CadastrarNome (TCliente * c);
void CadastrarTelefone (TCliente * c);
void CadastrarEmail (TCliente * c);
void CadastrarCliente (FILE * arq, char cpf []);
void AlterarCliente (FILE * arq, char cpf []);
void ExibirCliente (FILE * arq, char cpf []);
void RemoverCliente (FILE * arq, char cpf []);
int BuscarCliente (FILE * arq, char cpf []);
int ValidaCPF (char cpf[]);
int ValidaNome (char nome[]);
int ValidaTelefone (char telefone[]);
int ValidaEmail (char email[]);



#endif /* HEADERCLIENTE_H_ */
