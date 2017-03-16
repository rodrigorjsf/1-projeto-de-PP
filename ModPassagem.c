#include "HeaderPassagem.h"

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

void ConsultarPassagem (FILE * arqPass, FILE * arqVoo,char cpf [])
{
    int pos, posAux = -1,cont = 0;
    int voo, status, validar;
    TPass p;
    TVoo v;
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

