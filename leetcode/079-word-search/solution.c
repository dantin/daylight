#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct Object {
    char **board;
    int rows;
    int cols;
    char *word;
};

char **make_board(char *s, int rows, int cols)
{
    if (rows < 1 || cols < 1 || rows * cols > strlen(s)) {
        return NULL;
    }
    char **board = malloc(rows * sizeof(char *));
    int i, j;

    for (i = 0; i < rows; i++) {
        char *line= malloc(cols * sizeof(char));
        for (j = 0; j < cols; j++) {
            line[j] = s[i * cols + j];
        }
        board[i] = line;
    }

    return board;
}

void print_line(char *line, int size)
{
    if (size < 1) {
        printf("[]");
        return;
    }

    int i;
    printf("[\'%c\'", line[0]);
    for (i = 1; i < size; i++) {
        printf(", \'%c\'", line[i]);
    }
    printf("]");
}

void print_board(char **board, int rows, int cols)
{
    int i, indent = 2;
    if (rows < 1) {
        printf("[]\n");
        return;
    }
    printf("[\n%*s", indent, "");
    print_line(board[0], cols);
    for (i = 1; i < rows; i++) {
        printf(",\n%*s", indent, "");
        print_line(board[i], cols);
    }
    printf("\n]\n");
}

void free_board(char **board, int rows)
{
    int i;
    for (i = 0; i < rows; i++) {
        free(board[i]);
    }
    free(board);
}

bool dfs(char *word, char **board, bool *used,
         int row, int col, int row_size, int col_size)
{
    if (board[row][col] != *word) {
        return false;
    }

    used[row * col_size + col] = true;

    if (*(word + 1) == '\0') {
        return true;
    }

    bool result = false;
    if (row > 0 && !used[(row - 1) * col_size + col]) {
        result = dfs(word + 1, board, used, row - 1, col, row_size, col_size);
    }

    if (!result && row < row_size - 1 && !used[(row + 1) * col_size + col]) {
        result = dfs(word + 1, board, used, row + 1, col, row_size, col_size);
    }

    if (!result && col > 0 && !used[row * col_size + col - 1]) {
        result = dfs(word + 1, board, used, row, col - 1, row_size, col_size);
    }

    if (!result && col < col_size - 1 && !used[row * col_size + col + 1]) {
        result = dfs(word + 1, board, used, row, col + 1, row_size, col_size);
    }

    used[row * col_size + col] = false;
    return result;
}

bool exist(char **board, int board_row_size, int board_col_size, char *word)
{
    int i, j;
    int len = strlen(word);
    if (len > board_row_size * board_col_size) {
        return false;
    }
    bool *used = malloc(board_row_size * board_col_size);
    for (i = 0; i < board_row_size; i++) {
        for (j = 0; j < board_col_size; j++) {
            memset(used, false, board_row_size * board_col_size);
            if (dfs(word, board, used, i, j, board_row_size, board_col_size)) {
                free(used);
                return true;
            }
        }
    }

    free(used);
    return false;
}

int main(int argc, char **argv)
{
    int row_size = 3, col_size = 4;
    char *s = "ABCESFCSADEE";
    char **board = make_board(s, row_size, col_size);
    struct Object inputs[] = {
        { .board = board, .rows = row_size, .cols = col_size, .word = "ABCCED" },
        { .board = board, .rows = row_size, .cols = col_size, .word = "SEE" },
        { .board = board, .rows = row_size, .cols = col_size, .word = "ABCB" },
    };
    int i, len = sizeof(inputs) / sizeof(struct Object);

    printf("board =\n");
    print_board(board, row_size, col_size);
    printf("\n");
    for (i = 0; i < len; i++) {
        char **boards = inputs[i].board;
        int rows = inputs[i].rows;
        int cols = inputs[i].cols;
        char *word = inputs[i].word;

        printf("Given word = \"%s\"", word);
        bool found = exist(boards, rows, cols, word);
        printf(", return %s.\n", found ? "true" : "false");
    }
    free_board(board, row_size);

    return EXIT_SUCCESS;
}
