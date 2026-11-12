#ifndef PERSONAGEM_H
#define PERSONAGEM_H

#include "tipos.h"

void criarPersonagem(Personagem *p, ClassePersonagem classe);
void mostrarPersonagem(const Personagem *p);

void ganharXP(Personagem *p, int xp);
void subirNivel(Personagem *p);
void aplicarBonusAleatorio(Personagem *p);
void curar(Personagem *p, int quantidade);

#endif