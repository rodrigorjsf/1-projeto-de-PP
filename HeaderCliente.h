#ifndef HEADERCLIENTE_H_
#define HEADERCLIENTE_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <ctype.h>

typedef struct cliente {
	char cpf[12];          //PORUQE TEM QUE SER CHAR?
	char nome [100];
	char telefone [12];
	char email [100];
	int status;
}TCliente;

void CadastrarCliente (FILE * arq);
void AlterarCliente (FILE * arq);
void ExibirCliente (FILE * arq);
void RemoverCliente (FILE * arq);
int BuscarCliente (FILE * arq, char cpf []);
int ValidaCPF (char cpf[]);
int ValidaNome (char nome[]);
int ValidaTelefone (char telefone[]);
int ValidaEmail (char email[]);



#endif /* HEADERCLIENTE_H_ */
