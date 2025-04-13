#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

char board[3][3];
int player1Wins = 0, player2Wins = 0;

void initBoard() {
    char val = '1';
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = val++;
}

void printBoard() {
    printf("\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf(" %c ", board[i][j]);
            if (j < 2) printf("|");
        }
        if (i < 2) printf("\n---|---|---\n");
    }
    printf("\n\n");
}

int checkWin(char mark) {
    for (int i = 0; i < 3; i++) {
        if ((board[i][0] == mark && board[i][1] == mark && board[i][2] == mark) ||
            (board[0][i] == mark && board[1][i] == mark && board[2][i] == mark)) return 1;
    }
    return (board[0][0] == mark && board[1][1] == mark && board[2][2] == mark) ||
           (board[0][2] == mark && board[1][1] == mark && board[2][0] == mark);
}

int isFull() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] != 'X' && board[i][j] != 'O')
                return 0;
    return 1;
}

void clearInput() {
    while (getchar() != '\n');
}

int isOnlyDigits(const char *str) {
    while (*str) if (!isdigit(*str++)) return 0;
    return 1;
}

int isValidInput(char *input) {
    return (strlen(input) > 0 && !isOnlyDigits(input) && strlen(input) <= 18);
}

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

int main() {
    int pos, row, col, playAgain;
    char player = 'X', player1[20], player2[20], input[100];

    clearScreen();

    while (1) {
        printf("Enter name for Player 1 (X): ");
        fgets(player1, sizeof(player1), stdin);
        player1[strcspn(player1, "\n")] = 0;
        if (!isValidInput(player1)) { printf("Invalid name. Try again.\n"); continue; }
        break;
    }

    while (1) {
        printf("Enter name for Player 2 (O): ");
        fgets(player2, sizeof(player2), stdin);
        player2[strcspn(player2, "\n")] = 0;
        if (!isValidInput(player2)) { printf("Invalid name. Try again.\n"); continue; }
        if (strcasecmp(player1, player2) == 0) { printf("Names cannot be the same. Try again.\n"); continue; }
        break;
    }

    do {
        initBoard();

        while (1) {
            printBoard();
            printf("%s (%c), enter position (1-9 or 0 to quit): ", (player == 'X') ? player1 : player2, player);
            fgets(input, sizeof(input), stdin);
            input[strcspn(input, "\n")] = '\0';

            if (sscanf(input, "%d", &pos) != 1 || pos < 0 || pos > 9 || (pos != 0 && board[(pos - 1) / 3][(pos - 1) % 3] == 'X' || board[(pos - 1) / 3][(pos - 1) % 3] == 'O')) {
                printf("Invalid input. Try again.\n");
                continue;
            }

            if (pos == 0) { printf("Game exited. 👋\n"); break; }

            row = (pos - 1) / 3;
            col = (pos - 1) % 3;
            board[row][col] = player;

            if (checkWin(player)) {
                printBoard();
                printf("🎉 %s (%c) wins!\n", (player == 'X') ? player1 : player2, player);
                player == 'X' ? player1Wins++ : player2Wins++;
                break;
            }
            if (isFull()) {
                printBoard();
                printf("🤝 It's a draw!\n");
                break;
            }

            player = (player == 'X') ? 'O' : 'X';
        }

        printf("\n%s(X):%d  %s(O):%d\n", player1, player1Wins, player2, player2Wins);

        printf("\nPlay again? (1 = Yes, 0 = No): ");
        if (scanf("%d", &playAgain) != 1 || (playAgain != 1 && playAgain != 0)) {
            printf("Invalid input. Exiting...\n");
            break;
        }
        clearInput();
        player = (player == 'X') ? 'O' : 'X';
    } while (playAgain == 1);

    printf("Thanks for playing! 👋\n");
    return 0;
}
