#include <stdio.h>
#include <string.h>
#include "personagem.h"

void criarPersonagem(Personagem *p, ClassePersonagem classe) {
    p->classe = classe;
    p->xp = 0;
    p->nivel = 1;

    switch (classe) {
    case FILHO_POSEIDON:
        strcpy(p->nome, "Filho de Poseidon");
        p->vidaMax = 120; p->forca = 12; p->defesa = 10;
        p->agilidade = 8; p->inteligencia = 6;
        strcpy(p->arma, "Tridente de Bronze Celestial");
        strcpy(p->armadura, "Peitoral de Escamas Marinhas");
        strcpy(p->habilidade, "Onda Gigante");
        break;
    case FILHA_ATENA:
        strcpy(p->nome, "Filha de Atena");
        p->vidaMax = 100; p->forca = 8; p->defesa = 8;
        p->agilidade = 10; p->inteligencia = 14;
        strcpy(p->arma, "Adaga e Escudo da Sabedoria");
        strcpy(p->armadura, "Armadura Grega Leve");
        strcpy(p->habilidade, "Estrategia Perfeita");
        break;
    case FILHO_HADES:
        strcpy(p->nome, "Filho de Hades");
        p->vidaMax = 90; p->forca = 10; p->defesa = 7;
        p->agilidade = 9; p->inteligencia = 12;
        strcpy(p->arma, "Espada de Ferro Estigio");
        strcpy(p->armadura, "Manto das Sombras");
        strcpy(p->habilidade, "Chamado dos Mortos");
        break;
    }
    p->vida = p->vidaMax;
}

void mostrarPersonagem(const Personagem *p) {
    printf("=== %s (Nivel %d) ===\n", p->nome, p->nivel);
    printf("Vida: %d/%d | Forca: %d | Defesa: %d\n",
           p->vida, p->vidaMax, p->forca, p->defesa);
    printf("Agilidade: %d | Inteligencia: %d | XP: %d\n",
           p->agilidade, p->inteligencia, p->xp);
    printf("Arma: %s\nArmadura: %s\nHabilidade: %s\n\n",
           p->arma, p->armadura, p->habilidade);
}