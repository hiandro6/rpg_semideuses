# Semideuses: A Jornada pelo Raio de Zeus

**Aluno:** Hiandro Alex Silva de Medeiros
**Matrícula:** 20260014041
**Disciplina:** DCT1106 - Programação (BSI/UFRN) - 2026.2

Jogo de tabuleiro RPG em modo texto, feito em C (padrão **C99**), que roda inteiramente no terminal.

## História

O Raio de Zeus, a arma mais poderosa do Olimpo, foi roubado e escondido nas profundezas do mundo mitológico. Sem ele, os deuses enfraquecem e o caos ameaça a Terra. Três semideuses, filhos de Poseidon, Atena e Hades, se oferecem para recuperá-lo. O herói escolhido precisa atravessar o Labirinto de Creta, o Mar dos Monstros e o Submundo, cumprindo uma missão em cada lugar. Na última fase, ele enfrenta Cérbero e devolve o Raio de Zeus ao Olimpo.

## Personagens

| Classe | Vida | Força | Defesa | Agilidade | Inteligência | Arma | Armadura | Habilidade especial |
|---|---|---|---|---|---|---|---|---|
| Filho de Poseidon | 120 | 12 | 10 | 8 | 6 | Tridente de Bronze Celestial | Peitoral de Escamas Marinhas | **Onda Gigante**: ataque com +10 de dano |
| Filha de Atena | 100 | 8 | 8 | 10 | 14 | Adaga e Escudo da Sabedoria | Armadura Grega Leve | **Estratégia Perfeita**: ignora a defesa do monstro |
| Filho de Hades | 90 | 10 | 7 | 9 | 12 | Espada de Ferro Estígio | Manto das Sombras | **Chamado dos Mortos**: causa dano e recupera metade do dano causado em vida |

Todos começam no nível 1 com 0 de XP.

## Fases e monstros

Cada fase tem 3 monstros comuns (sorteados sem repetição) e 1 chefe. Os valores abaixo são os **base** (vida / ataque / defesa / XP) e são multiplicados pelo fator da fase.

| Fase | Fator | Missão | Monstros comuns | Chefe |
|---|---|---|---|---|
| 1 - Labirinto de Creta | 1.0 | Pegar o Fio de Ariadne e derrotar o Minotauro | Harpia (25/5/1/20), Cão Infernal (35/6/2/25), Empusa (30/6/2/22) | Minotauro (55/8/3/50) |
| 2 - Mar dos Monstros | 1.4 | Recuperar o Velocino de Ouro e derrotar Scylla | Ciclope (35/6/2/20), Hidra (45/7/3/25), Sereia (40/7/2/22) | Scylla (60/8/4/50) |
| 3 - Submundo | 1.8 | Resgatar o Raio de Zeus e derrotar Cérbero | Fúria (40/7/3/20), Quimera (50/8/4/25), Espectro (45/8/3/22) | Cérbero (65/9/5/50) |

## Dinâmica do jogo

### Tabuleiro e movimentação
- O tabuleiro tem 12 casas. O herói lança um d6 e avança esse número de casas, parando na última se o dado passar do fim.
- Layout: 1 Início, 2 Vazia, 3 Combate, 4 Tesouro, 5 Combate, 6 Cura, 7 Armadilha, 8 Combate, 9 Vazia, 10 Tesouro, 11 Missão, 12 Chefe.
- Ao cair na casa de **Missão**, o herói pega o item da fase. O chefe (casa 12) só pode ser enfrentado depois disso; se chegar nele sem o item, o herói recua para a casa 11.

### Combate por turnos
A cada turno o jogador escolhe uma ação:
1. **Atacar**
2. **Defender**: o dano do próximo ataque do monstro cai pela metade
3. **Habilidade especial**: recarga de 3 turnos
4. **Fugir**: lança d6 e foge com 4 ou mais (50%). Fugir não dá recompensa; fugir do chefe faz o herói voltar uma casa.

Depois da ação, o monstro contra-ataca. Há 1 segundo de pausa entre as ações.

### Fórmulas
| Cálculo | Fórmula |
|---|---|
| Ataque do herói | d20 + força (Atena usa inteligência) |
| Ataque do monstro | d20 + ataque do monstro |
| Dano | max(1, ataque - defesa do alvo) |
| Escala da fase | atributo final = ⌈atributo base × fator da fase⌉ |
| XP para subir de nível | nível × 50 de XP acumulado |
| Subida de nível | vida máxima +10, força +1, defesa +1, vida atual +10 |

### Eventos das casas
- **Combate:** monstro comum sorteado (nunca repete na fase) ou o chefe na casa 12.
- **Tesouro:** 50% de chance de bônus aleatório de atributo, 50% de XP extra (20 × número da fase).
- **Cura:** recupera 30% da vida máxima.
- **Armadilha:** perde 5 × número da fase + 10% da vida atual. Nunca mata: deixa no mínimo 1 de vida.
- **Missão:** entrega o item da fase.

### Recompensas e descanso
- Ao vencer um monstro, o herói ganha o XP dele e um bônus aleatório (força +1, defesa +1, agilidade +1, inteligência +1 ou vida máxima +5).
- Ao concluir uma fase, o herói descansa e recupera 15% da vida máxima antes da próxima.

### Vitória e derrota
- **Vitória:** derrotar o chefe das 3 fases (Cérbero encerra o jogo).
- **Derrota:** a vida do herói chega a 0.

## Como compilar e jogar

Pré-requisito: `gcc` (padrão C99).

**Linux** (`sudo apt install build-essential`) e **macOS** (Xcode Command Line Tools):
```bash
make
./jogo
```

Sem `make`:
```bash
gcc -Wall -Wextra -std=c99 -o jogo src/*.c -lm
./jogo
```

**Windows** (MinGW), no terminal:
```bash
gcc -Wall -Wextra -std=c99 -o jogo.exe src/main.c src/personagem.c src/dado.c src/tabuleiro.c src/combate.c src/monstro.c src/fase.c src/interface.c -lm
jogo.exe
```

Observação: o delay entre os turnos usa `clock()` de `time.h` (espera ocupada), para respeitar a lista de bibliotecas permitidas (`stdio.h`, `stdlib.h`, `string.h`, `time.h`, `math.h`).

## Estrutura do código

```
src/
├── tipos.h        # enums e structs
├── personagem.*   # criação, exibição, XP, nível, bônus, cura
├── dado.*         # rolarDado e srand
├── tabuleiro.*    # casas, movimentação, exibição
├── combate.*      # turnos, ataque, dano, habilidades, fuga
├── monstro.*      # tabela de monstros, escala por fase, sorteio
├── fase.*         # fases, missões, avanço e descanso
├── interface.*    # leitura segura de entrada, pausa e delay
└── main.c         # fluxo geral do jogo
```

**Enums:** `ClassePersonagem`, `TipoCasa`, `AcaoCombate`, `ResultadoCombate`.
**Structs:** `Personagem`, `Monstro`, `Casa`, `Fase`.

**Uso de ponteiros** (a atualização de status é sempre feita por endereço):
- `receberDano(Personagem *p, int dano)` e `danoNoMonstro(Monstro *m, int dano)`
- `ganharXP`, `subirNivel`, `aplicarBonusAleatorio` e `curar` recebem `Personagem *p`
- `moverJogador(int *posicao, int passos)` e `avancarFase(int *faseAtual, int *posicao)`
- `sortearMonstroComum(..., int usado[])` marca os monstros usados dentro da `Fase`

**Robustez:** `lerInteiro` usa `fgets` + `strtol` e repete a pergunta até receber um número válido, então letras, linha vazia ou números fora do menu não travam o jogo.


## Vídeo de demonstração

[Assista aqui](https://drive.google.com/drive/folders/1esjCudwzjoP6qa-7g-E07PSZsdOQDUhJ?usp=drive_link)
