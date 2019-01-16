#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define SIZE 9

struct object {
    char *board;
    int rows;
    int cols;
};

struct stack {
    int row;
    int col;
    int value;
};

char **make_2d(char *board, int rows, int cols)
{
    int i, j;
    char **result = malloc(rows * sizeof(char *));

    for (i = 0; i < rows; i++) {
        result[i] = malloc(cols * sizeof(char));
        for (j = 0; j < cols; j++) {
            result[i][j] = board[i * cols + j];
        }
    }

    return result;
}

void print_board(char **board, int rows, int cols)
{
    int i, j;

    printf("[\n");
    for (i = 0; i < rows; i++) {
        printf("  [");
        for (j = 0; j < cols; j++) {
            if (j == 0) {
                printf("%c", board[i][j]);
            } else {
                printf(", %c", board[i][j]);
            }
        }
        printf("]");
        printf("%s", (i != rows -1) ? ",\n" : "\n");
    }
    printf("]\n");
}

bool valid(char **board, int row, int col)
{
    int i, j, k;
    char mark[10];

    // check row validity
    for (i = 0; i < row; i++) {
        memset(mark, 0, 10);
        for (j = 0; j < SIZE; j++) {
            if (board[i][j] != '.') {
                int idx = board[i][j] - '0';
                if (mark[idx]) {
                    return false;
                } else {
                    mark[idx] = 1;
                }
            }
        }
    }

    // check column validity
    for (i = 0; i <= col; i++) {
        memset(mark, 0, 10);
        for (j = 0; j < SIZE; j++) {
            if (board[j][i] != '.') {
                int idx = board[j][i] - '0';
                if (mark[idx]) {
                    return false;
                } else {
                    mark[idx] = 1;
                }
            }
        }
    }

    // check sub-box validity
    int count = row / 3 * 3 + col / 3 + 1;
    for (k = 0; k < count; k++) {
        int sr = k / 3 * 3;
        int sc = (k % 3) * 3;
        memset(mark, 0, 10);
        for (i = sr; i < sr + 3; i++) {
            for (j = sc; j < sc + 3; j++) {
                if (board[i][j] != '.') {
                    int idx = board[i][j] - '0';
                    if (mark[idx]) {
                        return false;
                    } else {
                        mark[idx] = 1;
                    }
                }
            }
        }
    }

    return true;
}

void solve_sudoku(char **board, int board_row_size, int board_col_size)
{
    if (board_row_size != SIZE || board_col_size != SIZE) {
        return;
    }

    int i = 0, j = 0, k = 1, top = 0;
    struct stack stack[SIZE * SIZE];

    while (i < board_row_size) {
        if (board[i][j] == '.') {
            while (k <= SIZE) {
                board[i][j] = k + '0';
                if (valid(board, i, j)) {
                    stack[top].row = i;
                    stack[top].col = j;
                    stack[top].value = k;
                    top++;
                    k = 1;
                    break;
                }
                k++;
            }
            if (k == SIZE + 1) {
                if (top == 0) {
                    return;
                }
                board[i][j] = '.';
                --top;
                i = stack[top].row;
                j = stack[top].col;
                k = stack[top].value + 1;
                board[i][j] = '.';
                continue;
            }
        }
        // next row
        if (++j == board_col_size) {
            j = 0;
            i++;
        }
    }
}

int main(int argc, char **argv)
{
    char *board1 =
        "53..7...."
        "6..195..."
        ".98....6."
        "8...6...3"
        "4..8.3..1"
        "7...2...6"
        ".6....28."
        "...419..5"
        "....8..79";

    struct object inputs[] = {
        {.board = board1, .rows = SIZE, .cols = SIZE},
    };
    int i, len = sizeof(inputs) / sizeof(struct object);

    for (i = 0; i < len; i++) {
        char *data = inputs[i].board;
        int rows = inputs[i].rows;
        int cols = inputs[i].cols;
        char **board = make_2d(data, rows, cols);
        printf("\n Input:\n");
        print_board(board, rows, cols);
        solve_sudoku(board, rows, cols);
        printf(" Output:\n");
        print_board(board, rows, cols);
    }

    return EXIT_SUCCESS;
}
