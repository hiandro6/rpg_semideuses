#ifndef TIPOS_H
#define TIPOS_H

typedef enum {
    FILHO_POSEIDON = 1,
    FILHA_ATENA,
    FILHO_HADES
} ClassePersonagem;

typedef struct {
    char nome[30];
    ClassePersonagem classe;
    int vida, vidaMax;
    int forca, defesa, agilidade, inteligencia;
    int xp, nivel;
    char arma[40];
    char armadura[40];
    char habilidade[40];
} Personagem;

#endif