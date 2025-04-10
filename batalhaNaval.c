#include <stdio.h>
#include <stdlib.h> // para a função abs()

#define BOARD_SIZE 10

// Tamanhos das matrizes de habilidade
#define CONE_ROWS 3
#define CONE_COLS 5
#define SKILL_SIZE 5  // Usado para a Cruz e o Octaedro (5x5)

// Função para imprimir o tabuleiro
void printBoard(int board[BOARD_SIZE][BOARD_SIZE]) {
    printf("  A B C D E F G H I J\n");
    for (int i = 0; i < BOARD_SIZE; i++) {
        printf("%d ", i);
        for (int j = 0; j < BOARD_SIZE; j++) {
            // Se o valor for 3 (navio) o imprime em vere; 
            // se for 5 (área afetada) o imprime em vermelho; 
            // se for 7 (navio atingido) o imprime em amarelo;
            // caso contrário, imprime em azul (água)
            if (board[i][j] == 3) {
                printf("\033[32m3 \033[m");
            } else if (board[i][j] == 5) {
                printf("\033[31m5 \033[m");
            } else if (board[i][j] == 7) {
                printf("\033[33m7 \033[m");
            } else {
                printf("\033[34m0 \033[m");
            }
        }
        printf("\n");
    }
    printf("\n");
}

/*
 * Função para sobrepor a matriz de habilidade ao tabuleiro.
 * Se o parâmetro centralizado for 1, a matriz será posicionada de forma
 * que seu centro (índice SKILL_SIZE/2) coincida com o ponto de origem.
 * Se for 0 (no caso do Cone), o ponto de origem da matriz de habilidade será a
 * primeira linha (índice 0) e a coluna central.
 */
void overlaySkill(int board[BOARD_SIZE][BOARD_SIZE],
                  int skillRows, int skillCols,
                  int skillMatrix[skillRows][skillCols],
                  int originRow, int originCol, int centered) {
    int offsetRow, offsetCol;
    for (int i = 0; i < skillRows; i++) {
        for (int j = 0; j < skillCols; j++) {
            if (skillMatrix[i][j] == 1) {
                if (centered) {
                    offsetRow = i - (skillRows / 2);
                    offsetCol = j - (skillCols / 2);
                } else {
                    // Para o cone, a origem da matriz é a primeira linha e a coluna central.
                    offsetRow = i;
                    offsetCol = j - (skillCols / 2);
                }

                int boardRow = originRow + offsetRow;
                int boardCol = originCol + offsetCol;

                // Verifica se a posição calculada está dentro dos limites do tabuleiro
                if (boardRow >= 0 && boardRow < BOARD_SIZE &&
                    boardCol >= 0 && boardCol < BOARD_SIZE) {
                    
                    // Se houver um navio na posição, marca como atingido (valor 7)
                    if (board[boardRow][boardCol] == 3) {
                        board[boardRow][boardCol] = 7;
                    } else {
                        // Marca a área afetada com 5
                        board[boardRow][boardCol] = 5;
                    }
                }
            }
        }
    }
}

int main() {
    // 1. Inicializa o tabuleiro com água (0)
    int board[BOARD_SIZE][BOARD_SIZE];
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = 0;
        }
    }

    // 2. Posiciona os navios no tabuleiro (valor 3)
    int ships[4][3][2] = {
        {{0,0}, {0,1}, {0,2}},
        {{5,6}, {6,6}, {7,6}},
        {{1,9}, {2,8}, {3,7}},
        {{2,3}, {3,4}, {4,5}}
    };
    
    for (int i = 0; i < sizeof(ships) / sizeof(ships[0]); i++) {        
        for (int j = 0; j < sizeof(ships[i]) / sizeof(ships[i][0]); j++) {
            int x = ships[i][j][0];
            int y = ships[i][j][1];

            if (x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE) {
                printf("Erro: coordenadas fora do tabuleiro.\n");
                return 1;
            }
            
            board[x][y] = 3;
        }
    }
    
    printf("Tabuleiro inicial:\n");
    printBoard(board);

    // 3. Construir as matrizes de habilidades

    // 3.1. Habilidade em forma de Cone (3x5)
    int cone[CONE_ROWS][CONE_COLS];
    int coneCenter = CONE_COLS / 2;
    // A lógica: na linha 0, apenas a coluna central; na linha 1, expande uma posição para cada lado, etc.
    for (int i = 0; i < CONE_ROWS; i++) {
        for (int j = 0; j < CONE_COLS; j++) {
            if (j >= (coneCenter - i) && j <= (coneCenter + i))
                cone[i][j] = 1;
            else
                cone[i][j] = 0;
        }
    }

    // 3.2. Habilidade em forma de Cruz (5x5)
    int cross[SKILL_SIZE][SKILL_SIZE];
    for (int i = 0; i < SKILL_SIZE; i++) {
        for (int j = 0; j < SKILL_SIZE; j++) {
            if (i == SKILL_SIZE / 2 || j == SKILL_SIZE / 2)
                cross[i][j] = 1;
            else
                cross[i][j] = 0;
        }
    }

    // 3.3. Habilidade em forma de Octaedro (vista frontal / losango) (5x5)
    int octahedron[SKILL_SIZE][SKILL_SIZE];
    int octCenter = SKILL_SIZE / 2;
    for (int i = 0; i < SKILL_SIZE; i++) {
        for (int j = 0; j < SKILL_SIZE; j++) {
            if (abs(i - octCenter) + abs(j - octCenter) <= octCenter)
                octahedron[i][j] = 1;
            else
                octahedron[i][j] = 0;
        }
    }

    // 4. Sobrepor as áreas de efeito no tabuleiro
    // Os pontos de origem foram definidos diretamente no código.
    // Para habilidades com matriz centralizada (Cruz e Octaedro), o centro da matriz
    // (posição [SKILL_SIZE/2][SKILL_SIZE/2]) será alinhado com o ponto de origem.
    // Para o Cone, o ponto de origem da matriz será a primeira linha e a coluna central.
    
    // Sobrepor o Cone no tabuleiro (uso da sobreposição não centralizada)
    // Exemplo: ponto de origem (1, 4)
    overlaySkill(board, CONE_ROWS, CONE_COLS, cone, 1, 4, 0);
    
    // Sobrepor a Cruz no tabuleiro (matriz centralizada)
    // Exemplo: ponto de origem (5, 5)
    overlaySkill(board, SKILL_SIZE, SKILL_SIZE, cross, 5, 5, 1);
    
    // Sobrepor o Octaedro no tabuleiro (matriz centralizada)
    // Exemplo: ponto de origem (7, 2)
    overlaySkill(board, SKILL_SIZE, SKILL_SIZE, octahedron, 7, 2, 1);
    
    // 5. Exibir o tabuleiro final com navios e áreas de efeito das habilidades
    printf("Tabuleiro final com áreas de efeito das habilidades:\n");
    printBoard(board);
    
    return 0;
}
