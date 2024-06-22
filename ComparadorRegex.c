#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

int comparador(char *argv[], char *linha){
    regex_t regex; // Estrutura para a expressão regular compilada

    // compila a expressão passada em argv[1] em caso de erro, a função retorna diferente de zero 
    if (regcomp(&regex, argv[1], REG_EXTENDED|REG_NOSUB|REG_ICASE) != 0) {
        fprintf(stderr, "Erro ao compilar a expressão regular\n");
        exit(1);
    }

    /* tenta comparar a Expressao Regular compilada (&reg) com a linha do entrada.txt
       se a função regexec retornar 0 casou, caso contrário não */
    if (regexec(&regex, linha, 0, (regmatch_t *)NULL, 0) == 0)
        puts(linha);
}


int main(int argc, char **argv)
{
    if (argc != 2) {
        printf("Uso: compara <ExpReg> \n");
        return 1;
    }

    FILE *arquivo = fopen("entrada.txt", "r");
    size_t tamanho_linha = 100; // Tamanho inicial da linha
    char *linha = malloc(tamanho_linha);

    if (!arquivo) {
        perror("entrada.txt");
        exit(1);
    }

    while (getline(&linha, &tamanho_linha, arquivo) > 0)
        comparador(argv, linha);

    if (linha)
        free(linha);

    fclose(arquivo);
    return 0;
}
