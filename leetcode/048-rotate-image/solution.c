#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct object {
    int *nums;
    int len;
};

struct matrix {
    int **matrix;
    int rows;
    int cols;
};

void print_nums(int *nums, int size)
{
    int i;

    if (size < 1) {
        printf("[]");
        return;
    }

    printf("[%2d", nums[0]);
    for (i = 1; i < size; i++) {
        printf(", %2d", nums[i]);
    }
    printf("]");
}

void print_matrix(int **matrix, int rows, int cols)
{
    int i, indent = 2;

    if (rows < 1) {
        printf("[]\n");
        return;
    }

    if (rows < 1) {
        printf("[]\n");
    }
    printf("[\n%*s", indent, "");
    print_nums(matrix[0], cols);
    for (i = 1; i < rows; i++) {
        printf(",\n%*s", indent, ""); print_nums(matrix[i], cols);
    }
    printf("\n]\n");
}


struct matrix *build_matrix(int *nums, int size)
{
    int i, j, len = (int) sqrt((double) size);

    int **matrix = (int **) malloc(len * sizeof(int *));

    for (i = 0; i < len; i++) {
        int *row = (int *) malloc(len * sizeof(int));
        for (j = 0; j < len; j++) {
            row[j] = nums[i * len + j];
        }
        matrix[i] = row;
    }

    struct matrix *result = (struct matrix *) malloc(sizeof(struct matrix));
    result->matrix = matrix;
    result->rows = len;
    result->cols = len;

    return result; 
}

void rotate(int **matrix, int matrix_row_size, int *matrix_col_sizes)
{
    int i, j, matrix_col_size = *matrix_col_sizes;
    if (matrix_row_size != matrix_col_size) {
        return;
    }

    for (i = 0; i < matrix_row_size / 2; i++) {
        int low = i, high = matrix_col_size - i - 1;
        for (j = low; j < high; j++) {
            int tmp = matrix[i][j];
            matrix[i][j] = matrix[matrix_col_size - 1 - j][i];
            matrix[matrix_col_size - 1 - j][i] = matrix[matrix_row_size - 1 - i][matrix_col_size - 1 - j];
            matrix[matrix_row_size - 1 - i][matrix_col_size - 1 - j] = matrix[j][matrix_row_size - 1 - i];
            matrix[j][matrix_row_size - 1 - i] = tmp;
        }
    }
}

int main(int argc, char **argv)
{
    int nums1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9},                             len1 = sizeof(nums1) / sizeof(int);
    int nums2[] = {5, 1, 9, 11, 2, 4, 8, 10, 13, 3, 6, 7, 15, 14, 12, 16}, len2 = sizeof(nums2) / sizeof(int);
    struct object inputs[] = {
        {.nums = nums1, .len = len1},
        {.nums = nums2, .len = len2},
    };
    int i, len = sizeof(inputs) / sizeof(struct object);

    for (i = 0; i < len; i++) {
        int *nums = inputs[i].nums;
        int size = inputs[i].len;

        printf("\n Input matrix =\n");
        struct matrix *matrix = build_matrix(nums, size);
        print_matrix(matrix->matrix, matrix->rows, matrix->cols);

        rotate(matrix->matrix, matrix->rows, &matrix->cols);

        printf("\n Inplace rotate =\n");
        print_matrix(matrix->matrix, matrix->rows, matrix->cols);
    }

    return EXIT_SUCCESS;
}
