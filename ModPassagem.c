#include "HeaderCliente.h"
#include "HeaderPassagem.h"
#include "HeaderVoo.h"

int BuscarPassagemCPF (FILE * arq, char cpf [], int pos)
{
    int cont = -1, status;
    TPass p;
    if (pos > -1){
        cont = pos;
        fseek (arq, pos * sizeof (TPass), 0);
    }
    else
        fseek (arq, 0, 0);
    while (1)
    {
        status = fread (&p, sizeof (TPass), 1, arq);
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
            if (p.status == 1 && strcmp (p.cpf, cpf) == 0)
                return cont;
        }
    }
}
int BuscarPassagemCodReserva (FILE * arq, char cod [])
{
	int cont = -1, status;
		TPass p;

		fseek (arq, 0, 0);
		while (1)
		{
			status = fread (&p, sizeof (TPass), 1, arq);
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
				if (p.status == 1 && strcmp (p.codReserva, cod) == 0)
					return cont;
			}
		}
}

int validaCodReserva(char cod[]) {
	int i;

	for (i = 0; i < strlen(cod); i++) {
		if (cod[i] == '\n') {
			return 1;
		}
		if (isdigit(cod[i]) == 0) {
			return 0;
		}
	}
	return 1;
}
void gerarCodigoReserva (TPass * p)
{
	int i;
	char aux, cod[6];
	for(i = 0;i < 5;i++){
		aux = (rand() % 9) + 48;
		cod[i] = aux;
	}
	cod[i] = '\0';
	strcpy (p->codReserva,cod);
}

void opcoesOrigem ()
{
    int i;
    char origens[9][100] = {"1- RECIFE","2 - SALVADOR","3 - SAO PAULO","4 - RIO DE JANEIRO","5 - CURITIBA","6 - PORTO ALEGRE","7 - NATAL","8 - MANAUS","9 - BELO HORIZONTE"};
    char origensEstado[9][10] = {"- PE","- BA","- SP","- RJ","- PR","- RS","- RN","- AM","- MG"};
    printf ("Opcoes de Origem: \n");
    for(i = 0; i < 10; i++)
        printf ("%s %s \n", origens[i], origensEstado[i]);
    printf ("\n");
}

void opcoesDestinos ()
{
    int i;
    char destinos[9][100] = {"1- RECIFE","2 - SALVADOR","3 - SAO PAULO","4 - RIO DE JANEIRO","5 - CURITIBA","6 - PORTO ALEGRE","7 - NATAL","8 - MANAUS","9 - BELO HORIZONTE"};
    char origensEstado[9][10] = {"- PE","- BA","- SP","- RJ","- PR","- RS","- RN","- AM","- MG"};
    printf ("Opcoes de Destino: \n");
    for(i = 0; i < 10; i++)
        printf ("%s %s \n", destinos[i], origensEstado[i]);
    printf ("\n");
}

int procurarVooPassagem(FILE *arqVoo, int origem, int destino, char hora[], char min[]) {
	TVoo v;
	int cont = -1;
	char Locais[9][100] = {"RECIFE","SALVADOR","AO PAULO","RIO DE JANEIRO","CURITIBA","PORTO ALEGRE","NATAL","MANAUS","BELO HORIZONTE"};

	fseek(arqVoo, 0, 0);
	while (1) {
		if (fread(&v, sizeof(TVoo), 1, arqVoo) != 1) {
			if (!feof(arqVoo)) {
				return -2;
			}
			else {
				return -1;
			}
		}
		else {
			cont++;
			if (v.status == 1 && strcmp(v.origem, Locais[origem]) == 0 && strcmp(v.destino, Locais[destino]) == 0 && strcmp(v.hora, hora) == 0 && strcmp(v.min, min) == 0) {
				if (v.poltronas > 0) {
					return cont;
				}
				else {
					printf("Nao ha poltronas disponiveis \n");
					return -3;
				}
			}
		}
	}
}


void ConsultarPassagem (FILE * arqCliente, FILE * arqPass, FILE * arqVoo,char cpf [])
{
    int pos, posAux = -1,cont = 0;
    int voo, status, validar, c;
    TPass p;
    TVoo v;
    c = BuscarCliente (arqCliente,cpf);
    if (c == -1){
        printf ("Cliente nao cadastrado. \n");
        return;
    }
    else if (c == -2){
        printf ("Erro de leitura \n");
        return;
    }
    do{
    pos = BuscarPassagemCPF (arqPass, cpf, posAux);
    posAux = pos;
    if (pos == -1)
        printf ("Total de %d Passagem(ens). \n", cont);
    else if (pos == -2)
        printf ("Erro de leitura \n");
    else {
        fseek(arqPass, pos * sizeof (TPass), 0);
        status = fread (&p,sizeof (TPass), 1, arqPass);
        if (status != 1)
            printf ("Erro de leitura \n");
        else {
            voo = BuscarVoo(arqVoo, p.codVoo);
            if (voo == -1)
                printf ("Voo nao cadastrado. \n");
            else if (voo == -2)
                printf ("Erro de leitura \n");
            else
            {
                fseek(arqVoo, voo * sizeof (TVoo), 0);
                status = fread (&v,sizeof (TVoo), 1, arqVoo);
                validar = comparaHora (v.dia, v.mes, v.hora, v.min);
                if (validar == 1){
                    printf ("Codigo do Voo: %s \n", v.codVoo);
                    printf ("Data do Voo: %s/%s/2017 \n", v.dia,v.mes);
                    printf ("Horario: %s:%s \n", v.hora, v.min);
                    printf ("Origem: %s \n", v.origem);
                    printf ("Destino: %s \n", v.destino);
                    printf ("Valor: %f \n\n", v.valor);
                }

            }
        }
    }
    cont++;
    }while (pos == -1);
}

void ImagemVoo(char voo[6][6]) {
	printf("             ()              \n");
	printf("            /  \\            \n");
	printf("           /    \\           \n");
	printf("          /      \\          \n");
	printf("         /        \\         \n");
	printf("        /          \\        \n");
	printf("       /            \\       \n");
	printf("      |  A  B  C  D  E  F  | \n");
	printf("_____J|1 %c %c %c %c %c %c |J____________        \n", voo[0][0], voo[0][1], voo[0][2], voo[0][3], voo[0][4], voo[0][5]);
	printf("     A|2 %c %c %c %c %c %c |A             \\     \n", voo[1][0], voo[1][1], voo[1][2], voo[1][3], voo[1][4], voo[1][5]);
	printf("     N|3 %c %c %c %c %c %c |N              \\    \n", voo[2][0], voo[2][1], voo[2][2], voo[2][3], voo[2][4], voo[2][5]);
	printf("_____E|4 %c %c %c %c %c %c |E_______________\\   \n", voo[3][0], voo[3][1], voo[3][2], voo[3][3], voo[3][4], voo[3][5]);
	printf("     L|5 %c %c %c %c %c %c |L                    \n", voo[4][0], voo[4][1], voo[4][2], voo[4][3], voo[4][4], voo[4][5]);
	printf("     A|6 %c %c %c %c %c %c |A                    \n", voo[5][0], voo[5][1], voo[5][2], voo[5][3], voo[5][4], voo[5][5]);
	printf("     /                \\     \n");
	printf("    /__________________\\    \n");
	printf("                             \n");
	printf("                             \n");
}

void preencherMatriz(FILE *arqVoo, char matriz[6][6], int posi) {
	TVoo voo;
	int i, j;

	fseek(arqVoo, posi * sizeof(TVoo), 0);
	if (fread(&voo, sizeof(TVoo), 1, arqVoo) != 1) {
		printf("Erro ao ler \n");
	}
	else {
		for (i = 0; i < 6; i++) {
			for (j = 0; j < 6; j++) {
				matriz[i][j] = voo.mapaPoltronas[i][j];
			}
		}

	}

}

int confirmaCompra(FILE *arqVoo, int i, int j, int posi) {
	TVoo voo;

	if (i < 0 || i > 5){
		printf("Opcao invalida. Escolha entre 1 a 6. \n");
		return 0;
	}
	fseek(arqVoo, posi * sizeof(TVoo), 0);
	if (fread(&voo, sizeof(TVoo), 1, arqVoo) != 1) {
		printf("Erro ao ler \n");
	}
	else {
		if (voo.mapaPoltronas[i][j] == 'o') {
			voo.mapaPoltronas[i][j] = 'x';
			voo.poltronas = voo.poltronas - 1;
		}
		else {
			printf("Poltrona ja ocupada \n");
			return 0;
		}
	}

	fseek(arqVoo, -sizeof(TVoo), 1);
	if (fwrite(&voo, sizeof(TVoo), 1, arqVoo) != 1) {
		printf("Erro ao gravar \n");
	}
	else {
		printf("Compra confirmada \n");
		return 1;
	}
	return 0;
}

float valorPassagem(FILE *arqVoo, int posi) {
	TVoo voo;

	fseek(arqVoo, posi * sizeof(TVoo), 0);
	if (fread(&voo, sizeof(TVoo), 1, arqVoo) != 1) {
		printf("Erro ao ler \n");
	}
	else {
		return voo.valor;
	}
	return 0;
}

void liberarPoltrona(char matriz[6][6], int i, int j) {
	matriz[i][j] = 'o';
}

void acharCodigoVoo(FILE *arqVoo, int posi, char * cod) {
	TVoo voo;
	fseek(arqVoo, posi * sizeof(TVoo), 0);
	if (fread(&voo, sizeof(TVoo), 1, arqVoo) != 1) {
		printf("Erro ao ler \n");
	}
	else {
		strcpy (cod, voo.codVoo);
	}
}

void venderPassagem(FILE *arqPass, FILE *arqCliente, FILE *arqVoo, int origem, int destino, Horario h) {
	TPass passagem;
	int i, posi, num, conf = 1 ,aux, auxCod;
	char auxMapa[6][6], op, auxCpf[11], cod [8];
	char Locais[10][100] = {"RECIFE","SALVADOR","AO PAULO","RIO DE JANEIRO","CURITIBA","PORTO ALEGRE","NATAL","MANAUS","BELO HORIZONTE","ARACAJU"};
	srand((unsigned)time(NULL));

	posi = procurarVooPassagem(arqVoo, origem, destino, h.hora, h.min);
	if (posi < 0) {
		printf("Voo nao encontrado ou nao existem poltronas disponiveis \n");
	}
	else {
		fseek(arqPass, 0, 2);
		do{
			i = 0;
			system ("cls");
			printf ("Informe o CPF do Passageiro: ");
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
			return;
		else
		{
			if (BuscarCliente(arqCliente, passagem.cpf) < 0) {
				printf("Cliente nao cadastrado \n");
				return;
			}
			else
				strcpy(passagem.cpf, auxCpf);
		}
		acharCodigoVoo(arqVoo, posi, cod);
		strcpy(passagem.codVoo, cod);

		preencherMatriz(arqVoo, auxMapa, posi); ///////////////
		printf("Lugares disponiveis \n");
		ImagemVoo(auxMapa);

		do {
			do {
				printf("Digite a letra do seu acento: \n");
				printf("(A / B / C / D / E / F) \n");
				printf("'S' - Sair da passagem de passagens \n");
				printf("Digite: ");
				op = getchar();
				fflush(stdin);
				op = tolower(op);
				switch (op) {
				case 'a':
					printf("Digite o numero do seu acento: ");
					scanf("%d", &num);
					conf = confirmaCompra(arqVoo, num - 1, 0, posi);
					break;
				case 'b':
					printf("Digite o numero do seu acento: ");
					scanf("%d", &num);
					conf = confirmaCompra(arqVoo, num - 1, 1, posi);
					break;
				case 'c':
					printf("Digite o numero do seu acento: ");
					scanf("%d", &num);
					conf = confirmaCompra(arqVoo, num - 1, 2, posi);
					break;
				case 'd':
					printf("Digite o numero do seu acento: ");
					scanf("%d", &num);
					conf = confirmaCompra(arqVoo, num - 1, 3, posi);
					break;
				case 'e':
					printf("Digite o numero do seu acento: ");
					scanf("%d", &num);
					conf = confirmaCompra(arqVoo, num - 1, 4, posi);
					break;
				case 'f':
					printf("Digite o numero do seu acento: ");
					scanf("%d", &num);
					conf = confirmaCompra(arqVoo, num - 1, 5, posi);
					break;
				case 's':
					break;
				default:
					printf("Opcao invalida \n");
				}
			} while (conf == 0);
			if (conf == 1 && op != 's')
				break;
		} while (op != 's');
		op = toupper(op);
		passagem.poltrona[0] = op;
		passagem.poltrona[1] = num + 48;
		passagem.poltrona[2] = '\0';

		gerarCodigoReserva(&passagem);
		auxCod = BuscarPassagemCodReserva(arqPass, passagem.codReserva);
		if (auxCod > -1){
		    do{
		        gerarCodigoReserva(&passagem);
		        auxCod = BuscarPassagemCodReserva(arqPass, passagem.codReserva);
            }while (auxCod > -1);
	    }
		printf("Seu codigo da reserva eh: %s \n", passagem.codReserva);
		passagem.status = 1;

		printf("----------BOLETO---------- \n");
		printf("-------------------------- \n");
		printf("--Informacoes da reserva: \n");
		printf("--Origem: %s", Locais[origem]);
		printf("--Destino: %s", Locais[destino]);
		printf("--Data do voo: %s:%s \n", h.hora, h.min);
		printf("--Acento: %c %d \n", op, num);
		printf("--Codigo da reserva: %s \n", passagem.codReserva);
		printf("--Valor: %f \n", valorPassagem(arqVoo, posi));
		printf("-------------------------- \n");
		printf("-------------------------- \n");

		if (fwrite(&passagem, sizeof(TPass), 1, arqPass) != 1) {
			printf("Erro ao gravar \n");
		}
		else {
			printf("Passagem vendida com sucesso \n");
		}

	}
}



void cancelarPassagem(FILE *arqPass, FILE *arqVoo, char codReserva[]) {
	TPass passagem;
	TVoo voo;
	Data d;
	char op, num[2];
	int pos1, pos2, i, diaAtual, diaPass, subDia;
	time_t tp;
	struct tm *local;
	tp = time (NULL);
	local = localtime (&tp);
	strftime(d.dia, sizeof(d.dia), "%d", local);
	strftime(d.mes, sizeof(d.mes), "%m", local);
	diaAtual = atoi(d.dia);

	fseek(arqPass, 0, 0);
	pos1 = BuscarPassagemCodReserva (arqPass, codReserva);
	if (pos1 == -1)
		printf ("Passagem nao cadastrada \n");
	else if (pos1 == -2)
		printf ("Erro de leitura \n");
	else {
		fseek(arqPass, pos1 * sizeof (TPass), 0);
		fread (&passagem,sizeof (TPass), 1, arqPass);
		if(passagem.status == 1 && strcmp(passagem.codReserva,codReserva) == 0) {
			fseek(arqVoo, 0, 0);
			pos2 = BuscarVoo (arqVoo, passagem.codVoo);
				if (pos2 == -1)
					printf ("Voo nao cadastrado \n");
				else if (pos2 == -2)
					printf ("Erro de leitura \n");
				else {
					fseek(arqVoo, pos2 * sizeof (TVoo), 0);
					fread (&voo, sizeof(TVoo), 1, arqVoo);
					diaPass = atoi(voo.dia);
					subDia = diaAtual/diaPass;
					if (subDia < 2){
						printf("Cancelamento negado. Cancelamento so pode ser feito com ate dois dias de antecedencia. \n");
						return;
					}
					else{
						printf("-----Documento de Credito----- \n");
						printf("Informacoes do cancelamento: \n");
						printf("Cpf: %s ", passagem.cpf);
						printf("Cod Voo: %s \n", passagem.codVoo);
						if(voo.status == 1 && strcmp(voo.codVoo, passagem.codVoo) == 0) {
							op = passagem.poltrona[0];
							num[0] = passagem.poltrona[1];
							op = tolower(op);
							i = atoi(num);
							if(op == 'a') {
								liberarPoltrona(voo.mapaPoltronas, i - 1, 0);
							}
							else if(op == 'b') {
								liberarPoltrona(voo.mapaPoltronas, i - 1, 1);
							}
							else if(op == 'c') {
								liberarPoltrona(voo.mapaPoltronas, i - 1, 2);
							}
							else if(op == 'd') {
								liberarPoltrona(voo.mapaPoltronas, i - 1, 3);
							}
							else if(op == 'e') {
								liberarPoltrona(voo.mapaPoltronas, i - 1, 4);
							}
							else if(op == 'f') {
								liberarPoltrona(voo.mapaPoltronas, i - 1, 5);
							}
							else {
								printf("Houve algum erro \n");
							}
							printf("Metade do valor da compra: %.2f \n", voo.valor/2);
							printf("------------------------------ \n");

							voo.poltronas = voo.poltronas + 1;
							passagem.status = 0;

							fseek(arqPass, -sizeof(TPass), 1);
							if(fwrite(&passagem, sizeof(TPass), 1, arqPass) != 1) {
								printf("Erro ao gravar \n");
							}
							else {
								printf("Voo cancelado com sucesso \n");
							}

							fseek(arqVoo, -sizeof(TVoo), 1);
							if(fwrite(&voo, sizeof(TVoo), 1, arqVoo) != 1) {
								printf("Erro ao gravar \n");
							}
							else {
								printf("Poltrona liberada com sucesso \n");
							}
							return;
						}
					}
				}
		}

	}
}

void consultarPassageirosVoo(FILE *arqPass, FILE *arqCliente, char codVoo[]) {
	TPass passagem;
	TCliente cliente;

	fseek(arqPass, 0, 0);
	while(1) {
		if(fread(&passagem, sizeof(TPass), 1, arqPass) != 1) {
			if(!feof(arqPass)) {
				printf("Erro ao ler \n");
				return;
			}
			else {
				printf("Fim \n");
				return;
			}
		}
		else {
			if(passagem.status == 1 && strcmp(passagem.codVoo, codVoo) == 0) {
				fseek(arqCliente, 0, 0);
				if(fread(&cliente, sizeof(TCliente), 1, arqCliente) != 1) {
					if(!feof(arqCliente)) {
						printf("Erro ao ler \n");
						return;
					}
					else {
						printf("Nao achou \n");
						return;
					}
				}
				else {
					if(cliente.status == 1 && strcmp(cliente.cpf, passagem.cpf) == 0) {
						printf("--------------- \n");
						printf("Cpf: %s", cliente.cpf);
						printf("Nome: %s", cliente.nome);
						printf("Poltrona: %s \n", passagem.poltrona);
						printf("--------------- \n");
					}
				}

			}
		}
	}

}
void MenuPassagem (FILE * arqPassagem, FILE * arqVoo,FILE * arqCliente, char op)
{
	char auxCpf[12], codVooAux[8], Reserva[6];
	int i, aux;
	if (op == '1')
		menuProcurarVoo (arqPassagem,arqCliente,arqVoo,op);
	else if (op == '2')
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
				ConsultarPassagem (arqCliente, arqPassagem, arqVoo, auxCpf);
	}
	else if (op == '3')
	{
		do
		{
			i = 0;
			system ("cls");
			printf ("Informe o Codigo de reserva: ");
			while(i < 5){
				codVooAux[i] = getche();
				if (i == 4)
					Reserva[i+1] = '\0';
				i++;
			}
		}while (i < 5);
		if (validaCodReserva(Reserva) == 0)
			printf ("Codigo invalido. \n");
		else
			cancelarPassagem(arqPassagem ,arqVoo, Reserva);
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
			consultarPassageirosVoo (arqPassagem, arqCliente, codVooAux);
	}
}

