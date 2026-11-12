#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "interface.h"

/* Descarta o resto da linha digitada (usado quando ela é longa demais) */
static void descartarLinha(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

/* Lê um inteiro entre min e max. Repete até a entrada ser válida. */
int lerInteiro(const char *msg, int min, int max) {
    char linha[64];
    char *fim;
    long valor;
    int valida;

    while (1) {
        printf("%s", msg);
        if (fgets(linha, sizeof(linha), stdin) == NULL) {
            printf("\nEntrada encerrada. Saindo do jogo...\n");
            exit(0);
        }

        valida = 1;
        if (strchr(linha, '\n') == NULL) {   /* linha maior que o vetor */
            descartarLinha();
            valida = 0;
        }

        if (valida) {
            valor = strtol(linha, &fim, 10);
            if (fim == linha) {
                valida = 0;                  /* nenhum número (ex.: "abc") */
            } else {
                while (*fim == ' ' || *fim == '\t') fim++;
                if (*fim != '\n') valida = 0;   /* sobrou lixo (ex.: "3abc") */
            }
        }

        if (valida && valor >= min && valor <= max) {
            return (int)valor;
        }
        printf("Entrada invalida! Digite um numero de %d a %d.\n", min, max);
    }
}

/* Mostra a mensagem e espera o jogador apertar Enter */
void pausar(const char *msg) {
    char linha[64];
    printf("%s", msg);
    if (fgets(linha, sizeof(linha), stdin) == NULL) {
        printf("\nEntrada encerrada. Saindo do jogo...\n");
        exit(0);
    }
    if (strchr(linha, '\n') == NULL) {
        descartarLinha();
    }
}

/* Delay portável usando só time.h (espera ocupada) */
void esperar(double segundos) {
    clock_t fim = clock() + (clock_t)(segundos * CLOCKS_PER_SEC);
    fflush(stdout);   /* garante que o texto apareça antes da espera */
    while (clock() < fim) { }
}