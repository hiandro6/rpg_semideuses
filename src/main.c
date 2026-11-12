#include <stdio.h>
#include "personagem.h"
#include "dado.h"
#include "combate.h"

int main(void) {
    Personagem heroi;
    Monstro minotauro = {
        "Minotauro", "Fera do Labirinto de Creta",
        60, 8, 4, 1, 30
    };
    ResultadoCombate r;
    int escolha;

    iniciarAleatorio();

    printf("Escolha: [1] Poseidon  [2] Atena  [3] Hades: ");
    if (scanf("%d", &escolha) != 1 || escolha < 1 || escolha > 3) {
        escolha = 1;
    }
    criarPersonagem(&heroi, (ClassePersonagem)escolha);

    r = combate(&heroi, &minotauro);

    if (r == COMBATE_VENCEU)      printf("Resultado: vitoria!\n");
    else if (r == COMBATE_MORREU) printf("Resultado: game over.\n");
    else                          printf("Resultado: fuga.\n");

    return 0;
}