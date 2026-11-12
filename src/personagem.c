#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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

/* Sobe um nível: aumenta atributos e recupera parte da vida */
void subirNivel(Personagem *p) {
    p->nivel++;
    p->vidaMax += 10;
    p->forca++;
    p->defesa++;
    p->vida += 10;
    if (p->vida > p->vidaMax) p->vida = p->vidaMax;
    printf("*** NIVEL %d! Vida max +10, Forca +1, Defesa +1 ***\n", p->nivel);
}

/* Soma XP e sobe de nível enquanto o total alcançar nivel * 50 */
void ganharXP(Personagem *p, int xp) {
    p->xp += xp;
    while (p->xp >= p->nivel * 50) {
        subirNivel(p);
    }
}

/* Sorteia um atributo para receber bônus */
void aplicarBonusAleatorio(Personagem *p) {
    switch (rand() % 5) {
    case 0: p->forca++;
            printf("Bonus: Forca +1!\n"); break;
    case 1: p->defesa++;
            printf("Bonus: Defesa +1!\n"); break;
    case 2: p->agilidade++;
            printf("Bonus: Agilidade +1!\n"); break;
    case 3: p->inteligencia++;
            printf("Bonus: Inteligencia +1!\n"); break;
    default: p->vidaMax += 5;
             printf("Bonus: Vida maxima +5!\n"); break;
    }
}

/* Recupera vida sem passar do máximo */
void curar(Personagem *p, int quantidade) {
    p->vida += quantidade;
    if (p->vida > p->vidaMax) p->vida = p->vidaMax;
}

/* Conta a lore da classe escolhida e destaca pontos fortes e fracos */
void mostrarApresentacao(const Personagem *p) {
    printf("\nVoce escolheu o %s!\n", p->nome);
    switch (p->classe) {
    case FILHO_POSEIDON:
        printf("Criado a beira-mar, ele carrega a furia das tempestades no sangue.\n");
        printf("Resistente e forte, e o mais duro de derrubar, mas nao e muito agil\n");
        printf("nem esperto. Sua Onda Gigante e um golpe devastador!\n");
        break;
    case FILHA_ATENA:
        printf("Estrategista nata, ela vence as batalhas antes mesmo de lutar.\n");
        printf("Nao aguenta tanto dano quanto os irmaos, mas sua inteligencia\n");
        printf("e enorme. A Estrategia Perfeita ignora a defesa de qualquer inimigo!\n");
        break;
    default: /* FILHO_HADES */
        printf("Sombrio e solitario, ele cresceu entre os espiritos do Submundo.\n");
        printf("Nao e um bom defensor e tem pouca vida, mas seu Chamado dos Mortos\n");
        printf("e uma habilidade incrivel: causa dano e rouba a vida do inimigo!\n");
        break;
    }
    printf("\n");
}