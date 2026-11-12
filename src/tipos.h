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

#define TAM_TABULEIRO 12

typedef enum {
    CASA_VAZIA,
    CASA_COMBATE,
    CASA_TESOURO,
    CASA_CURA,
    CASA_ARMADILHA,
    CASA_MISSAO
} TipoCasa;

typedef struct {
    TipoCasa tipo;
    const char *nome;   /* texto exibido para o jogador */
} Casa;

#endif