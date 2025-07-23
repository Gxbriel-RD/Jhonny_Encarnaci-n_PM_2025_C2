#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define BOARD_SIZE 8

// Representacion de piezas
// Blancas: mayusculas, Negras: minusculas
char board[BOARD_SIZE][BOARD_SIZE] = {
    {'r','n','b','q','k','b','n','r'},
    {'p','p','p','p','p','p','p','p'},
    {' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' '},
    {' ',' ',' ',' ',' ',' ',' ',' '},
    {'P','P','P','P','P','P','P','P'},
    {'R','N','B','Q','K','B','N','R'}
};
//Imprime el tablero completo
void printBoard() {
    printf("  a b c d e f g h\n");
    for (int i = 0; i < BOARD_SIZE; i++) {
        printf("%d ", 8 - i);
        for (int j = 0; j < BOARD_SIZE; j++) {
            printf("%c ", board[i][j]);
        }
        printf("%d\n", 8 - i);
    }
    printf("  a b c d e f g h\n");
}
//Calcula la posicion usando notacion de ajedres (D3,E4,A7)
int parsePosition(const char* pos, int* row, int* col) {
    if (strlen(pos) != 2) return 0;
    char file = pos[0];
    char rank = pos[1];
    if (file < 'a' || file > 'h' || rank < '1' || rank > '8') return 0;
    *col = file - 'a';
    *row = 8 - (rank - '0');
    return 1;
}
//Verifica si es blanca
int isWhite(char piece) {
    return isupper(piece);
}
//Se valida si el movimiento es legal usando las columnas y filas que se supone es posible que se mueva esa pieza
int isLegalMove(int fromRow, int fromCol, int toRow, int toCol, int turn) {
    char piece = board[fromRow][fromCol];
    char target = board[toRow][toCol];

    if (piece == ' ') return 0;
    if (turn == 1 && !isWhite(piece)) return 0;
    if (turn == 2 && isWhite(piece)) return 0;
    if (target != ' ' && ((isWhite(piece) && isWhite(target)) || (!isWhite(piece) && !isWhite(target))))
        return 0;

    int dr = toRow - fromRow;
    int dc = toCol - fromCol;

    piece = tolower(piece);

    switch (piece) {
        case 'p': // Reglas del Peon
            if (isWhite(board[fromRow][fromCol])) {
                if (dc == 0 && dr == -1 && target == ' ') return 1;
                if (fromRow == 6 && dc == 0 && dr == -2 && board[fromRow - 1][fromCol] == ' ' && target == ' ') return 1;
                if (abs(dc) == 1 && dr == -1 && target != ' ' && !isWhite(target)) return 1;
            } else {
                if (dc == 0 && dr == 1 && target == ' ') return 1;
                if (fromRow == 1 && dc == 0 && dr == 2 && board[fromRow + 1][fromCol] == ' ' && target == ' ') return 1;
                if (abs(dc) == 1 && dr == 1 && target != ' ' && isWhite(target)) return 1;
            }
            break;
        case 'r': // Reglas de la Torre
            if (dr == 0 || dc == 0) return 1;
            break;
        case 'n': // Reglas del Caballo
            if ((abs(dr) == 2 && abs(dc) == 1) || (abs(dr) == 1 && abs(dc) == 2)) return 1;
            break;
        case 'b': // Reglas del Alfil
            if (abs(dr) == abs(dc)) return 1;
            break;
        case 'q': // Reglas de la Reina
            if (dr == 0 || dc == 0 || abs(dr) == abs(dc)) return 1;
            break;
        case 'k': // Reglas del Rey
            if (abs(dr) <= 1 && abs(dc) <= 1) return 1;
            break;
    }
    return 0;
}
//Si es el rey y este se encuentra en peligro, se retorna verdadero.
int isKingInCheck(int turn) {
    int kingRow = -1, kingCol = -1;
    char king = (turn == 1) ? 'K' : 'k';

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == king) {
                kingRow = i;
                kingCol = j;
                break;
            }
        }
    }

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            char piece = board[i][j];
            if ((turn == 1 && !isWhite(piece)) || (turn == 2 && isWhite(piece))) {
                if (isLegalMove(i, j, kingRow, kingCol, 3 - turn)) {
                    return 1;
                }
            }
        }
    }
    return 0;
}
//Se calcula la posicion usando la matriz
int movePiece(const char* from, const char* to, int turn) {
    int fromRow, fromCol, toRow, toCol;
    if (!parsePosition(from, &fromRow, &fromCol) || !parsePosition(to, &toRow, &toCol)) return 0;
    if (!isLegalMove(fromRow, fromCol, toRow, toCol, turn)) return 0;

    char temp = board[toRow][toCol];
    board[toRow][toCol] = board[fromRow][fromCol];
    board[fromRow][fromCol] = ' ';

    if (isKingInCheck(turn)) {
        board[fromRow][fromCol] = board[toRow][toCol];
        board[toRow][toCol] = temp;
        return 0;
    }

    return 1;
}

int main() {
    char from[3], to[3];
    int turn = 1;

    while (1) {
        printBoard();
        printf("Jugador %d (%s), ingrese movimiento (ej. e2 e4): ", turn, turn == 1 ? "Blancas" : "Negras");
        if (scanf("%2s %2s", from, to) != 2) break;

        if (!movePiece(from, to, turn)) {
            printf("\nMovimiento ilegal. Intenta de nuevo.\n\n");
            continue;
        }

        if (isKingInCheck(3 - turn)) {
            printf("\nJaque al rey del Jugador %d!\n\n", 3 - turn);
        }

        turn = 3 - turn; // Alternar turno
    }

    return 0;
}
