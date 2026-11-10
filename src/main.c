#include <stdio.h>
#include "personagem.h"

int main(void) {
    Personagem heroi;
    int c;

    for (c = FILHO_POSEIDON; c <= FILHO_HADES; c++) {
        criarPersonagem(&heroi, (ClassePersonagem)c);
        mostrarPersonagem(&heroi);
    }
    return 0;
}