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

    int ships[2][3][2] = {
        {{0,0}, {0,1}, {0,2}},
        {{5,6}, {6,6}, {7,6}}
    };

    for (int i = 0; i < sizeof(ships) / sizeof(ships[0]); i++)
    {
        for (int j = 0; j < sizeof(ships[i]) / sizeof(ships[i][0]); j++)
        {
            int x = ships[i][j][0];
            int y = ships[i][j][1];
            board[x][y] = 3;
        }
    }
    
    printf("Tabuleiro inicial:\n");
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            int value = board[i][j];
            
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
