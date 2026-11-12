#include <stdio.h>
#include "fase.h"

static void definirFase(Fase *f, const char *nome, const char *historia,
                        const char *missao, const char *item, double fator) {
    f->nome = nome;
    f->historia = historia;
    f->missao = missao;
    f->item = item;
    f->fator = fator;
    f->itemObtido = 0;
    f->chefeDerrotado = 0;
}

void inicializarFases(Fase fases[]) {
    definirFase(&fases[0], "Labirinto de Creta",
        "Os corredores de pedra escondem feras famintas e armadilhas antigas.",
        "Pegar o Fio de Ariadne e derrotar o Minotauro.",
        "Fio de Ariadne", 1.0);
    definirFase(&fases[1], "Mar dos Monstros",
        "Ondas negras cercam ilhas malditas onde criaturas dominam as aguas.",
        "Recuperar o Velocino de Ouro e derrotar Scylla.",
        "Velocino de Ouro", 1.4);
    definirFase(&fases[2], "Submundo",
        "O reino de Hades guarda o Raio de Zeus, o artefato roubado do Olimpo.",
        "Resgatar o Raio de Zeus e derrotar Cerbero.",
        "Raio de Zeus", 1.8);
}

void mostrarMissao(const Fase *f, int numero) {
    printf("\n======================================\n");
    printf(" FASE %d: %s\n", numero, f->nome);
    printf("======================================\n");
    printf("%s\n", f->historia);
    printf("MISSAO: %s\n", f->missao);
}

/* A missao so esta cumprida quando o chefe da fase foi derrotado */
int missaoCumprida(const Fase *f) {
    return f->chefeDerrotado;
}

/* Passa para a proxima fase e volta o heroi para o inicio do tabuleiro */
void avancarFase(int *faseAtual, int *posicao) {
    (*faseAtual)++;
    *posicao = 0;
}