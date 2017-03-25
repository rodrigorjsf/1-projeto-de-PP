
#ifndef VALIDACOES_H_
#define VALIDACOES_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <ctype.h>
#include <time.h>
#define ANO 2017

void opcoesOrigem ();
void opcoesDestinos ();
int comparaHora_e_Data (char dia[], char mes[], char hora[], char min[]);
int bissexto (int ano);
int comparaHoraLocal (Horario horario);
int comparaDataLocal (Data data);
int BuscarCliente (FILE * arq, char cpf []);
int ValidaCPF (char cpf[]);
int validaRemocao (FILE * arqPass, FILE * arqVoo,char cpf[]);
int validaDataCorreta(Data d);
int validaHoraCorreta (Horario horario);
int ValidaData(Data d);
int ValidaHora(Horario horario);
int ValidaCodVoo(char cod[]);
int validaCodReserva(char cod[]);


#endif /* VALIDACOES_H_ */
