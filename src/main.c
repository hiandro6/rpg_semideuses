#include <stdio.h>
#include "personagem.h"
#include "dado.h"
#include "tabuleiro.h"

int main(void) {
    Personagem heroi;
    Casa tabuleiro[TAM_TABULEIRO];
    int posicao = 0;
    int passos;

    iniciarAleatorio();
    criarPersonagem(&heroi, FILHO_POSEIDON);
    inicializarTabuleiro(tabuleiro);

    mostrarPersonagem(&heroi);
    mostrarTabuleiro(tabuleiro, posicao);

    while (posicao < TAM_TABULEIRO - 1) {
        printf("Aperte Enter para lancar o d6...");
        getchar();

        passos = rolarDado(6);
        moverJogador(&posicao, passos);

        printf("Voce tirou %d! Foi para a casa %d (%s).\n",
               passos, posicao + 1, tabuleiro[posicao].nome);
        mostrarTabuleiro(tabuleiro, posicao);
    }

    printf("Chegou ao fim do tabuleiro!\n");
    return 0;
}