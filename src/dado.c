#include <stdlib.h>
#include <time.h>
#include "dado.h"

/* Chamar uma única vez, no início do programa */
void iniciarAleatorio(void) {
    srand((unsigned int)time(NULL));
}

/* Retorna um valor entre 1 e "lados" (d6, d20...) */
int rolarDado(int lados) {
    return rand() % lados + 1;
}