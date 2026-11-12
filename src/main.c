#include <stdio.h>
#include "personagem.h"
#include "dado.h"
#include "tabuleiro.h"
#include "combate.h"
#include "monstro.h"
#include "fase.h"

/* Descarta o que sobrou na linha digitada (ex.: o Enter depois do scanf) */
static void limparBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

static void pausar(const char *msg) {
    printf("%s", msg);
    limparBuffer();
}

static void escolherPersonagem(Personagem *p) {
    int op = 0, c;

    printf("=== ESCOLHA SEU SEMIDEUS ===\n\n");
    for (c = FILHO_POSEIDON; c <= FILHO_HADES; c++) {
        criarPersonagem(p, (ClassePersonagem)c);
        printf("[%d] ", c);
        mostrarPersonagem(p);
    }
    do {
        printf("Escolha (1-3): ");
        if (scanf("%d", &op) != 1) {
            scanf("%*s");
            op = 0;
        }
        limparBuffer();
    } while (op < 1 || op > 3);

    criarPersonagem(p, (ClassePersonagem)op);
}

/* Entrega o item da fase (casa de Missao) */
static void pegarItem(Fase *f) {
    if (f->itemObtido) {
        printf("Voce ja pegou o %s nesta fase.\n", f->item);
        return;
    }
    f->itemObtido = 1;
    printf("Voce encontrou o %s! Agora o chefe pode ser enfrentado.\n", f->item);
}

/* Executa o que acontece na casa em que o heroi caiu */
static void executarEvento(Personagem *p, Fase *f, const Casa tabuleiro[],
                           int *posicao, int numeroFase) {
    Monstro m;
    ResultadoCombate r;
    int ehChefe = (*posicao == TAM_TABULEIRO - 1);

    switch (tabuleiro[*posicao].tipo) {
    case CASA_COMBATE:
        if (ehChefe) {
            if (!f->itemObtido) {
                printf("Uma forca misteriosa impede voce de enfrentar o chefe...\n");
                printf("Voce recua para a casa de Missao.\n");
                *posicao = TAM_TABULEIRO - 2;
                pegarItem(f);
                return;
            }
            criarMonstro(&m, numeroFase, 2, f->fator);
        } else {
            sortearMonstroComum(&m, numeroFase, f->fator);
        }

        r = combate(p, &m);
        limparBuffer();   /* o combate termina logo apos um scanf */

        if (r == COMBATE_VENCEU && ehChefe) {
            f->chefeDerrotado = 1;
        } else if (r == COMBATE_FUGIU && ehChefe) {
            printf("O chefe continua te esperando. Voce volta uma casa.\n");
            *posicao = TAM_TABULEIRO - 2;
        }
        /* Recompensa de XP e bonus: Etapa 5 */
        break;
    case CASA_MISSAO:
        pegarItem(f);
        break;
    case CASA_TESOURO:
        printf("Tesouro! (efeito sera implementado na Etapa 5)\n");
        break;
    case CASA_CURA:
        printf("Fonte de cura! (efeito sera implementado na Etapa 5)\n");
        break;
    case CASA_ARMADILHA:
        printf("Armadilha! (efeito sera implementado na Etapa 5)\n");
        break;
    default:
        printf("Nada acontece por aqui.\n");
        break;
    }
}

int main(void) {
    Personagem heroi;
    Fase fases[NUM_FASES];
    Casa tabuleiro[TAM_TABULEIRO];
    int faseAtual = 0;
    int posicao = 0;
    int passos;

    iniciarAleatorio();
    inicializarFases(fases);
    inicializarTabuleiro(tabuleiro);
    escolherPersonagem(&heroi);

    mostrarMissao(&fases[faseAtual], faseAtual + 1);

    while (heroi.vida > 0 && faseAtual < NUM_FASES) {
        pausar("\nPressione Enter para lancar o d6...");

        passos = rolarDado(6);
        moverJogador(&posicao, passos);
        printf("Voce tirou %d! Foi para a casa %d (%s).\n",
               passos, posicao + 1, tabuleiro[posicao].nome);
        mostrarTabuleiro(tabuleiro, posicao);

        executarEvento(&heroi, &fases[faseAtual], tabuleiro,
                       &posicao, faseAtual);

        if (heroi.vida <= 0) break;

        if (missaoCumprida(&fases[faseAtual])) {
            printf("\nMISSAO CUMPRIDA: %s\n", fases[faseAtual].nome);
            avancarFase(&faseAtual, &posicao);
            if (faseAtual < NUM_FASES) {
                mostrarMissao(&fases[faseAtual], faseAtual + 1);
            }
        }
    }

    if (heroi.vida <= 0) {
        printf("\nGAME OVER. O Olimpo continua sem esperanca...\n");
    } else {
        printf("\nVITORIA! O Raio de Zeus foi devolvido ao Olimpo!\n");
        mostrarPersonagem(&heroi);
    }
    return 0;
}