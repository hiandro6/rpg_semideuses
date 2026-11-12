#include <math.h>
#include "monstro.h"
#include "dado.h"

/* Monstros base de cada fase (antes da escala).
   Ordem dos campos: nome, descricao, vida, ataque, defesa, nivel, xp.
   O indice 2 de cada fase e o chefe. */
static const Monstro base[NUM_FASES][MONSTROS_POR_FASE] = {
    { /* Fase 1: Labirinto de Creta */
        {"Harpia",      "Ave de garras afiadas que ronda os corredores", 25, 5, 1, 1, 20},
        {"Cao Infernal","Fera de pelo negro e olhos em chamas",          35, 6, 2, 1, 25},
        {"Minotauro",   "Guardiao do Labirinto, metade homem, metade touro", 55, 8, 3, 1, 50}
    },
    { /* Fase 2: Mar dos Monstros */
        {"Ciclope",     "Gigante de um olho so, arremessa rochas",       35, 6, 2, 1, 20},
        {"Hidra",       "Serpente de varias cabecas que se regeneram",   45, 7, 3, 1, 25},
        {"Scylla",      "Monstro marinho de seis cabecas famintas",      60, 8, 4, 1, 50}
    },
    { /* Fase 3: Submundo */
        {"Furia",       "Espirito alado da vinganca",                    40, 7, 3, 1, 20},
        {"Quimera",     "Leao, cabra e serpente em um so corpo",         50, 8, 4, 1, 25},
        {"Cerbero",     "Cao de tres cabecas que guarda o Submundo",     65, 9, 5, 1, 50}
    }
};

/* Copia o monstro base para *m e aplica o fator da fase (arredondando para cima) */
void criarMonstro(Monstro *m, int fase, int indice, double fator) {
    *m = base[fase][indice];
    m->vida         = (int)ceil(m->vida * fator);
    m->ataque       = (int)ceil(m->ataque * fator);
    m->defesa       = (int)ceil(m->defesa * fator);
    m->xpRecompensa = (int)ceil(m->xpRecompensa * fator);
    m->nivel        = fase + 1;
}

/* Sorteia um dos 2 monstros comuns da fase (o chefe fica de fora) */
void sortearMonstroComum(Monstro *m, int fase, double fator) {
    criarMonstro(m, fase, rolarDado(2) - 1, fator);
}