#include "HeaderCliente.h"
#include "HeaderPassagem.h"
#include "HeaderVoo.h"

int BuscarPassagem (FILE * arq, char cpf [], int pos)
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
void opcoesOrigem ()
{
    int i;
    char origens[10][100] = {"RECIFE","SALVADOR","SAO PAULO","RIO DE JANEIRO","CURITIBA","PORTO ALEGRE","NATAL","MANAUS","BELO HORIZONTE","ARACAJU"};
    char origensEstado[10][10] = {"- PE","- BA","- SP","- RJ","- PR","- RS","- RN","- AM","- MG","- SE"};
    printf ("Opcoes de Origem: \n");
    for(i = 0; i < 10; i++)
        printf ("%s %s \n", origens[i], origensEstado[i]);
    printf ("\n");
}

int validaOrigem(char Origem[])
{
	int i;
	char origens[10][100] = {"RECIFE","SALVADOR","SAO PAULO","RIO DE JANEIRO","CURITIBA","PORTO ALEGRE","NATAL","MANAUS","BELO HORIZONTE","ARACAJU"};
	char aux [100];
	aux = gerarMaiusculo(Origem);
	if (strlen(aux) == 0)
		return 0;
	for (i = 0; i < 10; i++){
		if (strcmp (origens[i],aux) != 0){
			if (i == 9)
				return 0;
		}
		else
			return 1;
	}
	return 1;
}

void opcoesDestinos ()
{
    int i;
    char destinos[10][100] = {"RECIFE","SALVADOR","SAO PAULO","RIO DE JANEIRO","CURITIBA","PORTO ALEGRE","NATAL","MANAUS","BELO HORIZONTE","ARACAJU"};
    char origensEstado[10][10] = {"- PE","- BA","- SP","- RJ","- PR","- RS","- RN","- AM","- MG","- SE"};
    printf ("Opcoes de Destino: \n");
    for(i = 0; i < 10; i++)
        printf ("%s %s \n", destinos[i], origensEstado[i]);
    printf ("\n");
}

int validaDestino (char Destino[])
{
	int i;
	char destinos[10][100] = {"RECIFE","SALVADOR","SAO PAULO","RIO DE JANEIRO","CURITIBA","PORTO ALEGRE","NATAL","MANAUS","BELO HORIZONTE","ARACAJU"};
	char aux [100];
	aux = gerarMaiusculo(Destino);
	if (strlen(aux) == 0)
		return 0;
	for (i = 0; i < 10; i++){
		if (strcmp (destinos[i],aux) != 0){
			if (i == 9)
				return 0;
		}
		else
			return 1;
	}
	return 1;
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
    else if (pos == -2){
        printf ("Erro de leitura \n");
        return;
    }
    do{
    pos = BuscarPassagem (arqPass, cpf, posAux);
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

