#ifndef HEADERVOO_H_
#define HEADERVOO_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

typedef struct voo {
	char codVoo [8];
	char origem [100];
	char destino [100];
	char dia [3];
        char mes [3];
	char hora [3];
        char min [3];
	int poltronas;
	int mapaPoltronas [6][6];
	float valor;
	int status;
}TVoo;

char * gerarCodigo ();
void CadastrarVoo (FILE * arq);
void ProcurarVoo (FILE * arq, char origem[], char destino[], char data[]);
void AlterarValorPassagem (FILE * arq, char cod[]);
void CancelarVoo (FILE * arq, char cod[]);
int BuscarVoo (FILE * arq, char cod []);
int ValidaCodVoo (char cod[]);
int ValidaData (char data[]);
int ValidaHora (char hora[]);

#endif /* HEADERVOO_H_ */
