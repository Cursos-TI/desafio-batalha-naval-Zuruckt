#include <stdio.h>

// Desafio Batalha Naval - MateCheck
// Este código inicial serve como base para o desenvolvimento do sistema de Batalha Naval.
// Siga os comentários para implementar cada parte do desafio.

int main() {

    int board[10][10];

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            board[i][j] = 0;
        }   
    }

    int ships[4][3][2] = {
        {{0,0}, {0,1}, {0,2}},
        {{5,6}, {6,6}, {7,6}},
        {{1,9}, {2,8}, {3,7}},
        {{2,3}, {3,4}, {4,5}}
    };
    
    for (int i = 0; i < sizeof(ships) / sizeof(ships[0]); i++)
    {        
        for (int j = 0; j < sizeof(ships[i]) / sizeof(ships[i][0]); j++)
        {
            int x = ships[i][j][0];
            int y = ships[i][j][1];

            if (x > 9 || x < 0 || y > 9 || y < 0) {
                printf("Erro: coordenadas fora do tabuleiro.\n");
                return 1;
            }
            
            board[x][y] = 3;
        }
    }
    
    printf("Tabuleiro inicial:\n");
    printf("X A B C D E F G H I J\n");
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (j == 0) {
                printf("%d ", i);
            }
            
            int value = board[i][j];
            
            // Print ships in red
            if (value == 3) {
                printf("\033[31m");
                printf("%d ", board[i][j]);
                printf("\033[m");
            } else {
                printf("%d ", board[i][j]);
            }
        }
        printf("\n");
    }
    
    return 0;
}
