#include <stdio.h>
#include <string.h>

char board[3][3];

// Original logic below (unchanged functions)
void initBoard() {
    char val = '1';
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = val++;
}

void printBoard() {
    printf("\n");
    for (int i = 0; i < 3; i++) {
        printf(" ");
        for (int j = 0; j < 3; j++) {
            printf(" %c ", board[i][j]);
            if (j < 2) printf("|");
        }
        if (i < 2) printf("\n---|---|---\n");
    }
    printf("\n");
}

int checkWin(char mark) {
    for (int i = 0; i < 3; i++) {
        if ((board[i][0] == mark && board[i][1] == mark && board[i][2] == mark) ||
            (board[0][i] == mark && board[1][i] == mark && board[2][i] == mark))
            return 1;
    }
    if ((board[0][0] == mark && board[1][1] == mark && board[2][2] == mark) ||
        (board[0][2] == mark && board[1][1] == mark && board[2][0] == mark))
        return 1;
    return 0;
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

// New main with features around original game logic
int main() {
    int pos, row, col;
    char player = 'X';
    char player1[20], player2[20];

    printf("Enter name for Player 1 (X): ");
    fgets(player1, sizeof(player1), stdin);
    player1[strcspn(player1, "\n")] = 0; // remove newline

    printf("Enter name for Player 2 (O): ");
    fgets(player2, sizeof(player2), stdin);
    player2[strcspn(player2, "\n")] = 0;

    initBoard();

    while (1) {
        printBoard();
        printf("%s (%c), enter position (1-9 or 0 to quit): ", (player == 'X') ? player1 : player2, player);

        if (scanf("%d", &pos) != 1) {
            printf("Invalid input. Try again.\n");
            clearInput();
            continue;
        }

        if (pos == 0) {
            printf("Game exited. 👋\n");
            break;
        }

        if (pos < 1 || pos > 9) {
            printf("Position out of range! Try again.\n");
            continue;
        }

        row = (pos - 1) / 3;
        col = (pos - 1) % 3;

        if (board[row][col] == 'X' || board[row][col] == 'O') {
            printf("Cell already taken! Try again.\n");
            continue;
        }

        board[row][col] = player;

        if (checkWin(player)) {
            printBoard();
            printf("🎉 %s (%c) wins!\n", (player == 'X') ? player1 : player2, player);
            break;
        }

        if (isFull()) {
            printBoard();
            printf("🤝 It's a draw!\n");
            break;
        }

        player = (player == 'X') ? 'O' : 'X';
    }

    return 0;
}
