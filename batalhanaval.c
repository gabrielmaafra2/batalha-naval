#include <stdio.h>
#include <stdlib.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define VALOR_AGUA 0
#define VALOR_NAVIO 3
#define VALOR_HABILIDADE 5

// Preenche o tabuleiro com zeros (agua)
void preencherTabuleiro(int campo[10][10]) {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            campo[i][j] = 0;
        }
    }
}

// Verifica se o navio cabe no tabuleiro
int cabeNoTabuleiro(int linha, int coluna, char direcao) {
    if (direcao == 'H') {
        return coluna + 3 <= 10;
    } else if (direcao == 'V') {
        return linha + 3 <= 10;
    } else if (direcao =='D'){
        return linha + 3 <= 10 && coluna + 3 <= 10;
    } else if (direcao == 'I'){
        return linha + 3 <= 10 && coluna - 2 >= 0;
    }
    return 0;
}

// Verifica se o navio vai sobrepor outro
int estaLivre(int campo[10][10], int linha, int coluna, char direcao) {
    for (int i = 0; i < 3; i++) {
        if (direcao == 'H') {
            if (campo[linha][coluna + i] == 3) return 0;
        } else if (direcao == 'V') {
            if (campo[linha + i][coluna] == 3) return 0;
        } else if (direcao == 'D') {
            if (campo[linha + i][coluna + i] == 3) return 0;
        } else if (direcao == 'I') {
            if (campo[linha + i][coluna - i] == 3) return 0;
        }
    }
    return 1;
}

// Coloca o navio no tabuleiro
void colocarNavio(int campo[10][10], int navio[3], int linha, int coluna, char direcao) {
    for (int i = 0; i < 3; i++) {
        if (direcao == 'H') {
            campo[linha][coluna + i] = navio[i];
        } else if (direcao == 'V') {
            campo[linha + i][coluna] = navio[i];
        } else if (direcao == 'D') {
            campo[linha + i][coluna + i] = navio[i];
        } else if (direcao == 'I') {
            campo[linha + i][coluna - i] = navio[i];
        }
    }
}

// Aplica uma habilidade no tabuleiro baseado em uma matriz de habilidade e ponto de origem
void aplicarHabilidade(int campo[10][10], int habilidade[5][5], int origemLinha, int origemColuna) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            int linhaTabuleiro = origemLinha - 2 + i;
            int colunaTabuleiro = origemColuna - 2 + j;
            if (linhaTabuleiro >= 0 && linhaTabuleiro < 10 && colunaTabuleiro >= 0 && colunaTabuleiro < 10) {
                if (habilidade[i][j] == 1 && campo[linhaTabuleiro][colunaTabuleiro] != 3) {
                    campo[linhaTabuleiro][colunaTabuleiro] = VALOR_HABILIDADE;
                }
            }
        }
    }
}

// Gera matriz de cone (forma de piramide para baixo)
void gerarMatrizCone(int matriz[5][5]) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (i >= j - 2 && i >= 2 - j) {
                matriz[i][j] = 1;
            } else {
                matriz[i][j] = 0;
            }
        }
    }
}

// Gera matriz em forma de cruz
void gerarMatrizCruz(int matriz[5][5]) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (i == 2 || j == 2) {
                matriz[i][j] = 1;
            } else {
                matriz[i][j] = 0;
            }
        }
    }
}

// Gera matriz em forma de octaedro (losango)
void gerarMatrizOctaedro(int matriz[5][5]) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (abs(i - 2) + abs(j - 2) <= 2) {
                matriz[i][j] = 1;
            } else {
                matriz[i][j] = 0;
            }
        }
    }
}


// Mostra o tabuleiro na tela
void mostrarTabuleiro(int campo[10][10]) {
    printf("\n=== TABULEIRO BATALHA NAVAL ===\n\n");
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (campo[i][j] == VALOR_AGUA) {
                printf("~ ");
            } else if (campo[i][j] == VALOR_NAVIO) {
                printf("N ");
            } else if (campo[i][j] == VALOR_HABILIDADE) {
                printf("* ");
            } else {
                printf("? ");
            }
        }
        printf("\n");
    }
}

int main() {
    int campo[10][10];

    preencherTabuleiro(campo);

    int navioA[3] = {3, 3, 3};
    int navioB[3] = {3, 3, 3};
    int navioC[3] = {3, 3, 3};
    int navioD[3] = {3, 3, 3};

    int l1 = 2, c1 = 4;
    int l2 = 0, c2 = 0;
    int l3 = 4, c3 = 4;
    int l4 = 0, c4 = 9;

    if (cabeNoTabuleiro(l1, c1, 'H') && estaLivre(campo, l1, c1, 'H')) colocarNavio(campo, navioA, l1, c1, 'H');
    if (cabeNoTabuleiro(l2, c2, 'V') && estaLivre(campo, l2, c2, 'V')) colocarNavio(campo, navioB, l2, c2, 'V');
    if (cabeNoTabuleiro(l3, c3, 'D') && estaLivre(campo, l3, c3, 'D')) colocarNavio(campo, navioC, l3, c3, 'D');
    if (cabeNoTabuleiro(l4, c4, 'I') && estaLivre(campo, l4, c4, 'I')) colocarNavio(campo, navioD, l4, c4, 'I');

    int cone[5][5], cruz[5][5], octaedro[5][5];
    gerarMatrizCone(cone);
    gerarMatrizCruz(cruz);
    gerarMatrizOctaedro(octaedro);

    aplicarHabilidade(campo, cone, 2, 2);
    aplicarHabilidade(campo, cruz, 5, 5);
    aplicarHabilidade(campo, octaedro, 7, 7);

    mostrarTabuleiro(campo);

    return 0;
}
