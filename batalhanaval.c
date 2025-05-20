#include <stdio.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define VALOR_AGUA 0
#define VALOR_NAVIO 3

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
        }
    }
}

// Mostra o tabuleiro na tela
void mostrarTabuleiro(int campo[10][10]) {
    printf("\n=== TABULEIRO BATALHA NAVAL ===\n\n");
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            printf("%d ", campo[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int campo[10][10];

    preencherTabuleiro(campo);

    int navioA[3] = {3, 3, 3}; // horizontal
    int navioB[3] = {3, 3, 3}; // vertical

    int l1 = 2, c1 = 4;
    int l2 = 0, c2 = 0;

    if (cabeNoTabuleiro(l1, c1, 'H') && estaLivre(campo, l1, c1, 'H')) {
        colocarNavio(campo, navioA, l1, c1, 'H');
    } else {
        printf("Erro ao colocar navio A\n");
        return 1;
    }

    if (cabeNoTabuleiro(l2, c2, 'V') && estaLivre(campo, l2, c2, 'V')) {
        colocarNavio(campo, navioB, l2, c2, 'V');
    } else {
        printf("Erro ao colocar navio B\n");
        return 1;
    }

    mostrarTabuleiro(campo);

    return 0;
}
