#include <stdio.h>
#include "combate.h"
#include "dado.h"

#define RECARGA_HABILIDADE 3
#define DADO_FUGA_MIN 4        /* d6 >= 4 => 50% de chance */

/* ---------- Aplicação de dano (via ponteiro) ---------- */

void receberDano(Personagem *p, int dano) {
    p->vida -= dano;
    if (p->vida < 0) p->vida = 0;
}

void danoNoMonstro(Monstro *m, int dano) {
    m->vida -= dano;
    if (m->vida < 0) m->vida = 0;
}

/* ---------- Cálculos ---------- */

/* Ataque = d20 + atributo principal da classe */
int calcularAtaque(const Personagem *p) {
    int atributo = p->forca;
    if (p->classe == FILHA_ATENA) {
        atributo = p->inteligencia;   /* Atena ataca com a mente */
    }
    return rolarDado(20) + atributo;
}

/* Dano = max(1, ataque - defesa) */
int calcularDano(int ataque, int defesa) {
    int dano = ataque - defesa;
    if (dano < 1) dano = 1;
    return dano;
}

/* ---------- Interface do combate ---------- */

static void mostrarStatus(const Personagem *p, const Monstro *m) {
    printf("\n--------------------------------------\n");
    printf("%s: %d/%d PV\n", p->nome, p->vida, p->vidaMax);
    printf("%s: %d PV\n", m->nome, m->vida);
    printf("--------------------------------------\n");
}

static AcaoCombate escolherAcao(const Personagem *p, int recarga) {
    int op;
    printf("[1] Atacar  [2] Defender  [3] %s", p->habilidade);
    if (recarga > 0) {
        printf(" (recarga: %d)", recarga);
    }
    printf("  [4] Fugir\nEscolha: ");
    if (scanf("%d", &op) != 1) {
        scanf("%*s");   /* descarta a entrada inválida */
        return 0;
    }
    return (AcaoCombate)op;
}

/* ---------- Turnos ---------- */

/* Habilidade especial de cada classe */
static void usarHabilidade(Personagem *p, Monstro *m) {
    int ataque = calcularAtaque(p);
    int dano;

    switch (p->classe) {
    case FILHO_POSEIDON:
        dano = calcularDano(ataque, m->defesa) + 10;
        printf("Onda Gigante! Uma muralha de agua atinge %s: %d de dano!\n",
               m->nome, dano);
        break;
    case FILHA_ATENA:
        dano = calcularDano(ataque, 0);   /* ignora a defesa */
        printf("Estrategia Perfeita! Voce acha o ponto fraco de %s: %d de dano!\n",
               m->nome, dano);
        break;
    default: /* FILHO_HADES */
        dano = calcularDano(ataque, m->defesa);
        printf("Chamado dos Mortos! Espiritos atacam %s: %d de dano!\n",
               m->nome, dano);
        p->vida += dano / 2;
        if (p->vida > p->vidaMax) p->vida = p->vidaMax;
        printf("Voce absorve %d de vida.\n", dano / 2);
        break;
    }
    danoNoMonstro(m, dano);
}

/* Retorna 1 se o herói conseguiu fugir */
static int tentarFuga(void) {
    int d = rolarDado(6);
    printf("Voce tenta fugir... (d6 = %d)\n", d);
    return d >= DADO_FUGA_MIN;
}

static void turnoMonstro(Personagem *p, const Monstro *m, int defendendo) {
    int ataque = rolarDado(20) + m->ataque;
    int dano = calcularDano(ataque, p->defesa);

    if (defendendo) {
        dano /= 2;
        if (dano < 1) dano = 1;
    }
    printf("%s ataca! (ataque %d) Voce perde %d de vida.\n",
           m->nome, ataque, dano);
    receberDano(p, dano);
}

/* ---------- Combate completo ---------- */

ResultadoCombate combate(Personagem *p, Monstro *m) {
    int recarga = 0;        /* turnos até poder usar a habilidade */
    int defendendo;
    int dano, ataque;
    AcaoCombate acao;

    printf("\n!!! %s apareceu: %s\n", m->nome, m->descricao);

    while (p->vida > 0 && m->vida > 0) {
        defendendo = 0;
        mostrarStatus(p, m);
        acao = escolherAcao(p, recarga);

        switch (acao) {
        case ACAO_ATACAR:
            ataque = calcularAtaque(p);
            dano = calcularDano(ataque, m->defesa);
            printf("Voce ataca! (ataque %d) %s perde %d de vida.\n",
                   ataque, m->nome, dano);
            danoNoMonstro(m, dano);
            break;
        case ACAO_DEFENDER:
            defendendo = 1;
            printf("Voce se prepara para defender.\n");
            break;
        case ACAO_HABILIDADE:
            if (recarga > 0) {
                printf("Habilidade em recarga! Escolha outra acao.\n");
                continue;   /* não gasta o turno */
            }
            usarHabilidade(p, m);
            recarga = RECARGA_HABILIDADE + 1;   /* +1 pois diminui no fim do turno */
            break;
        case ACAO_FUGIR:
            if (tentarFuga()) {
                printf("Voce fugiu!\n");
                return COMBATE_FUGIU;
            }
            printf("A fuga falhou!\n");
            break;
        default:
            printf("Opcao invalida! Escolha de 1 a 4.\n");
            continue;       /* não gasta o turno */
        }

        if (m->vida <= 0) break;

        turnoMonstro(p, m, defendendo);
        if (recarga > 0) recarga--;
    }

    if (p->vida <= 0) {
        printf("\nVoce foi derrotado por %s...\n", m->nome);
        return COMBATE_MORREU;
    }
    printf("\nVoce derrotou %s!\n", m->nome);
    return COMBATE_VENCEU;
}