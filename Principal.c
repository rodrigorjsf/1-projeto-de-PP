#include <stdio.h>
#include "HeaderCliente.h"


FILE * criarArquivo (char nome[]) {
	FILE * arq;
	arq = fopen (nome, "r+b");
	if (arq == NULL) {
		arq = fopen (nome, "w+b");
	}
	return arq;
}
void ModuloCliente ();

int main () {
	int i;
	char op, codAux[100], nomeArqum [] = "Cliente.dat", nomeArqdois [] = "Passagem.dat", nomeArqtres [] = "Voo.dat";
	FILE * arqCliente,arqPassagem,arqVoo;
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
		   case '1': ModuloCliente ();
				     break;
		   case '2': ModuloPassagem ();
				     break;
		   case '3': ModuloVoo ();
				     break;
		   case '4': manutencao (arqVoo);
		             break;
		   default: printf ("Opcao invalida \n");
		   }
		} while (op != '4');
	}
    return 0;
}

void ModuloCliente (){
	char op, cpfAux [12];
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
		case '1': printf ("Informe o cpf do Cliente: ");
		          gets (cpfAux); fflush (stdin);
		          CadastrarCliente (cpfAux);
			      break;
		case '2': printf ("Informe o cpf do Cliente: ");
				  gets (cpfAux); fflush (stdin);
				  AlterarCliente (cpfAux);
				  break;
		case '3': printf ("Informe o cpf do Cliente: ");
				  gets (cpfAux); fflush (stdin);
				  ExibirCliente (cpfAux);
				  break;
		case '4': printf ("Informe o cpf do Cliente: ");
				  gets (cpfAux); fflush (stdin);
				  RemoverCliente (cpfAux);
				  break;
		case '5': break;
		default: printf ("Opcao invalida \n");
		}
	} while (op != '5');
}


