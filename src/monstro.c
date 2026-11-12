#include <math.h>
#include "monstro.h"
#include "dado.h"

/* Monstros base de cada fase (antes da escala).
   Ordem dos campos: nome, descricao, vida, ataque, defesa, nivel, xp.
   Os indices 0 a 2 sao monstros comuns; o ultimo indice e o chefe. */
static const Monstro base[NUM_FASES][MONSTROS_POR_FASE] = {
    { /* Fase 1: Labirinto de Creta */
        {"Harpia",       "Ave de garras afiadas que ronda os corredores", 25, 5, 1, 1, 20},
        {"Cao Infernal", "Fera de pelo negro e olhos em chamas",          35, 6, 2, 1, 25},
        {"Empusa",       "Demonio de uma perna de bronze que seduz e devora", 30, 6, 2, 1, 22},
        {"Minotauro",    "Guardiao do Labirinto, metade homem, metade touro", 55, 8, 3, 1, 50}
    },
    { /* Fase 2: Mar dos Monstros */
        {"Ciclope",      "Gigante de um olho so, arremessa rochas",       35, 6, 2, 1, 20},
        {"Hidra",        "Serpente de varias cabecas que se regeneram",   45, 7, 3, 1, 25},
        {"Sereia",       "Canto hipnotico que atrai marinheiros ao abismo", 40, 7, 2, 1, 22},
        {"Scylla",       "Monstro marinho de seis cabecas famintas",      60, 8, 4, 1, 50}
    },
    { /* Fase 3: Submundo */
        {"Furia",        "Espirito alado da vinganca",                    40, 7, 3, 1, 20},
        {"Quimera",      "Leao, cabra e serpente em um so corpo",         50, 8, 4, 1, 25},
        {"Espectro",     "Alma penada que arrasta os vivos para as trevas", 45, 8, 3, 1, 22},
        {"Cerbero",      "Cao de tres cabecas que guarda o Submundo",     65, 9, 5, 1, 50}
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

/* Sorteia um monstro comum que ainda nao apareceu nesta fase.
   O vetor "usado" pertence a Fase e e atualizado por ponteiro. */
void sortearMonstroComum(Monstro *m, int fase, double fator, int usado[]) {
    int disponiveis[MONSTROS_POR_FASE];
    int n = 0, i;

    for (i = 0; i < MONSTROS_POR_FASE - 1; i++) {   /* -1: o chefe fica de fora */
        if (!usado[i]) disponiveis[n++] = i;
    }
    if (n == 0) {   /* seguranca: se todos ja apareceram, reinicia a lista */
        for (i = 0; i < MONSTROS_POR_FASE - 1; i++) {
            usado[i] = 0;
            disponiveis[n++] = i;
        }
    }

    i = disponiveis[rolarDado(n) - 1];
    usado[i] = 1;
    criarMonstro(m, fase, i, fator);
}