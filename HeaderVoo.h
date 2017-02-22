/*
 * HeaderVoo.h
 *
 *  Created on: 22 de fev de 2017
 *      Author: Rodrigo
 */

#ifndef HEADERVOO_H_
#define HEADERVOO_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct voo {
	char codVoo [20];
	char origem [100];
	char destino [100];
	char data [9];
	char horario [5];
	int poltronas;
	int mapaPoltronas [6][6];
	float valor;
	int status;
};

void CadastrarVoo ();
void ProcurarVoo (char origem[], char destino[], char data[]);
void AlterarValorPassagem (char cod[]);
void CancelarVoo (char cod[]);
int BuscarVoo (char cod []);
int ValidaCodVoo (char cod[]);
int ValidaData (char data[]);
int ValidaHora (char hora[]);

#endif /* HEADERVOO_H_ */
