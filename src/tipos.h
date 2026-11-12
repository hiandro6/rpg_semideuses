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


typedef struct {
    const char *nome;
    const char *descricao;
    int vida, ataque, defesa, nivel;
    int xpRecompensa;
} Monstro;

typedef enum {
    ACAO_ATACAR = 1,
    ACAO_DEFENDER,
    ACAO_HABILIDADE,
    ACAO_FUGIR
} AcaoCombate;

typedef enum {
    COMBATE_VENCEU,
    COMBATE_MORREU,
    COMBATE_FUGIU
} ResultadoCombate;

#define NUM_FASES 3
#define MONSTROS_POR_FASE 3

typedef struct {
    const char *nome;
    const char *historia;
    const char *missao;
    const char *item;        /* item entregue na casa de Missao */
    double fator;            /* escala de dificuldade da fase */
    int itemObtido;          /* 1 = ja passou pela casa de Missao */
    int chefeDerrotado;      /* 1 = missao cumprida */
} Fase;

#endif