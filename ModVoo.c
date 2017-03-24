#include "HeaderCliente.h"
#include "HeaderPassagem.h"
#include "HeaderVoo.h"

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
int RecebeCOD(char cod[]){

	int validar;
	char op;
	validar = ValidaCodVoo (cod);
	if (validar == 0)
	{
		printf("Codigo invalido, deseja tentar denovo? (S/N) \n");
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

int ValidaCodVoo(char cod[]) {
	int i;

	for (i = 0; i < 3; i++) {
		if (isalpha(cod[i]) == 0) {
			return 0;
		}
	}

	for (i = 3; i < 7; i++) {
		if (isdigit(cod[i]) == 0) {
			return 0;
		}
	}

	return 1;
}

int bissexto (int ano){
	int anoAux1, anoAux2;
	anoAux1 = ano%4;
	anoAux2 = ano%400;
	if (anoAux1 == 0){
		anoAux1 = ano%100;
		if (anoAux1 == 0)
			return 0;
		else
			return 1;
	}
	else if (anoAux2 == 0)
		return 1;
	return 0;
}

int validaDataCorreta(Data d){
	int diaAux,mesAux,quantDias, ano;
	int QuantDias1[12] = { 31,28,31,30,31,30,31,31,30,31,30,31};
        diaAux = atoi (d.dia);
        mesAux = atoi (d.mes);
	ano = bissexto(ANO);
	if (mesAux < 1 || mesAux > 12)
		return 0;
	if (diaAux < 1 || diaAux > 31)
		return 0;
	if (mesAux == 2){
		if (ano == 1)
			quantDias = 29;
		else
			quantDias = QuantDias1[mesAux-1];
		if (diaAux < 1 || diaAux > quantDias)
			return 0;
	}
	else
	{
		quantDias = QuantDias1[mesAux-1];
		if (diaAux < 1 || diaAux > quantDias)
			return 0;
	}
	return 1;
}

int validaHoraCorreta (Horario horario){
    int horaAux,minAux;
    horaAux = atoi (horario.hora);
    minAux = atoi (horario.min);
    if (horaAux < 0 || horaAux > 23)
        return 0;
    if (minAux < 0 || minAux > 59)
        return 0;
    return 1;
}

int ValidaData(Data d) {
	int i;

	for (i = 0; i < 2; i++) {
		if(d.dia[i] == '\0')
			return 1;
		if (isdigit(d.dia[i]) == 0)
			return 0;
	}
        i = 0;
	for (i = 0; i < 2; i++) {
		if(d.dia[i] == '\0')
			return 1;
		if (isdigit(d.mes[i]) == 0)
			return 0;

	}
	if (validaDataCorreta(d) == 0)
            return 0;
	return 1;
}




int ValidaHora(Horario horario) {
	int i;

	for (i = 0; i < 2; i++) {
		if (isdigit(horario.hora[i]) == 0) {
			return 0;
		}
	}
	for (i = 0; i < 2; i++) {
		if (isdigit(horario.min[i]) == 0) {
			return 0;
		}
	}
        if (validaHoraCorreta(horario) == 0)
            return 0;
	return 1;
}

/*while(i < 5)
        {
            if (j < 3 && i < 3)
            {
                if (j == 2){
                    hora[3] = '\0';
                    printf(":");
                    j = 0;
                }
                else{
                    hora[i] = getche();
                    j++;
                }
            }
            else
            {
                if (j == 2){
                    min[3] = '\0';
                    j = 0;
                }
                else{
                    min[i] = getche();
                    j++;
                }
            }
            i++;
        }   */

void CadastrarData (TVoo * v)
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
            		data.dia[2] = '\0';
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
        			data.mes[2] = '\0';
        	}
        	i++;
        }
        if (ValidaData(data) == 0 ){
            printf("Data invalida, digite novamente. \n");
            system("pause");
        }
        else{
            strcpy(v->dia, data.dia);
            strcpy(v->mes, data.mes);
        }
    } while (ValidaData(data) == 0);
}

void CadastrarHorario (Horario * h)
{
    int i, j;
    Horario horario;
    do
    {
        i = 0;
        j = 0;
        system("cls");
        printf("Digite o horario de partida: \n");
        printf("Formato hh/mm \n");
        while(i < 5)
        {
            if (j < 3 && i < 3)
            {
                if (j == 2){
                	horario.hora[3] = '\0';
                    printf(":");
                    j = 0;
                }
                else{
                	horario.hora[i] = getche();
                    j++;
                }
            }
            else
            {
                if (j == 2){
                	horario.min[3] = '\0';
                    j = 0;
                }
                else{
                	horario.min[i] = getche();
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
	Horario h;
	int aux, i, j, num1, num2, t = 0;
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
		CadastrarData(&v);
		CadastrarHorario(&h);
		strcpy(v.hora, h.hora);
		strcpy(v.min, h.min);
		v.poltronas = 36;
		for (i = 0; i < 6; i++)
                {
			for (j = 0; j < 6; j++) {
				v.mapaPoltronas[i][j] = 'o';
			}
		}
		printf("Digite o valor da passagem: \n");
		scanf("%f", &v.valor);

		v.status = 1;

	}

}

void ProcurarVoo (FILE * arq, int origem, int destino, Horario h)
{
    TVoo voo;
    int status, aux;
    char Locais[9][100] = {"RECIFE","SALVADOR","SAO PAULO","RIO DE JANEIRO","CURITIBA","PORTO ALEGRE","NATAL","MANAUS","BELO HORIZONTE"};
    fseek (arq, 0, 0);
    while (1)
    {
        status = fread (&voo, sizeof (TVoo), 1, arq);
        if (status != 1)
        {
            if (!feof(arq)){
                printf("Erro na leitura do arquivo");
                break; // erro de leitura
            }else
                printf("Nenhum voo encontrado"); // nao achou
        }
        else
        {
            do
            {
                if(strcmp(voo.destino,Locais[destino]) == 0 && strcmp(voo.origem,Locais[origem]) == 0  && strcmp(voo.hora,h.hora) == 0  && strcmp(voo.min,h.min) == 0)
                {
                    printf("Codigo do voo: %s\n", voo.codVoo);
                    printf("Horario do voo: %s:%s\n", voo.hora, voo.min);
                    printf("Cadeiras disponiveis nesse voo: %d", voo.poltronas);
                }
                aux = BuscarVoo(arq, voo.codVoo);
                if (aux < 0)
                    printf("Codigo nao registrado. \n");
                else
                {
                    fseek(arq, aux * sizeof (TVoo), 0);
                    status = fread (&voo,sizeof (TVoo), 1, arq);
                    if (status != 1)
                        printf ("Erro de leitura \n");
                    else {

                    }
                }
            }while (status != 1);
        }
    }


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
    if (aux < 0)
        printf("Codigo nao registrado. \n");
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
        		printf("Voo nao pode ser removido, existem poltronas ocupadas");
        	}
        }
    }

}

void menuProcurarVoo (FILE *arqPass, FILE *arqCliente,FILE * arqVoo ,char op)
{
	Horario h;
	int i = 0, data, num1, num2;
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
	do{
	CadastrarHorario(&h);
	data = ValidaHora(h);
	if (destino == origem){
        printf ("Destino nao pode ser o mesmo da Origem. \n");
	}
	else if (data == 0)
		printf ("Data invaldia \n");
	else
		if (op == '2')
			ProcurarVoo (arqVoo, num1, num2, h);
		else
			venderPassagem(arqPass, arqCliente, arqVoo, num1, num2, h);
	}while(data == 0);
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

