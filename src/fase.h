#ifndef FASE_H
#define FASE_H

#include "tipos.h"

void inicializarFases(Fase fases[]);
void mostrarMissao(const Fase *f, int numero);
int missaoCumprida(const Fase *f);
void avancarFase(int *faseAtual, int *posicao);

#endif