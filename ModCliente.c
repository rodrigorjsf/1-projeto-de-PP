#include "HeaderCliente.h"
#include "HeaderPassagem.h"
#include "HeaderVoo.h"

int comparaHora (char dia[], char mes[], char hora[], char min[])
{
    Data d;
    time_t tp;
    struct tm *local;
    Horario h;
    tp = time (NULL);
    int diaLocal, diaRecebido, mesLocal, mesRecebido;
    int horaLocal, horaRecebido, minLocal, minRecebido;
    local = localtime (&tp);
    strftime(d.dia, sizeof(d.dia), "%d", local);
    strftime(d.mes, sizeof(d.mes), "%m", local);
    strftime(h.hora, sizeof(h.hora), "%H", local);
    strftime(h.min, sizeof(h.min), "%M", local);
    diaLocal = atoi (d.dia);
    diaRecebido = atoi (dia);
    mesLocal = atoi (d.mes);
	mesRecebido = atoi (mes);
	horaLocal = atoi (h.hora);
	horaRecebido = atoi (hora);
	minLocal = atoi (h.min);
	minRecebido = atoi (min);
	if (mesRecebido < mesLocal)
		return 0;
	else if (mesRecebido == mesLocal)    //mes igual
		{
		if (diaRecebido < diaLocal)
			return 0;
		else if (diaRecebido == diaLocal)
		{
			if(horaRecebido < horaLocal)
				return 0;
			else if (horaRecebido == horaLocal)
			{
				if (minRecebido < minLocal)
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
    /*if (strcmp (mes, d.mes) < 0)
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
        return 1; */
}
void gerarMaiusculo (char nome[], TCliente * c)
{
	char maiusculo[100];
	int i;
	for(i=0; nome[i]!= '\0'; i++){
		if (isalpha (nome[i]) != 0)
			maiusculo[i] = toupper(nome[i]);
		else if (nome[i+1] != 32)
				maiusculo[i] = nome[i];
		}
	maiusculo[i] = '\0';
	strcpy (c->nome,maiusculo);
}

int RecebeCPF(char cpf[]){

	int validar;
	char op;
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
	int aux, i = 0,soma=0,digito1,result1,result2,digito2,valor;
	aux = strlen (cpf);
	do{
		if (isdigit(cpf[i]) == 0)
		{
			if(i == aux && cpf[i] == '\0')
				break;
			else
			{
			printf ("\n %d", i);
			printf ("\nCPF Invalido. \nInforme uma sequencia de 11 numeros sem espacos entre eles.");
			system ("pause");
			return 0;
			}
		}
		else
			i++;
	}while (i != aux+1);
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
	if((digito1==icpf[9]) && (digito2==icpf[10]))
	{
		printf("\nCPF VALIDADO.\n");
		system ("pause");

		return 1;
	}
	else
	{
		printf("Problema com os digitos. CPF invalido.\n");
		system ("pause");
	}
	return 0;
}

int validaNome(char nome[]) {
	int i;

	for (i = 0; i < strlen(nome); i++) {
		if (nome[i] == '\n') {
			return 1;
		}
		if (isalpha(nome[i]) == 0) {
			if (isspace(nome[i]) == 0)
				return 0;
		}
	}
	return 1;
}

int validaTelefone(char telefone[]) {
	int i;

	for (i = 0; i < strlen(telefone); i++) {
		if (telefone[i] == '\n') {
			return 1;
		}
		if (isdigit(telefone[i]) == 0) {
			return 0;
		}
	}
	return 1;
}

int validaEmail(char email[]) {
	int i, j = 0;

	for (i = 0; i < strlen(email); i++) {
		if (email[i] == '\n') {
			return 1;
		}
		if (isalnum(email[i]) == 0) {
			if (email[i] != '.') {
				if (email[i] == '@') {
					j++;
				}
				if (j > 1) {
					return 0;
				}
				if (email[i] != '@') {//!arroba
					return 0;
				}
			}
		}
	}

	if (j == 0)
		return 0;

	return 1;
}

int validaRemocao (FILE * arqPass, FILE * arqVoo,char cpf[])
{
    int pos, posAux = -1;
    int voo, status, validar = 0;
    TPass p;
    TVoo v;
    do{
    pos = BuscarPassagemCPF (arqPass, cpf, posAux);
    posAux = pos;
    if (pos == -1)
        return validar;
    else if (pos == -2)
        printf ("Erro de leitura \n");
    else 
    {
        fseek(arqPass, pos * sizeof (TPass), 0);
        status = fread (&p,sizeof (TPass), 1, arqPass);
        if (status != 1)
            printf ("Erro de leitura \n");
        else {
            voo = BuscarVoo(arqVoo, p.codVoo);
            if (voo == -1)
                return validar;
            else if (voo == -2)
                printf ("Erro de leitura \n");
            else
            {                
                fseek(arqVoo, voo * sizeof (TVoo), 0);
                status = fread (&v,sizeof (TVoo), 1, arqVoo);
                validar = comparaHora (v.dia, v.mes, v.hora, v.min);  
                if (validar == 1)
                    return validar;                       
            }
        }
    }
    }while (pos != -2);
    return validar;
}



void CadastrarNome (TCliente * c)
{
	char nome [100];
	int i, aux;
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
		aux = validaNome(nome);
		if (aux == 1){
			gerarMaiusculo(nome, c);
			strcpy(c->nome, nome);
		}
		else{
			printf("Nome invalido. Por favor, inserir nome valido. \n");
			system("pause");
		}
	}while (aux == 0);
}

void CadastrarTelefone (TCliente * c)
{
	char tel[12];
	int i, aux;
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
		aux = validaTelefone(tel);
		if (aux == 1)
			strcpy(c->telefone, tel);
		else{
			printf("Telefone invalido. Por favor, inserir numero valido. \n");
			system("pause");
		}
	}while (aux == 0);
}

void CadastrarEmail (TCliente * c)
{
	char email[100];
	int i, aux;
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
		aux = validaEmail(email);
		if (aux == 1)
			strcpy(c->email, email);
		else{
			printf("E-Mail invalido. Por favor, inserir e-mail valido. \n");
			system("pause");
		}
	}while(aux == 0);
}

void CadastrarCliente (FILE * arq, char cpf [])
{
	TCliente cliente;
	int aux;

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
    do{
    	printf("Escolha o que deseja altrar: ");
    	printf ("1 - Alterar nome \n");
    	printf ("2 - Alterar email \n");
    	printf ("3 - Alterar telefpne \n");
    	printf ("4 - Sair \n");
    	printf ("informe a opcao: ");
    	op = getchar (); fflush (stdin);
    	switch (op) {
    	case '1':
    		CadastrarNome (&cliente);
    		break;
        case '2':
        	CadastrarEmail (&cliente);
        	break;
        case '3':
        	CadastrarTelefone (&cliente);
        	break;
        case '4':
        	break;
                default: printf("Opcao invalida");
    	}
    }while(op != '4');
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

void RemoverCliente (FILE * arqPass, FILE * arqVoo,FILE * arq, char cpf []) {
	TCliente c;
	int pos, status, valida;

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
                    valida = validaRemocao (arqPass,arqVoo,cpf);
                    if (valida == 1)
                        printf ("Nao e possivel excluir esse cliente no momento. Ele ainda possui reseva para voos futuros. \n");
                    else
                    {
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
}

void MenuCliente (FILE * arqPassagem, FILE * arqVoo,FILE * arqCliente, char op)
{
	char auxCpf[12];
	int i, aux;
	if (op == '1')
	{
		do{
			i = 0;
			system ("cls");
			printf ("Informe o CPF do Cliente: ");
			while(i < 11){
				auxCpf[i] = getche();
				if (i == 2)
					printf (".");
				if (i == 5)
					printf (".");
				if (i == 8)
					printf ("-");
				if (i == 10)
					auxCpf[i+1] = '\0';
				i++;
			}
			aux = RecebeCPF(auxCpf);
		}while (aux == 0);
		if (aux == 2)
			return;
		else
			CadastrarCliente (arqCliente, auxCpf);
	}
	else if (op == '2')
	{
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
				i++;
			}
			aux = RecebeCPF(auxCpf);
		}while (aux == 0);
		if (aux == 2)
			return;
		else
			AlterarCliente (arqCliente, auxCpf);
	}
	else if (op == '3')
	{
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
				i++;
			}
			aux = RecebeCPF(auxCpf);
		}while (aux == 0);
		if (aux == 2)
			return;
		else
			ExibirCliente (arqCliente, auxCpf);
	}
	else
	{
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
				i++;
			}
			aux = RecebeCPF(auxCpf);
		}while (aux == 0);
		if (aux == 2)
			return;
		else
			RemoverCliente (arqPassagem,arqVoo,arqCliente, auxCpf);
	}
}




