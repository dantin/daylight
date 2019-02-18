#include <stdio.h>
#include <stdlib.h>

struct Object {
    int *nums;
    int rows;
    int cols;
};

int **make_matrix(int *nums, int rows, int cols)
{
    if (rows < 1) {
        return NULL;
    }
    int **matrix = malloc(rows * sizeof(int *));
    int i, j;

    for (i = 0; i < rows; i++) {
        int *row = malloc(cols * sizeof(int));
        for (j = 0; j < cols; j++) {
            row[j] = nums[i * cols + j];
        }
        matrix[i] = row;
    }

    return matrix;
}

void print_nums(int *nums, int size)
{
    if (size < 1) {
        printf("[]");
        return;
    }

    int i;
    printf("[%d", nums[0]);
    for (i = 1; i  < size; i++) {
        printf(", %d", nums[i]);
    }
    printf("]");
}

void print_matrix(int **matrix, int rows, int cols)
{
    if (rows < 1) {
        printf("[]\n");
        return;
    }

    int i, indent = 2;
    printf("[\n%*s", indent, "");
    print_nums(matrix[0], cols);
    for (i = 1; i < rows; i++) {
        printf(",\n%*s", indent, "");
        print_nums(matrix[i], cols);
    }
    printf("\n]\n");
}

void delete_matrix(int **matrix, int rows)
{
    int i;
    for (i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

void set_zeroes(int **matrix, int matrix_row_size, int matrix_col_size)
{
    int row, col, row_flag = 0, col_flag = 0;
    for (row = 0; row < matrix_row_size; row++) {
        for (col = 0; col < matrix_col_size; col++) {
            if (matrix[row][col] == 0) {
                if (row == 0) col_flag = 1;
                if (col == 0) row_flag = 1;
                matrix[0][col] = matrix[row][0] = 0;
            }
        }
    }

    for (row = 1; row < matrix_row_size; row++) {
        for (col = 1; col < matrix_col_size; col++) {
            if (matrix[0][col] == 0 || matrix[row][0] == 0) {
                matrix[row][col] = 0;
            }
        }
    }

    if (row_flag) {
        for (row = 0; row < matrix_row_size; row++) {
            matrix[row][0] = 0;
        }
    }

    if (col_flag) {
        for (col = 0; col < matrix_col_size; col++) {
            matrix[0][col] = 0;
        }
    }
}

int main(int argc, char **argv)
{
    int nums1[] = {1, 1, 1, 1, 0, 1, 1, 1, 1},          rows1 = 3, cols1 = 3;
    int nums2[] = {0, 1, 2, 0, 3, 4, 5, 2, 1, 3, 1, 5}, rows2 = 3, cols2 = 4;
    struct Object inputs[] = {
        { .nums = nums1, .rows = rows1, .cols = cols1 },
        { .nums = nums2, .rows = rows2, .cols = cols2 },
    };
    int i, len = sizeof(inputs) / sizeof(struct Object);

    for (i = 0; i < len; i++) {
        int *nums = inputs[i].nums;
        int rows = inputs[i].rows;
        int cols = inputs[i].cols;
        int **matrix = make_matrix(nums, rows, cols);
        printf("\n Input:\n");
        print_matrix(matrix, rows, cols);
        set_zeroes(matrix, rows, cols);
        printf(" Output:\n");
        print_matrix(matrix, rows, cols);
        delete_matrix(matrix, rows);
    }

    return EXIT_SUCCESS;
}
