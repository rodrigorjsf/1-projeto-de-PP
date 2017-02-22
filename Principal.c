#include "HeaderCliente.h"
#include "HeaderPassagem.h"
#include "HeaderVoo.h"


FILE * criarArquivo (char nome[]) {
	FILE * arq;
	arq = fopen (nome, "r+b");
	if (arq == NULL) {
		arq = fopen (nome, "w+b");
	}
	return arq;
}
void ModuloCliente ();
void ModuloPassagem ();
void ModuloVoo ();

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

void ModuloPassagem (){
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
		          CadastrarPassagem (origem, destino, data);
			      break;
		case '2': printf ("Informe o cpf do Cliente: ");
				  gets (cpfAux); fflush (stdin);
				  ConsultarPassagem (cpfAux);
				  break;
		case '3': printf ("Informe o Codigo da Reserva: ");
				  gets (codReservaAux); fflush (stdin);
				  CancelarPassagem (codReservaAux);
				  break;
		case '4': printf ("Informe o Codigo do Voo: ");
				  gets (codVooAux); fflush (stdin);
				  ConsultarVoo (codVooAux);    //  CONSULTA PASSAGEIROS DE UM VOO
				  break;
		case '5': break;
		default: printf ("Opcao invalida \n");
		}
	} while (op != '5');
}

void ModuloVoo (){
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
		case '1': CadastrarVoo ();
			      break;
		case '2': printf ("Informe a Origem: ");
                  gets (origem); fflush (stdin);
                  printf ("Informe o Destino: ");
                  gets (destino); fflush (stdin);
                  printf ("Informe a data do voo: ");
                  gets (data); fflush (stdin);           // TIRAR DUVIDA SOBRE COLAR BARRAS NA DATA
				  ProcurarVoo (origem, destino, data);
				  break;
		case '3': printf ("Informe o Codigo do Voo: ");
				  gets (codVooAux); fflush (stdin);
				  AlterarValorPassagem (codVooAux);
				  break;
		case '4': printf ("Informe o Codigo do Voo: ");
				  gets (codVooAux); fflush (stdin);
				  CancelarVoo (codVooAux);
				  break;
		case '5': break;
		default: printf ("Opcao invalida \n");
		}
	} while (op != '5');
}

