#include <stdio.h>
#include <string.h>

void f_asterisco(char *cadeia_saida, char *expressao_regular, int tamanho_exp_reg) {
    strncat(cadeia_saida, expressao_regular, tamanho_exp_reg - 2);

    printf("\nCADEIAS\n");
    for (int i = 0; i < 5; i++) {
        printf("%s\n", cadeia_saida);
        strncat(cadeia_saida, expressao_regular + tamanho_exp_reg - 2, 1);
    }
}

void f_acento(char *cadeia_saida, char *expressao_regular, int tamanho_exp_reg) {
    strncat(cadeia_saida, expressao_regular, tamanho_exp_reg - 2);

    printf("\nCADEIAS\n");
    for (int i = 0; i < 5; i++) {
        printf("%s\n", cadeia_saida);
        strncat(cadeia_saida, expressao_regular + tamanho_exp_reg - 3, 1);
    }
}

void f_parentesis(char *expressao_regular, int pos_parentesis_aberto, int pos_parentesis_fechado) {
    char parte_da_string[20] = "";

    if (expressao_regular[pos_parentesis_fechado + 1] == '*' || expressao_regular[pos_parentesis_fechado + 1] == '^') {
        int auxiliar = 1;

        printf("\nCADEIAS\n");
        for (int i = 0; i < 5; i++) {
            strncat(parte_da_string, expressao_regular + pos_parentesis_aberto + 1, pos_parentesis_fechado - pos_parentesis_aberto - 1);
            printf("%s\n", parte_da_string);
        }
    }
}

void f_parentesis_ou(char *expressao_regular, int pos_amais, int pos_mais, int pos_parentesis_aberto, int pos_dmais, int pos_parentesis_fechado) {
    char metade_esquerda[20] = "", metade_direita[20] = "", nova_exp_reg[20] = "", parte1_string[20] = "", parte2_string[20] = "";

    strncpy(nova_exp_reg, expressao_regular + pos_parentesis_fechado + 1, strlen(expressao_regular) - pos_parentesis_fechado);

    if (pos_amais == pos_mais - pos_parentesis_aberto - 1) {
        strncat(metade_esquerda, expressao_regular + pos_parentesis_aberto + 1, pos_amais);
        strncat(parte1_string, metade_esquerda, sizeof(parte1_string) - strlen(parte1_string) - 1);
    }

    if (nova_exp_reg[strlen(nova_exp_reg) - 1] == '*') {
        f_asterisco(parte1_string, nova_exp_reg, strlen(nova_exp_reg));
    } else if (nova_exp_reg[strlen(nova_exp_reg) - 1] == '^') {
        f_acento(parte1_string, nova_exp_reg, strlen(nova_exp_reg));
    }
}


int main() {
    char exp_reg_input[100] = "", cadeia_saida[100] = "";
    int pos_parentesis_aberto = -1, pos_parentesis_fechado = -1, pos_mais = 0, pos_amais = 0, pos_dmais = 0, pos_asterisco = 0, pos_acento = 0, pos_plus = 0;

    FILE *arquivo = fopen("entrada.txt", "r");
    if (arquivo == NULL) {
        printf("Arquivo não encontrado!\n");
        return 1;
    }

    if (fgets(exp_reg_input, sizeof(exp_reg_input), arquivo) == NULL) {
        printf("Erro ao ler o arquivo!\n");
        fclose(arquivo);
        return 1;
    }

    fclose(arquivo);

    printf("EXPRESSAO REGULAR\n%s\n", exp_reg_input);

    for (int i = 0; i < strlen(exp_reg_input); i++) {
        if (exp_reg_input[i] == '(') {
            pos_parentesis_aberto = i;
        } else if (exp_reg_input[i] == ')') {
            pos_parentesis_fechado = i;
        } else if (exp_reg_input[i] == '+') {
            pos_mais = i;
        } else if (exp_reg_input[i] == '*') {
            if (i > 0 && exp_reg_input[i - 1] != ')') {
                pos_asterisco = i;
            }
        } else if ((exp_reg_input[i] == '^') || (exp_reg_input[i + 1] == '+')) {
            if (i > 0 && exp_reg_input[i - 1] != ')') {
                pos_acento = i;
                pos_plus = i + 1;
            }
        }
    }

    if (pos_asterisco != 0) {
        f_asterisco(cadeia_saida, exp_reg_input, strlen(exp_reg_input));
    } else if (pos_parentesis_aberto == -1 && pos_acento != 0) {
        f_acento(cadeia_saida, exp_reg_input, strlen(exp_reg_input));
    } else if (pos_parentesis_aberto != -1 && (pos_mais == 0 || pos_plus != 0)) {
        f_parentesis(exp_reg_input, pos_parentesis_aberto, pos_parentesis_fechado);
    } else if (pos_parentesis_aberto != -1 && pos_mais != 0) {
        f_parentesis_ou(exp_reg_input, pos_amais, pos_mais, pos_parentesis_aberto, pos_dmais, pos_parentesis_fechado);
    }

    return 0;
}


