#include "HeaderCliente.h"

int RecebeCPF(char cpf[]){

	int i, validar, sair = 0;
	char op;
	i = 0;
	validar = ValidaCPF (cpf);
	if (validar == 0)
	{
		printf("CPF invalido, deseja tentar denovo? (S/N) \n");
		do{
			op = getche();
			if (op != 78 && op != 83 && op != 110 && op != 115)
			{
				printf("Opcao invalida. Deseja recadastrar o CPF? (S/N) \n");
			}
			else if (op == 78 || op == 110)
				return 2;                             // se for invalido e nao deseja tentar novamente
			else
				return 0;                    //se for invalido e desejar tentar denovo
		}while(1);
	}
	else
		return 1;	                                               /////////// se for valido
}

char * gerarMaiusculo (char nome[]){
	char maiusculo [100];
        maiusculo = (char *)malloc(100 * sizeof(char));
	int i;
	for(i=0; nome[i]!= '\0'; i++)
		maiusculo[i] = toupper(nome[i]);
        maiusculo[i] = '\0';
	return maiusculo;
}

void CadastrarNome (TCliente * c)
{
	char nomeAux[100], nome [100];
	int i;
	do{
		i = 0;
		system("cls");
		printf("Digite o nome do cliente: \n");
		while(i < 100)
		{
			nome[i] = getche();
			if (i == 99)
				nome[100] = '\0';
			if (nome[i] == 13)
			{
				nome[i] = '\0';
				break;
			}
			i++;
		}
		if (ValidaNome(nome) == 1){
			nomeAux = gerarMaiusculo (nome);
			strcpy(c.nome, nomeAux);
		}
		else{
			printf("Nome invalido. Por favor, inserir nome valido. \n");
			system("pause");
		}
	}while (ValidaNome(nome) == 0);
}

void CadastrarTelefone (TCliente * c)
{
	char tel[12];
	int i;
	do{
		i = 0;
		system("cls");
		printf("Digite o telefone do cliente: \n");
		while(i < 12)
		{
			if (i == 0)
				printf ("(");
			tel[i] = getche();
			if (i == 1)
				printf (") ");
			if (i == 6)
				printf ("-");
			if (i == 11)
				tel[12] = '\0';
			i++;
		}
		if (ValidaTelefone(tel) == 1)
			strcpy(c.telefone, tel);
		else{
			printf("Telefone invalido. Por favor, inserir numero valido. \n");
			system("pause");
		}
	}while (ValidaTelefone(tel) == 0);
}

void CadastrarEmail (TCliente * c)
{
	char email[100];
	int i;
	do{
		i = 0;
		system("cls");
		printf("Digite o e-mail do cliente: \n");
		while(i < 100)
		{
			email[i] = getche();
			if (i == 99)
				email[100] = '\0';
			if (email[i] == 13)
			{
				email[i] = '\0';
				break;
			}
			i++;
		}
		if (ValidaEmail(email) == 1)
			strcpy(c.email, email);
		else{
			printf("E-Mail invalido. Por favor, inserir e-mail valido. \n");
			system("pause");
		}
	}while(ValidaEmail(email) == 0);
}

void CadastrarCliente (FILE * arq, char cpf [])
{
	TCliente cliente;
	int aux, i, validar,sair = 0;
	char nomeAux [100];

	aux = BuscarCliente (arq, cpf);
	if (aux > -1)
		printf ("Cliente ja cadastrado. \n");
	else{
		int status;
		strcpy (cliente.cpf, cpf);
		cliente.status = 1;
		CadastrarNome (&cliente);
		CadastrarTelefone (&cliente);
		CadastrarEmail (&cliente);
		status = fwrite(&cliente,sizeof(TCliente),1,arq);
		if (status != 1)
			printf ("Erro de gravacao \n");
		else
			printf ("Cliente cadastrado com sucesso \n");
		system ("pause");
	}
}

void AlterarCliente(FILE * arq, char cpf []){
    int escolha;
    TCliente cliente;
    int pos, status;
    char op;

    pos = BuscarCliente (arq, cpf);
    if (pos == -1)
        printf ("Cliente nao cadastrado \n");
    else if (pos == -2)
        printf ("Erro de leitura \n");
    else {
        fseek(arq, pos * sizeof (TCliente), 0);
        status = fread (&cliente,sizeof (TCliente), 1, arq);
    }
    for (escolha = 1; escolha != 2; ) {
    	printf("Escolha o que deseja altrar: ");
    	printf ("1 - Alterar nome \n");
    	printf ("2 - Alterar email \n");
    	printf ("3 - Alterar telefpne \n");
    	printf ("4 - Sair \n");
    	printf ("informe a opcao: ");
    	op = getchar (); fflush (stdin);
    	switch (op) {
    	case 1:
    		CadastrarNome (&cliente);
    		break;
        case 2:
        	CadastrarEmail (&cliente);
        	break;
        case 3:
        	CadastrarTelefone (&cliente);
        	break;
        case 4:
        	break;
                default: printf("Opcao invalida");
    }
    	printf("Deseja alterar mais algum dado: \n");
        printf("1 - Sim \n");
        printf("2 - Nao \n");
        escolha = getint(); fflush(stdin);
    }
    fseek(arq, -sizeof(TCliente), 1);
    status = fwrite (&cliente,sizeof (TCliente), 1, arq);
    if (status != 1)
        printf ("Erro de gravacao \n");
    else
        printf ("Cliente alterado com sucesso \n");
}

void ExibirCliente (FILE * arq, char cpf []) {
	TCliente c;
	int pos, status;

	pos = BuscarCliente (arq, cpf);
	if (pos == -1)
		printf ("Cliente nao cadastrado \n");
	else if (pos == -2)
		printf ("Erro de leitura \n");
	else {
		fseek(arq, pos * sizeof (TCliente), 0);
		status = fread (&c,sizeof (TCliente), 1, arq);
		if (status != 1)
			printf ("Erro de leitura \n");
		else {
			printf ("Nome: %s \n", c.nome);
			printf ("Fone: %s \n", c.telefone);
			printf ("Email: %s \n", c.email);
		}
	}
}

void RemoverCliente (FILE * arq, char cpf []) {
	TCliente c;
	int pos, status;

	pos = BuscarCliente (arq, cpf);
	if (pos == -1)
		printf ("Cliente nao cadastrado \n");
	else if (pos == -2)
		printf ("Erro de leitura \n");
	else {
		fseek(arq, pos * sizeof (TCliente), 0);
		status = fread (&c,sizeof (TCliente), 1, arq);
		if (status != 1)
			printf ("Erro de leitura \n");
		else {
			c.status = 0;
			fseek(arq, -sizeof(TCliente), 1);
			status = fwrite (&c,sizeof (TCliente), 1, arq);
			if (status != 1)
				printf ("Erro de gravacao \n");
			else
				printf ("Cliente removido com sucesso \n");
		}
	}
}

int BuscarCliente (FILE * arq, char cpf [])
{
	int cont = -1, status;
		TCliente c;

		fseek (arq, 0, 0);
		while (1)
		{
			status = fread (&c, sizeof (TCliente), 1, arq);
			if (status != 1)
			{
				if (!feof(arq))
				    return -2; // erro de leitura
				else
					return -1; // nao achou
			}
			else
			{
				cont++;
				if (c.status == 1 && strcmp (c.cpf, cpf) == 0)
					return cont;
			}
		}
}

int ValidaCPF (char cpf[]){
	int icpf[12];
	int i = 0,soma=0,digito1,result1,result2,digito2,valor;

	do{
		if (isdigit(cpf[i]) == 0)
		{
			printf ("CPF Invalido. Informe uma sequencia de 11 numeros sem espacos entre eles.");
			system ("pause");
			return 0;
		}
		else
			i++;
	}while (i != 12);
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
		return 1;                       // retorna 1 para valido
	}
	else
	{
		printf("Problema com os digitos. CPF invalido.\n");
	}
	return 0;      // retorna 0 para cpf invalido
}

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


