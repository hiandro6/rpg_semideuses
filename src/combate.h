#ifndef COMBATE_H
#define COMBATE_H

#include "tipos.h"

void receberDano(Personagem *p, int dano);
void danoNoMonstro(Monstro *m, int dano);
int calcularAtaque(const Personagem *p);
int calcularDano(int ataque, int defesa);
ResultadoCombate combate(Personagem *p, Monstro *m);

#endif