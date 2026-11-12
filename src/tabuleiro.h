#ifndef TABULEIRO_H
#define TABULEIRO_H

#include "tipos.h"

void inicializarTabuleiro(Casa tabuleiro[]);
void moverJogador(int *posicao, int passos);
void mostrarTabuleiro(const Casa tabuleiro[], int posicao);

#endif