#include <ctype.h>
#include "HeaderCliente.h"
#include "HeaderPassagem.h"
#include "HeaderVoo.h"
#DEFINE ANO_ATUAL 2017

typedef struct data {
	char dia[3];
        char mes[3];
}Data;

typedef struct horario {
        char hora[3];
        char min[3];
}Horario;

FILE * criarArquivo (char nome[]) {
	FILE * arq;
	arq = fopen (nome, "r+b");
	if (arq == NULL) {
		arq = fopen (nome, "w+b");
	}
	return arq;
}

void ModuloCliente (FILE * arqCliente);
void ModuloPassagem (FILE * arqPassagem);
void ModuloVoo (FILE * arqVoo);

int comparaHora (char dia[], char mes[], char hora[], char min[])
{
    Data d;
    time_t tp;
    struct tm *local;
    Horario h;
    int validar, dias;
    tp = time (NULL);
    local = localtime (&tp);
    strftime(d.dia, sizeof(d.dia), "%d", local);
    strftime(d.mes, sizeof(d.mes), "%m", local);
    strftime(h.hora, sizeof(h.hora), "%H", local);
    strftime(h.min, sizeof(h.min), "%M", local);
    if (strcmp (mes, d.mes) < 0) 
        return 0;
    else if (strcmp (mes, d.mes) == 0)    //mes igual
    {
        if (strcmp (dia, d.dia) < 0)
            return 0;
        else if (strcmp (dia, d.dia) == 0)
        {
            if(strcmp (hora, h.hora) < 0)
                return 0;
            else if (strcmp (hora, h.hora) == 0)
            {
                if ((strcmp (min, h.min) < 0))
                    return 0;
                else
                    return 1;
            }
            else
                return 1;
        }
        else
            return 1;             
    }
    else
        return 1;  
}

int main () {
	int i;
	char op, codAux[100], nomeArqum [] = "Cliente.dat", nomeArqdois [] = "Passagem.dat", nomeArqtres [] = "Voo.dat";
	FILE * arqCliente,*arqPassagem,*arqVoo;
	arqCliente = criarArquivo (nomeArqum);
	arqPassagem = criarArquivo (nomeArqdois);
	arqVoo = criarArquivo (nomeArqtres);
	if (arqCliente == NULL || arqPassagem == NULL || arqVoo == NULL )
		printf ("Erro ao tentar criar/abrir arquivo \n");
	else {
	    do {
	       printf ("Consultar: \n");
	   	   printf ("1 - Modulo do Cliente \n");
	   	   printf ("2 - Modulo de Passagens \n");
		   printf ("3 - Modulo de Voos \n");
		   printf ("4 - Sair \n");
		   printf ("Digite a opcao: ");
		   op = getchar (); fflush (stdin);
		   switch (op) {
		   case '1': ModuloCliente (arqCliente);
				     break;
		   case '2': ModuloPassagem (arqPassagem);
				     break;
		   case '3': ModuloVoo (arqVoo);
				     break;
		   case '4': manutencao (arqVoo);     //FALTA VERIFICAR SE E ISSO MESMO
		             break;
		   default: printf ("Opcao invalida \n");
		   }
		} while (op != '4');
	}
    return 0;
}

void ModuloCliente (FILE * arqPassagem, FILE * arqVoo,FILE * arqCliente){
	char op, auxCpf[12];
	int i, aux;
	do {
		system ("cls");
		printf ("-------------------- Modulo do Cliente -------------------- \n");
		printf ("1 - Cadastrar Cliente \n");
		printf ("2 - Alterar Cliente \n");
		printf ("3 - Exibir Cliente \n");
		printf ("4 - Remover Cliente \n");
		printf ("5 - Sair \n");
		printf ("informe a opcao: ");
		op = getchar (); fflush (stdin);
		switch (op) {
		case '1':
			do{
				i = 0;
				system ("cls");
				printf ("Informe o CPF do Cliente: ");
				while(i <= 11){
					auxCpf[i] = getche();
					if (i == 2)
						printf (".");
					if (i == 5)
						printf (".");
					if (i == 8)
						printf ("-");
					if (i == 11)
						auxCpf[12] = '\0';
				}
				aux = RecebeCPF(auxCpf);
			}while (aux == 0);
			if (aux == 2)
				break;
			else
				CadastrarCliente (arqCliente, auxCpf);
			break;
		case '2':
			do{
				i = 0;
				system ("cls");
				printf ("Informe o CPF do Cliente: ");
				while(i <= 11){
					auxCpf[i] = getche();
					if (i == 2)
						printf (".");
					if (i == 5)
						printf (".");
					if (i == 8)
						printf ("-");
					if (i == 11)
						auxCpf[12] = '\0';
				}
				aux = RecebeCPF(auxCpf);
			}while (aux == 0);
			if (aux == 2)
				break;
			else
				AlterarCliente (arqCliente, auxCpf);
			break;
		case '3':
			do{
				i = 0;
				system ("cls");
				printf ("Informe o CPF do Cliente: ");
				while(i <= 11){
					auxCpf[i] = getche();
					if (i == 2)
						printf (".");
					if (i == 5)
						printf (".");
					if (i == 8)
						printf ("-");
					if (i == 11)
						auxCpf[12] = '\0';
				}
				aux = RecebeCPF(auxCpf);
			}while (aux == 0);
			if (aux == 2)
				break;
			else
				ExibirCliente (arqCliente, auxCpf);
			break;
		case '4':
			do{
				i = 0;
				system ("cls");
				printf ("Informe o CPF do Cliente: ");
				while(i <= 11){
					auxCpf[i] = getche();
					if (i == 2)
						printf (".");
					if (i == 5)
						printf (".");
					if (i == 8)
						printf ("-");
					if (i == 11)
						auxCpf[12] = '\0';
				}
				aux = RecebeCPF(auxCpf);
			}while (aux == 0);
			if (aux == 2)
				break;
			else
				RemoverCliente (arqPassagem,arqVoo,arqCliente, auxCpf);
			break;
		case '5':
			break;
		default: printf ("Opcao invalida \n");
		}
	} while (op != '5');
}

void ModuloPassagem (FILE * arqPassagem, FILE * arqVoo){
	char op, cpfAux [12],codReservaAux[20], codVooAux[20], origem[100], destino[100], data[9];
	do {
		system ("cls");
		printf ("-------------------- Modulo de Passagem -------------------- \n");
		printf ("1 - Comprar Passagem \n");
		printf ("2 - Consultar Passagens de Cliente \n");
		printf ("3 - Cancelar Passagem \n");
		printf ("4 - Consultar passageiro de um voo  \n");
		printf ("5 - Sair \n");
		printf ("informe a opcao: ");
		op = getchar (); fflush (stdin);
		switch (op) {
		case '1': printf ("Informe a Origem: ");
		          gets (origem); fflush (stdin);
		          printf ("Informe o Destino: ");
		          gets (destino); fflush (stdin);
		          printf ("Informe a data do voo: ");
		          gets (data); fflush (stdin);           // TIRAR DUVIDA SOBRE COLAR BARRAS NA DATA
		          CadastrarPassagem (arqPassagem, origem, destino, data);
			      break;
		case '2': printf ("Informe o cpf do Cliente: ");
				  gets (cpfAux); fflush (stdin);
				  ConsultarPassagem (arqPassagem, arqVoo, cpfAux);
				  break;
		case '3': printf ("Informe o Codigo da Reserva: ");
				  gets (codReservaAux); fflush (stdin);
				  CancelarPassagem (arqPassagem, codReservaAux);
				  break;
		case '4': printf ("Informe o Codigo do Voo: ");
				  gets (codVooAux); fflush (stdin);
				  ConsultarVoo (arqPassagem, codVooAux);    //  CONSULTA PASSAGEIROS DE UM VOO
				  break;
		case '5': break;
		default: printf ("Opcao invalida \n");
		}
	} while (op != '5');
}

void ModuloVoo (FILE * arqVoo){
	char op, codVooAux[20], origem[100], destino[100], data[9];
	do {
		system ("cls");
		printf ("-------------------- Modulo de Voo -------------------- \n");
		printf ("1 - Cadastrar Voo \n");
		printf ("2 - Procurar Voo \n");
		printf ("3 - Alterar Valor da Passagem \n");
		printf ("4 - Cancelar Voo \n");
		printf ("5 - Sair \n");
		printf ("informe a opcao: ");
		op = getchar (); fflush (stdin);
		switch (op) {
		case '1': CadastrarVoo (arqVoo);
			      break;
		case '2': printf ("Informe a Origem: ");
                  gets (origem); fflush (stdin);
                  printf ("Informe o Destino: ");
                  gets (destino); fflush (stdin);
                  printf ("Informe a data do voo: ");
                  gets (data); fflush (stdin);           // TIRAR DUVIDA SOBRE COLAR BARRAS NA DATA
				  ProcurarVoo (arqVoo, origem, destino, data);
				  break;
		case '3': printf ("Informe o Codigo do Voo: ");
				  gets (codVooAux); fflush (stdin);
				  AlterarValorPassagem (arqVoo, codVooAux);
				  break;
		case '4': printf ("Informe o Codigo do Voo: ");
				  gets (codVooAux); fflush (stdin);
				  CancelarVoo (arqVoo, codVooAux);
				  break;
		case '5': break;
		default: printf ("Opcao invalida \n");
		}
	} while (op != '5');
}

int buscar (FILE * arq, char nomeAux[]) {
	int cont = -1, status;
	TCliente c;

	fseek (arq, 0, 0);
	while (1) {
		status = fread (&c, sizeof (TCliente), 1, arq);
		if (status != 1) {
			if (!feof(arq))
			    return -2; // erro de leitura
			else
				return -1; // nao achou
		}
		else {
			cont++;
			if (c.status == 1 && strcmp (c.nome, nomeAux) == 0)
				return cont;
		}
	}
}

