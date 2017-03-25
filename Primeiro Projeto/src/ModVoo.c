#include "HeaderCliente.h"
#include "HeaderPassagem.h"
#include "HeaderVoo.h"
#include "Validacoes.h"

/*char * gerarCodigo ()
{
	int n, i;
	char letras[26] = {'A', 'B', 'C', 'D', 'E','F', 'G', 'H', 'I','J', 'K', 'L', 'M','N', 'O', 'P', 'Q','R', 'S', 'T', 'U','V', 'X', 'Z', 'W','Y'};
	char aux, * cod;
        cod = (char *)malloc(8 * sizeof(char));
	for(i = 0;i < 3;i++){
		n = rand() % 26;
		cod[i] = letras[n];
	}
	for(i = 3;i < 8;i++){
		aux = (rand() % 9) + 48;
		cod[i] = aux;
	}
	i++;
	cod[i] = '\0';
	return cod;
}*/

void gerarCodigo (TVoo * v)
{
	int n, i;
	char letras[26] = {'A', 'B', 'C', 'D', 'E','F', 'G', 'H', 'I','J', 'K', 'L', 'M','N', 'O', 'P', 'Q','R', 'S', 'T', 'U','V', 'X', 'Z', 'W','Y'};
	char aux, cod[8];
	for(i = 0;i < 3;i++){
		n = rand() % 26;
		cod[i] = letras[n];
	}
	for(i = 3;i < 7;i++){
		aux = (rand() % 9) + 48;
		cod[i] = aux;
	}
	i++;
	cod[i] = '\0';
	strcpy (v->codVoo,cod);
}

int BuscarVoo(FILE * arq, char cod[]) {
	int cont = -1, status;
	TVoo v;
	fseek(arq, 0, 0);
	while (1) {
		status = fread(&v, sizeof(TVoo), 1, arq);
		if (status != 1) {
			if (!feof(arq))
				return -2;
			else
				return -1;
		}
		else {
			cont++;
			if (v.status == 1 && strcmp(v.codVoo, cod) == 0)
				return cont;
		}
	}

}
int BuscarVooPorData(FILE * arq, Data d) {
	int cont = -1, status;
	TVoo v;
	fseek(arq, 0, 0);
	while (1) {
		status = fread(&v, sizeof(TVoo), 1, arq);
		if (status != 1) {
			if (!feof(arq))
				return -2;
			else
				return -1;
		}
		else {
			cont++;
			if (v.status == 1 && strcmp(v.dia, d.dia) == 0 && strcmp(v.mes, d.mes) == 0)
				return cont;
		}
	}

}
int RecebeCOD(char cod[]){

	int validar;
	char op;
	validar = ValidaCodVoo (cod);
	if (validar == 0)
	{
		printf("\nCodigo invalido, deseja tentar denovo? (S/N) \n");
		do{
			op = getche();
			if (op != 78 && op != 83 && op != 110 && op != 115)
			{
				printf("Opcao invalida. deseja tentar denovo? (S/N) \n");
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

void CadastrarData (Data * d)
{
    int i;
    Data data;
    do
    {
        i = 0;
        system("cls");
        printf("Digite o dia da partida: ");
        while (i < 2)
        {

            if (i == 0)
            	data.dia[i] = getche();
            else{
            	data.dia[i] = getche();
            	if (data.dia[i] == 13)
            	{
            		data.dia[i] = '\0';
            		break;
            	}
            	else
            		data.dia[i+1] = '\0';
            }
            i++;
        }
        i = 0;
        system("cls");
        printf("Digite o mes da partida: ");
        while (i < 2)
        {
        	if (i == 0)
        		data.mes[i] = getche();
        	else{
        		data.mes[i] = getche();
        		if (data.mes[i] == 13)
        		{
        			data.mes[i] = '\0';
        			break;
        		}
        		else
        			data.mes[i+1] = '\0';
        	}
        	i++;
        }
        if (ValidaData(data) == 0 )
        {
            printf("Data invalida, digite novamente. \n");
            system("pause");
        }
        else if (comparaDataLocal (data) == 0)
        {
        	printf("Data invalida, digite novamente. \n");
        	system("pause");
        }
        else
        {
            strcpy(d->dia, data.dia);
            strcpy(d->mes, data.mes);
        }
    } while (ValidaData(data) == 0 || comparaDataLocal (data) == 0);
}

void CadastrarHorarioNaEstrutura (TVoo * v)
{
    int i, j;
    Horario horario;
    Data data;
    strcpy(data.mes, v->mes);
    strcpy(data.dia, v->dia);
    do
    {
        i = 0;
        j = 0;
        system("cls");
        printf("Digite o horario de partida: \n");
        while(i < 4)
        {
            if (j < 2 && i < 2)
            {
            	if (j == 1){
            		horario.hora[j] = getche();
            		horario.hora[j+1] = '\0';
            		printf(":");
            		j = 0;
            	}
            	else{
            		horario.hora[j] = getche();
            		j++;
            	}
            }
            else
            {
            	if (j == 1){
            		horario.min[j] = getche();
            		horario.min[j+1] = '\0';
            		j = 0;
            	}
            	else{
            		horario.min[j] = getche();
            		j++;
            	}
            }
            i++;
        }
        if (ValidaHora(horario) == 0){
            printf("Horario invalido, digite novamente. \n");
            system("pause");
        }
        else if (comparaHoraLocal (horario) == 0 && comparaDataLocal (data) == 2)
        {
        	printf("\n Horario invalido, digite novamente. \n");
        	system("pause");
        }
        else{
            strcpy(v->hora, horario.hora);
            strcpy(v->min, horario.min);
        }
    } while (ValidaHora(horario) == 0 || (comparaHoraLocal (horario) == 0 && comparaDataLocal (data) == 2));
}

void CadastrarHorario (Horario * h)
{
    int i, j;
    Horario  horario;
    do
    {
        i = 0;
        j = 0;
        printf("Digite o horario de partida: \n");
        while(i < 4)
        {
            if (j < 2 && i < 2)
            {
            	if (j == 1){
            		horario.hora[j] = getche();
            		horario.hora[j+1] = '\0';
            		printf(":");
            		j = 0;
            	}
            	else{
            		horario.hora[j] = getche();
            		j++;
            	}
            }
            else
            {
            	if (j == 1){
            		horario.min[j] = getche();
            		horario.min[j+1] = '\0';
            		j = 0;
            	}
            	else{
            		horario.min[j] = getche();
            		j++;
            	}
            }
            i++;
        }
        if (ValidaHora(horario) == 0){
            printf("Horario invalido, digite novamente. \n");
            system("pause");
        }
        else{
            strcpy(h->hora, horario.hora);
            strcpy(h->min, horario.min);
        }
    } while (ValidaHora(horario) == 0);
}

void CadastrarVoo(FILE * arq)
{
	TVoo v;
	Data d;
	int status, aux, i, j, num1, num2, t = 0;
	char origemAux[2], destinoAux[2];
	char Locais[9][100] = {"RECIFE","SALVADOR","SAO PAULO","RIO DE JANEIRO","CURITIBA","PORTO ALEGRE","NATAL","MANAUS","BELO HORIZONTE"};
	gerarCodigo(&v);
	aux = BuscarVoo(arq, v.codVoo);
	if (aux > -1){
	    do{
	        gerarCodigo(&v);
	        aux = BuscarVoo(arq, v.codVoo);
        }while (aux > -1);
	}
	else {
		do
		{
			do
			{
				system("cls");
				printf ("Voo de codigo: %s \n", v.codVoo);
				opcoesOrigem();
				printf ("Informe a Origem: ");
				origemAux [t] = getche();
				origemAux [t+1] = '\0';
				//scanf("%c" ,&origem); fflush(stdin);
				if (origemAux[t] < '1' || origemAux[t] > '9'){
					printf ("\nOpcao invalida. \n");
					getch();
				}
			}while (origemAux[t] < '1' || origemAux[t] > '9');
			do
			{
				system("cls");
				printf ("Voo de codigo: %s \n", v.codVoo);
				opcoesDestinos ();
				printf ("Informe o Destino: ");
				destinoAux [t] = getche();
				destinoAux [t+1] = '\0';
				//scanf("%c" ,&destino); fflush(stdin);
				if (destinoAux[t] < '1' || destinoAux[t] > '9'){
					printf ("\nOpcao invalida. \n");
					getch();
				}
			}while (destinoAux[t] < '1' || destinoAux[t] > '9');
			num1 = atoi(origemAux);
			num2 = atoi(destinoAux);
			if (num1 == num2){
				printf ("\nDestino nao pode ser o mesmo da Origem. \n");
				getch();
			}
		}while (num1 == num2);
        strcpy (v.origem, Locais[num1-1]);
		strcpy (v.destino, Locais[num2-1]);
		CadastrarData(&d);
		strcpy(v.dia, d.dia);
		strcpy(v.mes, d.mes);
		CadastrarHorarioNaEstrutura(&v);
		printf ("\nVoo de codigo: %s \n", v.codVoo);
		printf ("Voo de %s para %s.\n", v.origem, v.destino);
		v.poltronas = 36;
		for (i = 0; i < 6; i++)
                {
			for (j = 0; j < 6; j++) {
				v.mapaPoltronas[i][j] = 'o';
			}
		}
		printf("\nDigite o valor da passagem: \n");
		scanf("%f", &v.valor);

		v.status = 1;
		status = fwrite(&v,sizeof(TVoo),1,arq);
		if (status != 1)
			printf ("\nErro de gravacao \n");
		else
			printf ("\nVoo cadastrado com sucesso \n");
		system("pause");

	}

}

int BuscarTodosVoos (FILE * arq, Data d , int pos)
{
    int cont = -1, status;
    TVoo v;
    if (pos > -1){
    	cont = pos;
    	pos++;
        fseek (arq, pos * sizeof (TVoo), 0);
    }
    else{
        fseek (arq, 0, 0);
    }
    while (1)
    {
        status = fread (&v, sizeof (TVoo), 1, arq);
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
            if (v.status == 1 && strcmp (v.mes, d.mes) == 0 && strcmp (v.dia, d.dia) == 0)
            	return cont;
        }
    }
}

void ProcurarVoo (FILE * arq, int origem, int destino, Data d)
{
    TVoo voo;
    int pos, posAux = -1, cont = 0;
    char Locais[9][100] = {"RECIFE","SALVADOR","SAO PAULO","RIO DE JANEIRO","CURITIBA","PORTO ALEGRE","NATAL","MANAUS","BELO HORIZONTE"};
    fseek (arq, 0, 0);
    printf("\n%s para %s\n", Locais[origem-1], Locais[destino-1]);
    do
    {
    	pos = BuscarTodosVoos (arq, d,posAux);
    	posAux = pos;
    	if (pos == -1)
    		printf ("\nExistem %d voo(s) com essas caracteristicas.\n", cont);
    	else if (pos == -2)
    		printf ("Erro de leitura \n");
    	else
    	{
    		fseek(arq, pos * sizeof (TVoo), 0);
    		fread (&voo, sizeof (TVoo), 1, arq);
    		if(strcmp(voo.destino,Locais[destino-1]) == 0 && strcmp(voo.origem,Locais[origem-1]) == 0  && strcmp(voo.dia,d.dia) == 0  && strcmp(voo.mes,d.mes) == 0 && voo.poltronas != 0)
    		{
    			printf("\nCodigo do voo: %s\n", voo.codVoo);
    			printf("Horario do voo: %s:%s\n", voo.hora, voo.min);
    			printf("Cadeiras disponiveis nesse voo: %d\n", voo.poltronas);

    			cont++;
    		}
    		else
    		{
    			printf("\nO Voo de codigo %s nao possui poltronas disponiveis.\n", voo.codVoo);
    			cont++;
    		}
    	}
    }while (pos != -1);
    system("pause");
}



int RecebeCodVoo(char cod[]){

	int validar;
	char op;
	validar = ValidaCPF (cod);
	if (validar == 0)
	{
		printf("Codigo invalido, deseja tentar denovo? (S/N) \n");
		do{
			op = getche();
			if (op != 78 && op != 83 && op != 110 && op != 115)
			{
				printf("Opcao invalida. Deseja tentar novamente? (S/N) \n");
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

void AlterarValorPassagem (FILE * arq, char cod[])
{
	TVoo v;
	int aux, i, status;
    int validar,sair = 0;
    char cpf[12],op;
    do
    {
    	do
        {
    		i = 0;
    		system ("cls");
    		printf ("Informe o Codigo do Voo: ");
    		while(i <= 7){
    			cpf[i] = getche();
    			if (i == 7)
    				cpf[8] = '\0';
    		}
    	}while (strlen(cpf) != 7);
    	i = 0;                          ////////
    	validar = ValidaCodVoo (cod);
    	if (validar == 0)
    	{
    		printf("Codigo invalido, deseja tentar denovo? (S/N) \n");
    		do
                {
    			op = getche();
    			if (op != 78 && op != 83 && op != 110 && op != 115)
    			{
    				printf("Opcao invalida. Deseja tentar denovo? (S/N) \n");
    			}
    			else if (op == 78 || op == 110)
                        {
    				sair = 1;
    				break;
    			}
    			else
    				break;
    		}while(1);
    	}
    }while (validar == 0 || sair != 1);
    if (sair == 1)
    	return;
	aux = BuscarVoo(arq, cod);
	if (aux < 0)
		printf("Codigo nao registrado. \n");
	else
        {
		fseek(arq, aux * sizeof (TVoo), 0);
		status = fread (&v,sizeof (TVoo), 1, arq);
		if (status != 1)
			printf ("Erro de leitura \n");
		else
                {
			printf("Digite o novo valor da passagem: ");
			scanf("%f", &v.valor);
		}
	}
	fseek(arq, -sizeof(TVoo), 1);
	status = fwrite (&v,sizeof (TVoo), 1, arq);
	if (status != 1)
		printf ("Erro de gravacao \n");
	else
		printf ("Cliente alterado com sucesso \n");
}



void CancelarVoo (FILE * arq, char cod[]){
    TVoo voo;
    int status, aux;
    aux = BuscarVoo(arq, cod);
    if (aux < 0){
        printf("Codigo nao registrado. \n");
        system("pause");
    }
    else {
        fseek(arq, aux * sizeof (TVoo), 0);
        status = fread (&voo,sizeof (TVoo), 1, arq);
        if (status != 1)
            printf ("Erro de leitura \n");
        else {
        	if (voo.poltronas == 36) {
        		voo.status = 0;
        		fseek(arq, -sizeof(TVoo), 1);
        		if (fwrite(&voo, sizeof(TVoo), 1, arq) != 1) {
        			printf("Erro ao gravar \n");
        		}
        		else {
        			printf("Voo removido \n");
        		}
        	}
        	else {
        		printf("\nVoo nao pode ser removido, existem poltronas ocupadas");
        		system("pause");
        	}
        }
    }

}

void menuProcurarVoo (FILE *arqPass, FILE *arqCliente,FILE * arqVoo ,char op)
{
	Data d;
	int i = 0, num1, num2;
	char origem[2], destino[2];
	do
	{
	    do
	    {
	        system("cls");
	        opcoesOrigem();
            printf ("Informe a Origem: ");
            origem [i] = getche();
            origem [i+1] = '\0';
		    //scanf("%c" ,&origem); fflush(stdin);
		    if (origem[i] < '1' || origem[i] > '9'){
			   printf ("\nOpcao invalida. \n");
			   getch();
		    }
	    }while (origem[i] < '1' || origem[i] > '9');

	    do
	    {
	        system("cls");
	        opcoesDestinos ();
	        printf ("Informe o Destino: ");
	        destino [i] = getche();
            destino [i+1] = '\0';
	        //scanf("%c" ,&destino); fflush(stdin);
	        if (destino[i] < '1' || destino[i] > '9'){
                printf ("\nOpcao invalida. \n");
                getch();
	        }
        }while (destino[i] < '1' || destino[i] > '9');
        num1 = atoi(origem);
        num2 = atoi(destino);
        if (num1 == num2){
            printf ("\nDestino nao pode ser o mesmo da Origem. \n");
            getch();
        }
    }while (num1 == num2);
	CadastrarData(&d);
	if (destino == origem){
        printf ("Destino nao pode ser o mesmo da Origem. \n");
	}
	else
		if (op == '2')
			ProcurarVoo (arqVoo, num1, num2, d);
		else
			venderPassagem(arqPass, arqCliente, arqVoo, num1, num2, d);
}


void MenuVOO (FILE *arqPass, FILE *arqCliente,FILE * arqVoo ,char op)
{
	char codVooAux[8];
	int i, aux;
	if (op == '1')
	{
		CadastrarVoo (arqVoo);
	}
	else if (op == '2')
	{
		menuProcurarVoo (arqPass,arqCliente,arqVoo,op);
	}
	else if (op == '3')
	{
		do
		{
			i = 0;
			system ("cls");
			printf ("Informe o Codigo do Voo: ");
			while(i < 7){
				codVooAux[i] = getche();
				if (isalpha(codVooAux[i]) != 0)
					codVooAux[i] = toupper(codVooAux[i]);
				if (i == 6)
					codVooAux[i+1] = '\0';
				i++;
			}
			aux = RecebeCOD(codVooAux);
		}while (aux == 0);
		if (aux == 2)
			return;
		else
			AlterarValorPassagem (arqVoo, codVooAux);
	}
	else
	{
		do
		{
			i = 0;
			system ("cls");
			printf ("Informe o Codigo do Voo: ");
			while(i < 7){
				codVooAux[i] = getche();
				if (isalpha(codVooAux[i]) != 0)
					codVooAux[i] = toupper(codVooAux[i]);
				if (i == 6)
					codVooAux[i+1] = '\0';
				i++;
			}
			aux = RecebeCOD(codVooAux);
		}while (aux == 0);
		if (aux == 2)
			return;
		else
			CancelarVoo (arqVoo, codVooAux);
	}
}

