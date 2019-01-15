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

void print_board(char *board, int rows, int cols)
{
    int i, j;

    printf("[\n");
    for (i = 0; i < rows; i++) {
        printf("  [");
        for (j = 0; j < cols; j++) {
            if (j == 0) {
                printf("%c", board[i * cols + j]);
            } else {
                printf(", %c", board[i *cols + j]);
            }
        }
        printf("]");
        printf("%s", (i != rows -1) ? ",\n" : "\n");
    }
    printf("]\n");
}

bool is_valid_sudoku(char **board, int board_row_size, int board_col_size)
{
    return false;
}

int main(int argc, char **argv)
{
    char board1[] = {
        '5', '3', '.', '.', '7', '.', '.', '.', '.',
        '6', '.', '.', '1', '9', '5', '.', '.', '.',
        '.', '9', '8', '.', '.', '.', '.', '6', '.',
        '8', '.', '.', '.', '6', '.', '.', '.', '3',
        '4', '.', '.', '8', '.', '3', '.', '.', '1',
        '7', '.', '.', '.', '2', '.', '.', '.', '6',
        '.', '6', '.', '.', '.', '.', '2', '8', '.',
        '.', '.', '.', '4', '1', '9', '.', '.', '5',
        '.', '.', '.', '.', '8', '.', '.', '7', '9',
    };
    char board2[] = {
        '8', '3', '.', '.', '7', '.', '.', '.', '.',
        '6', '.', '.', '1', '9', '5', '.', '.', '.',
        '.', '9', '8', '.', '.', '.', '.', '6', '.',
        '8', '.', '.', '.', '6', '.', '.', '.', '3',
        '4', '.', '.', '8', '.', '3', '.', '.', '1',
        '7', '.', '.', '.', '2', '.', '.', '.', '6',
        '.', '6', '.', '.', '.', '.', '2', '8', '.',
        '.', '.', '.', '4', '1', '9', '.', '.', '5',
        '.', '.', '.', '.', '8', '.', '.', '7', '9',
    };
    struct object inputs[] = {
        {.board = board1, .rows = SIZE, .cols = SIZE},
        {.board = board2, .rows = SIZE, .cols = SIZE},
    };
    int i, len = sizeof(inputs) / sizeof(struct object);

    for (i = 0; i < len; i++) {
        char *board = inputs[i].board;
        int rows = inputs[i].rows;
        int cols = inputs[i].cols;
        print_board(board, rows, cols);
    }

    return EXIT_SUCCESS;
}
