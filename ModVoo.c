#include "HeaderVoo.h"

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

void AlterarValorPassagem (FILE * arq, char cod[]){
	TVoo v;
	int aux, i, j, status;
	char data[9], horario[5];
    int i, validar,sair = 0;
    char cpf[12],op;
    do
    {
    	do{
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
    		do{
    			op = getche();
    			if (op != 78 && op != 83 && op != 110 && op != 115)
    			{
    				printf("Opcao invalida. Deseja tentar denovo? (S/N) \n");
    			}
    			else if (op == 78 || op == 110){
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
	else {
		fseek(arq, aux * sizeof (TVoo), 0);
		status = fread (&v,sizeof (TVoo), 1, arq);
		if (status != 1)
			printf ("Erro de leitura \n");
		else {
			printf("Digite o novo valor da passagem: ");
			scan("%f", &v.valor);
		}
	}
	fseek(arq, -sizeof(TVoo), 1);
	status = fwrite (&v,sizeof (TVoo), 1, arq);
	if (status != 1)
		printf ("Erro de gravacao \n");
	else
		printf ("Cliente alterado com sucesso \n");
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

int ValidaData(char data[]) {
	int i;

	for (i = 0; i < 2; i++) {
		if (isdigit(data[i]) == 0) {
			return 0;
		}
	}

	if (data[i] != '/') {
		return 0;
	}

	for (i = 3; i < 5; i++) {
		if (isdigit(data[i]) == 0) {
			return 0;
		}
	}

	if (data[i] != '/') {
		return 0;
	}

	if (data[6] != '2')
		return 0;
	if (data[7] != '0')
		return 0;
	if (data[8] != '1')
		return 0;
	if (data[9] != '7')
		return 0;

	return 1;
}

int ValidaHora(char hora[]) {
	int i;

	for (i = 0; i < 2; i++) {
		if (isdigit(hora[i]) == 0) {
			return 0;
		}
	}

	if (hora[i] != ':') {
		return 0;
	}

	for (i = 3; i < 5; i++) {
		if (isdigit(hora[i]) == 0) {
			return 0;
		}
	}

	return 1;
}
char * gerarCodigo (){
	int n, i;
	char letras[26] = {'A', 'B', 'C', 'D', 'E','F', 'G', 'H', 'I','J', 'K', 'L', 'M','N', 'O', 'P', 'Q','R', 'S', 'T', 'U','V', 'X', 'Z', 'W','Y'};
	char aux, cod[8];
	for(i = 0;i < 3;i++){
		n = rand() % 26;
		cod[i] = letras[n];
	}
	for(i = 3;i < 8;i++){
		aux = (rand() % 9) + 48;  //transforma o numero aleatorio int em char?
		cod[i] = aux;
	}
	i++;
	cod[i] = '\0';
	return cod;
}

void CadastrarVoo(FILE * arq) {
	TVoo v;
	int aux, i, j;
	char cod[8], data[9], horario[5];
    /*int i, validar,sair = 0;

    char cpf[12],op;
    do
    {
    	do{
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
    		do{
    			op = getche();
    			if (op != 78 && op != 83 && op != 110 && op != 115)
    			{
    				printf("Opcao invalida. Deseja tentar denovo? (S/N) \n");
    			}
    			else if (op == 78 || op == 110){
    				sair = 1;
    				break;
    			}
    			else
    				break;
    		}while(1);
    	}
    }while (validar == 0 || sair != 1);
    if (sair == 1)
    	return;*/
	cod = gerarCodigo ();
	aux = BuscarVoo(arq, cod);
	if (aux < 0) {
		printf("Codigo de voo ja existente. \n");
	}
	else {
		strcpy(v.codVoo, cod);

		printf("Digite a origem: \n");
		fgets(v.origem, sizeof(v.destino), stdin);
		fflush(stdin);

		printf("Digite o destino: \n");
		fgets(v.destino, sizeof(v.destino), stdin);
		fflush(stdin);

		do {
			printf("Digite a data de partida: \n");
			fgets(data, sizeof(data), stdin);
			fflush(stdin);
			if (ValidaData(data) == 0)
				printf("Data invalida, digite novamente. \n");
			else
				strcpy(v.data, data);
		} while (ValidaData(data) == 0);

		do {
			printf("Digite o horario de partida: \n");
			fgets(horario, sizeof(horario), stdin);
			fflush(stdin);
			if (ValidaHora(horario) == 0)
				printf("Horario invalido, digite novamente. \n");
			else
				stcpy(v.horario, horario);
		} while (ValidaHora(horario) == 0);

		v.poltronas = 36;

		for (i = 0; i < 6; i++) {
			for (j = 0; j < 6; j++) {
				v.mapaPoltronas[i][j] = 'o';
			}
		}

		printf("Digite o valor da passagem: \n");
		scanf("%f", &v.valor);

		v.status = 1;

	}

}

