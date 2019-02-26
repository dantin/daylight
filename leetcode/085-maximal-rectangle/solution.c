#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct Object {
    char *s;
    int rows;
    int cols;
};

char **make_matrix(char *s, int rows, int cols)
{
    if (rows < 1 || cols < 1 || strlen(s) < rows * cols) {
        return NULL;
    }
    char **matrix = malloc(rows * sizeof(char *));
    int i, j;
    for (i = 0; i < rows; i++) {
        char *line = malloc(cols * sizeof(char));
        for (j = 0; j < cols; j++) {
            line[j] = s[i * cols + j];
        }
        matrix[i] = line;
    }

    return matrix;
}

void print_line(char *line, int size)
{
    if (size < 1) {
        printf("[]");
        return;
    }
    int i;
    printf("[\"%c\"", line[0]);
    for (i = 1; i < size; i++) {
        printf(", \"%c\"", line[i]);
    }
    printf("]");
}

void print_matrix(char **matrix, int rows, int cols)
{
    if (rows < 1) {
        printf("[]\n");
        return;
    }
    int i, indent = 2;;
    printf("[\n%*s", indent, "");
    print_line(matrix[0], cols);
    for (i = 1; i < rows; i++) {
        printf(",\n%*s", indent, "");
        print_line(matrix[i], cols);
    }
    printf(",\n]");
}

void free_matrix(char **matrix, int rows)
{
    int i;
    for (i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int max(int lhs, int rhs)
{
    return lhs > rhs ? lhs : rhs;
}

int area_calc(int *heights, int size)
{
    int *indexes = malloc(size * sizeof(int));
    int *left = malloc(size * sizeof(int));
    int *right = malloc(size * sizeof(int));

    int i, pos = 0;
    for (i = 0; i < size; i++) {
        while (pos > 0 && heights[indexes[pos - 1]] >= heights[i]) {
            pos--;
        }
        left[i] = pos == 0 ? -1 : indexes[pos - 1];
        indexes[pos++] = i;
    }

    pos = 0;
    for (i = size - 1; i >= 0; i--) {
        while (pos > 0 && heights[indexes[pos - 1]] >= heights[i]) {
            pos--;
        }
        right[i] = pos == 0 ? size : indexes[pos - 1];
        indexes[pos++] = i;
    }

    int max_area = 0;
    for (i = 0; i < size; i++) {
        int area = heights[i] * (right[i] - left[i] - 1);
        max_area = max(area, max_area);
    }

    free(indexes);
    free(left);
    free(right);

    return max_area;
}

int maximal_rectangle(char **matrix, int matrix_row_size, int matrix_col_size)
{
    int i, j, max_area = 0;
    int *heights = malloc(matrix_col_size * sizeof(int));
    memset(heights, 0, matrix_col_size * sizeof(int));
    for (i = 0; i < matrix_row_size; i++) {
        for (j = 0; j < matrix_col_size; j++) {
            heights[j] = matrix[i][j] == '1' ? heights[j] + 1 : 0;
        }
        max_area = max(max_area, area_calc(heights, matrix_col_size));
    }

    free(heights);

    return max_area;
}

int main(int argc, char **argv)
{
    char *s1 = "10100101111111110010";
    int rows1 = 4, cols1 = 5;
    struct Object inputs[] = {
        { .s = s1, .rows = rows1, .cols = cols1 },
    };
    int i, len = sizeof(inputs) / sizeof(struct Object);

    for (i = 0; i < len; i++) {
        char *s = inputs[i].s;
        int rows = inputs[i].rows;
        int cols = inputs[i].cols;

        char **matrix = make_matrix(s, rows, cols);
        printf("\n Input:\n");
        print_matrix(matrix, rows, cols);
        printf("\n");

        int area = maximal_rectangle(matrix, rows, cols);
        printf(" Output: %d\n", area);

        free_matrix(matrix, rows);
    }

    return EXIT_SUCCESS;
}
