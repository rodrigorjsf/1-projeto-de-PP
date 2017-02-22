#ifndef HEADERCLIENTE_H_
#define HEADERCLIENTE_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>

typedef struct cliente {
	char cpf[12];
	char nome [100];
	char telefone [11];
	char email [100];
	int status;
}TCliente;

TCliente * Cadastro (char cpf[]);
void CadastrarCliente (char cpf[]);
void AlterarCliente (char cpf[]);
void ExibirCliente (char cpf[]);
void RemoverCliente (char cpf[]);
int BuscarCliente (char cpf []);
int ValidaCPF (char cpf[]);
int ValidaNome (char nome[]);
int ValidaTelefone (char telefone[]);
int ValidaEmail (char email[]);



#endif /* HEADERCLIENTE_H_ */
