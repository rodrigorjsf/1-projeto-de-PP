#include "HeaderCliente.h"
#include <ctype.h>

int BuscarCliente (FILE * arq, char cpf []){
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
				if (c.status == 1 && strcmp (c.nome, cpf) == 0)
					return cont;
			}
		}
}


int ValidaCPF (char cpf[]){ 
	int icpf[12];  
	int i,soma=0,digito1,result1,result2,digito2,valor;  
	  
	printf("Digite o cpf: ");  
	scanf(" %s",cpf);  	
	for(i=0;i<11;i++)  //Efetua a conversao de array de char para um array de int.  
	{  
		icpf[i]=cpf[i]-48;  
	}  
	for(i=0;i<9;i++)  //PRIMEIRO DIGITO.  
	{  
		soma+=icpf[i]*(10-i);  
	}  
	result1=soma%11;  
	if( (result1==0) || (result1==1) )  
	{  
		digito1=0;  
	}  
	else  
	{  
		digito1 = 11-result1;  
	}
	soma=0;  
	for(i=0;i<10;i++)  //SEGUNDO DIGITO.  
	{  
		soma+=icpf[i]*(11-i);  
	}  
	valor=(soma/11)*11;  
	result2=soma-valor;  	  
	if( (result2==0) || (result2==1) )  
	{  
		digito2=0;  
	}  	  
	else  
	{  
		digito2=11-result2;  
	}  	  
	if((digito1==icpf[9]) && (digito2==icpf[10]))   //RESULTADOS DA VALIDACAO.  
	{  
		printf("\nCPF VALIDADO.\n");  
	}  
	else  
	{  
		printf("Problema com os digitos.\n");  
	}  
	return 0;  
}  

//letras e espacos
int ValidaNome(char nome[]) {
	int i;

	for (i = 0; nome[i]; i++) {
		if (isalpha(nome[i]) == 0) {
			if(isspace(nome[i]) == 0)
				return 0;
		}
	}
	return 1;
}

//numeros
int ValidaTelefone(char telefone[]) {
	int i;

	for (i = 0; telefone[i]; i++) {
		if (isdigit(telefone[i]) == 0) {
			return 0;
		}
	}
	return 1;
}

//letras, numeros, pontos e um @
int ValidaEmail(char email[]) {
	int i, j = 0;

	for (i = 0; email[i]; i++) {
		if (isalnum(email[i]) == 0) {//letra e numero
			if (email[i] != 46) {//ponto
				if (email[i] == 64) {//se for arroba i++
					j++;
				}
				if (j > 1) {
					return 0;
				}
				if (email[i] != 64) {//arroba
					return 0;
				}
			}
		}
	}
	return 1;
}
