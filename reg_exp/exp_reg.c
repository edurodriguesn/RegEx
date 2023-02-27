/*  */

#include <stdio.h>
#include <string.h>
#include <strings.h>

void f_asterisco(char *cadeia, char *exp_reg, int tam)
{
    int i, j;

    strncat(cadeia, exp_reg, tam - 2); // não copia o elemento antes do simbolo

    int aux = 1;
    printf("\nCADEIAS\n");
    for (i = 0; i < 5; i++)
    {
        for (j = 0; j < aux; j++)
        {
            printf(cadeia);
            printf("\n");
            strncat(cadeia, &exp_reg[tam - 2], 1);
        }
    }
}

void f_acento(char *cadeia, char *exp_reg, int tam)
{
    int i, j;

    strncat(cadeia, exp_reg, tam - 2); // não podia o elemento antes do simbolo

    int aux = 1;
    printf("\nCADEIAS\n");
    for (i = 0; i < 5; i++)
    {
        for (j = 0; j < aux; j++)
        {
            printf(cadeia);
            printf("\n");
            strncat(cadeia, &exp_reg[tam - 3], 1);
        }
    }
}

void f_parentesis(char *exp_reg, int parentesis1, int parentesis2)
{

    char parte[10];
    int i, j = 0;
    for (i = 0; i < 10; i++)
    {
        parte[i] = ' ';
    }
    parte[0] = '\0';

    if ((exp_reg[parentesis2 + 1] == '*') || (exp_reg[parentesis2 + 1] == '^'))
    {
        parentesis2 = parentesis2 - parentesis1 - 1; //
        int aux = 1;

        printf("\nCADEIAS\n");
        for (i = 0; i < 5; i++)
        {
            for (j = 0; j < aux; j++)
            {
                strncat(parte, &exp_reg[parentesis1 + 1], parentesis2);
            }
            printf(parte);
            printf("\n");
        }
    }
}

void f_parentesis_ou(char *exp_reg, int amais, int mais, int parentesis1, int dmais, int parentesis2)
{
    int i, k, tam;
    int controle = 0;
    char metade1[10];
    char metade2[10];
    char n_exp_reg[10];
    char parte1[10];
    char parte2[10];
    i = 0;
    for (i = 0; i < 10; i++)
    {
        metade1[i] = ' ';
        metade2[i] = ' ';
        n_exp_reg[i] = ' ';
        parte1[i] = ' ';
        parte2[i] = ' ';
    }
    metade1[0] = '\0';
    metade2[0] = '\0';
    n_exp_reg[0] = '\0';
    parte1[0] = '\0';
    parte2[0] = '\0';

    k = parentesis2 + 1;
    strcat(n_exp_reg, &exp_reg[k]);
    tam = strlen(n_exp_reg);

    if (controle == 0)
    {
        amais = mais - parentesis1 - 1;
        strncat(metade1, &exp_reg[parentesis1 + 1], amais);
        strcat(parte1, metade1);

        if (n_exp_reg[tam - 1] == '*')
        {
            f_asterisco(parte1, n_exp_reg, tam);
        }
        else if (n_exp_reg[tam - 1] == '^')
        {
            f_acento(parte1, n_exp_reg, tam);
        }
    }
    controle++;

    if (controle == 1)
    {
        dmais = parentesis2 - mais - 1;
        strncat(metade2, &exp_reg[mais + 1], dmais);
        strcat(parte2, metade2);
        printf(parte2);

        if (n_exp_reg[tam - 1] == '*')
        {
            f_asterisco(parte2, n_exp_reg, tam);
        }
        else if (n_exp_reg[tam - 1] == '^')
        {
            f_acento(parte2, n_exp_reg, tam);
        }
    }
}

int main()
{

    int i;
    int parentesis1 = -1;
    int parentesis2;
    int mais = 0;
    int amais;
    int dmais;
    int asterisco = 0;
    int acento = 0;
    int plus = 0;

    char exp_reg[10];
    char cadeia[10];

    for (i = 0; i < 20; i++)
    {
        cadeia[i] = ' ';
    }
    cadeia[0] = '\0';

    FILE *arq = fopen("entrada.txt", "r"); // Leitura da expressao regular a partir do arquivo "expressao.txt"
    if (arq == NULL)
        printf("Arquivo não encontrado!\n");

    while (!feof(arq))
    {
        fscanf(arq, "%s", &exp_reg);
    }
    fclose(arq);
    int tam = strlen(exp_reg);

    printf("EXPRESSAO REGULAR\n");
    printf(exp_reg);

    for (i = 0; i < tam; i++) // Laço que verifica a presença de simbolos '(',')','+','^','*', na cadeia e guarda suas posições
    {
        if (exp_reg[i] == '(')
        {
            parentesis1 = i;
        }
        else if (exp_reg[i] == ')')
        {
            parentesis2 = i;
        }
        else if (exp_reg[i] == '+')
        {
            mais = i;
        }
        else if (exp_reg[i] == '*')
        {
            if ((exp_reg[i - 1] != ')') && (parentesis1 == -1))
            {
                asterisco = i;
            }
        }
        else if ((exp_reg[i] == '^') || (exp_reg[i + 1] == '+'))
        {
            if ((exp_reg[i - 1] != ')') && (parentesis1 == -1))
            {
                acento = i;
                plus = i + 1;
            }
        }
    }

    if (asterisco != 0) // Condição que verifica a presença de uma expressao com ocorrencia de *
    {
        f_asterisco(cadeia, exp_reg, tam);
    }
    else if ((parentesis1 == -1) && (acento != 0)) // Condição que verifica a presença de uma expressao com ocorrencia de ^+
    {
        f_acento(cadeia, exp_reg, tam);
    }
    else if ((parentesis1 != -1) && ((mais == 0) || (plus != 0))) // Condição que verifica a presença de uma expressao com ocorrencia de ()
    {
        f_parentesis(exp_reg, parentesis1, parentesis2);
    }

    else if ((parentesis1 != -1) && (mais != 0)) // tiver parentesis e o mais
    {
        f_parentesis_ou(exp_reg, amais, mais, parentesis1, dmais, parentesis2);
    }
    return 0;
}
