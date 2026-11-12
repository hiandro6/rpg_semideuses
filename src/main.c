#include <stdio.h>
#include "personagem.h"
#include "dado.h"
#include "tabuleiro.h"
#include "combate.h"
#include "monstro.h"
#include "fase.h"
#include "interface.h"

static void escolherPersonagem(Personagem *p) {
    int op, c;

    printf("=== ESCOLHA SEU SEMIDEUS ===\n\n");
    for (c = FILHO_POSEIDON; c <= FILHO_HADES; c++) {
        criarPersonagem(p, (ClassePersonagem)c);
        printf("[%d] ", c);
        mostrarPersonagem(p);
    }
    op = lerInteiro("Escolha (1-3): ", 1, 3);
    criarPersonagem(p, (ClassePersonagem)op);

    mostrarApresentacao(p);
}

/* Linha de resumo mostrada depois de cada evento */
static void mostrarResumo(const Personagem *p) {
    printf("[Vida: %d/%d | Nivel: %d | XP: %d/%d]\n",
           p->vida, p->vidaMax, p->nivel, p->xp, p->nivel * 50);
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
    int dano, cura;

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
            criarMonstro(&m, numeroFase, MONSTROS_POR_FASE - 1, f->fator);
        } else {
            sortearMonstroComum(&m, numeroFase, f->fator, f->monstroUsado);
        }

        r = combate(p, &m);

        if (r == COMBATE_VENCEU) {
            printf("Recompensa: %d XP!\n", m.xpRecompensa);
            ganharXP(p, m.xpRecompensa);
            aplicarBonusAleatorio(p);
            if (ehChefe) f->chefeDerrotado = 1;
        } else if (r == COMBATE_FUGIU && ehChefe) {
            printf("O chefe continua te esperando. Voce volta uma casa.\n");
            *posicao = TAM_TABULEIRO - 2;
        }
        break;
    case CASA_MISSAO:
        pegarItem(f);
        break;
    case CASA_TESOURO:
        printf("Voce encontrou um bau!\n");
        if (rolarDado(2) == 1) {
            aplicarBonusAleatorio(p);
        } else {
            printf("Ouro e reliquias valem %d XP!\n", 20 * (numeroFase + 1));
            ganharXP(p, 20 * (numeroFase + 1));
        }
        break;
    case CASA_CURA:
        cura = p->vidaMax * 30 / 100;
        curar(p, cura);
        printf("Uma fonte sagrada restaura sua vida!\n");
        break;
    case CASA_ARMADILHA:
        dano = 5 * (numeroFase + 1) + p->vida / 10;
        if (dano > p->vida - 1) dano = p->vida - 1;   /* nunca mata */
        receberDano(p, dano);
        printf("Armadilha! Voce perde %d de vida.\n", dano);
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
        mostrarResumo(&heroi);

        if (heroi.vida <= 0) break;

        if (missaoCumprida(&fases[faseAtual])) {
            printf("\nMISSAO CUMPRIDA: %s\n", fases[faseAtual].nome);
            avancarFase(&faseAtual, &posicao);
            if (faseAtual < NUM_FASES) {
                descansarEntreFases(&heroi, faseAtual);
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