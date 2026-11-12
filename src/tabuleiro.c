#include <stdio.h>
#include "tabuleiro.h"

/* Define o tipo e o nome de uma casa (função auxiliar, só deste arquivo) */
static void definirCasa(Casa *c, TipoCasa tipo, const char *nome) {
    c->tipo = tipo;
    c->nome = nome;
}

void inicializarTabuleiro(Casa tabuleiro[]) {
    definirCasa(&tabuleiro[0],  CASA_VAZIA,     "Inicio");
    definirCasa(&tabuleiro[1],  CASA_VAZIA,     "Vazia");
    definirCasa(&tabuleiro[2],  CASA_COMBATE,   "Combate");
    definirCasa(&tabuleiro[3],  CASA_TESOURO,   "Tesouro");
    definirCasa(&tabuleiro[4],  CASA_COMBATE,   "Combate");
    definirCasa(&tabuleiro[5],  CASA_CURA,      "Cura");
    definirCasa(&tabuleiro[6],  CASA_ARMADILHA, "Armadilha");
    definirCasa(&tabuleiro[7],  CASA_COMBATE,   "Combate");
    definirCasa(&tabuleiro[8],  CASA_VAZIA,     "Vazia");
    definirCasa(&tabuleiro[9],  CASA_TESOURO,   "Tesouro");
    definirCasa(&tabuleiro[10], CASA_MISSAO,    "Missao");
    definirCasa(&tabuleiro[11], CASA_COMBATE,   "Chefe / Fim");
}

/* Avança "passos" casas, sem ultrapassar a última */
void moverJogador(int *posicao, int passos) {
    *posicao += passos;
    if (*posicao > TAM_TABULEIRO - 1) {
        *posicao = TAM_TABULEIRO - 1;
    }
    if (*posicao < 0) {
        *posicao = 0;
    }
}

/* Desenha o tabuleiro e marca onde o herói está com [X] */
void mostrarTabuleiro(const Casa tabuleiro[], int posicao) {
    int i;
    printf("\n");
    for (i = 0; i < TAM_TABULEIRO; i++) {
        printf("%2d: %-12s %s\n", i + 1, tabuleiro[i].nome,
               (i == posicao) ? "[X]" : "");
    }
    printf("\n");
}