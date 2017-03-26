#include "HeaderCliente.h"
#include "HeaderPassagem.h"
#include "HeaderVoo.h"
#include "Validacoes.h"

void opcoesOrigem ()
{
    int i;
    char origens[9][100] = {"1- RECIFE","2 - SALVADOR","3 - SAO PAULO","4 - RIO DE JANEIRO","5 - CURITIBA","6 - PORTO ALEGRE","7 - NATAL","8 - MANAUS","9 - BELO HORIZONTE"};
    char origensEstado[9][10] = {"- PE","- BA","- SP","- RJ","- PR","- RS","- RN","- AM","- MG"};
    printf ("Opcoes de Origem: \n");
    for(i = 0; i < 9; i++)
        printf ("%s %s \n", origens[i], origensEstado[i]);
    printf ("\n");
}

void opcoesDestinos ()
{
    int i;
    char destinos[9][100] = {"1- RECIFE","2 - SALVADOR","3 - SAO PAULO","4 - RIO DE JANEIRO","5 - CURITIBA","6 - PORTO ALEGRE","7 - NATAL","8 - MANAUS","9 - BELO HORIZONTE"};
    char origensEstado[9][10] = {"- PE","- BA","- SP","- RJ","- PR","- RS","- RN","- AM","- MG"};
    printf ("Opcoes de Destino: \n");
    for(i = 0; i < 9; i++)
        printf ("%s %s \n", destinos[i], origensEstado[i]);
    printf ("\n");
}

int comparaHora_e_Data (char dia[], char mes[], char hora[], char min[])
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
	else if (mesRecebido == mesLocal)
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

int comparaHoraLocal (Horario horario)
{
    time_t tp;
    struct tm *local;
    Horario h;
    tp = time (NULL);
    int horaLocal, horaRecebido, minLocal, minRecebido;
    local = localtime (&tp);
    strftime(h.hora, sizeof(h.hora), "%H", local);
    strftime(h.min, sizeof(h.min), "%M", local);
	horaLocal = atoi (h.hora);
	horaRecebido = atoi (horario.hora);
	minLocal = atoi (h.min);
	minRecebido = atoi (horario.min);
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

int comparaDataLocal (Data data)
{
    Data d;
    time_t tp;
    struct tm *local;
    tp = time (NULL);
    int diaLocal, diaRecebido, mesLocal, mesRecebido;
    local = localtime (&tp);
    strftime(d.dia, sizeof(d.dia), "%d", local);
    strftime(d.mes, sizeof(d.mes), "%m", local);
    diaLocal = atoi (d.dia);
    diaRecebido = atoi (data.dia);
    mesLocal = atoi (d.mes);
	mesRecebido = atoi (data.mes);
	if (mesRecebido < mesLocal)
		return 0;
	else if (mesRecebido == mesLocal)
		{
		if (diaRecebido < diaLocal)
			return 0;
		else if (diaRecebido > diaLocal)
			return 1;
		else
			return 2;
		}
	else
		return 1;
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
		return 1;
	}
	else
	{
		printf("\nProblema com os digitos. CPF invalido.\n");
		system("pause");
	}
	return 0;
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
                validar = comparaHora_e_Data (v.dia, v.mes, v.hora, v.min);
                if (validar == 1)
                    return validar;
            }
        }
    }
    }while (pos != -2);
    return validar;
}

int validaDataCorreta(Data d){
	int diaAux,mesAux,quantDias, ano;
	int QuantDias1[12] = { 31,28,31,30,31,30,31,31,30,31,30,31};
	diaAux = atoi (d.dia);
	mesAux = atoi (d.mes);
	ano = bissexto(ANO);

	if (mesAux < 1 || mesAux > 12){
		return 0;
	}
	if (diaAux < 1 || diaAux > 31){
		return 0;
	}
	if (mesAux == 2){
		if (ano == 1)
			quantDias = 29;
		else
			quantDias = QuantDias1[mesAux-1];
		if (diaAux < 1 || diaAux > quantDias){
			return 0;
		}
	}
	else
	{
		quantDias = QuantDias1[mesAux-1];
		if (diaAux < 1 || diaAux > quantDias){
			return 0;
		}
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
	int aux, cont = 0, i;

	for (i = 0; i < 2; i++) {
		if (isdigit(d.dia[i]) == 0 && cont == 0){
			printf("\n1");
			return 0;
		}
		cont++;
	}
        i = 0;
        cont = 0;
	for (i = 0; i < 2; i++) {
		if (isdigit(d.mes[i]) == 0 && cont ==0){
			printf("\n2");
			return 0;
		}
		cont++;
	}
	aux = validaDataCorreta(d);
	if (aux == 0){
		printf("\n3\n");
		return 0;
	}
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

int validaCodReserva(char cod[]) {
	int i;

	for (i = 0; i < 5; i++) {
		if (isdigit(cod[i]) == 0) {
			return 0;
		}
	}
	return 1;
}
