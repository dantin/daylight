#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Object {
    int *nums;
    int rows;
    int cols;
    int target;
};

int **make_matrix(int *nums, int rows, int cols)
{
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

void delete_matrix(int **matrix, int rows)
{
    int i;
    for (i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

void print_nums(int *nums, int size)
{
    if (size < 1) {
        printf("[]");
        return;
    }
    int i;
    printf("[%2d", nums[0]);
    for (i = 1; i < size; i++) {
        printf(", %2d", nums[i]);
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

int binary_search(int *nums, int len, int target)
{
    int low = -1;
    int high = len;
    while (low + 1 < high) {
        int mid = low + (high - low) / 2;
        if (target > nums[mid]) {
            low = mid;
        } else {
            high = mid;
        }
    }
    if (high == len || nums[high] != target) {
        return -high - 1;
    } else {
        return high;
    }
}

bool search_matrix(int **matrix, int matrix_row_size, int matrix_col_size, int target)
{
    if (matrix_row_size == 0 || matrix_col_size == 0) {
        return false;
    }

    if (target < matrix[0][0] || target > matrix[matrix_row_size - 1][matrix_col_size - 1]) {
        return false;
    }

    int row = 0;
    int *nums = NULL;
    if (matrix_row_size > 0) {
        nums = malloc(matrix_row_size * sizeof(int));
        for (row = 0; row < matrix_row_size; row++) {
            nums[row] = matrix[row][0];
        }

        row = binary_search(nums, matrix_row_size, target);
        if (row >= 0) {
            return true;
        } else {
            row = -row - 1;
            if (row == 0) {
                return false;
            } else {
                row--;
            }
        }
        free(nums);
    }
    int col = binary_search(matrix[row], matrix_col_size, target);
    return col >= 0;
}

int main(int argc, char **argv)
{
    int nums1[] = {1, 3, 5, 7, 10, 11, 16, 20, 23, 30, 34, 50}, rows1 = 3, cols1 = 4, target1 = 3;
    int nums2[] = {1, 3, 5, 7, 10, 11, 16, 20, 23, 30, 34, 50}, rows2 = 3, cols2 = 4, target2 = 13;
    struct Object inputs[] = {
        { .nums = nums1, .rows = rows1, .cols = cols1, .target = target1 },
        { .nums = nums2, .rows = rows2, .cols = cols2, .target = target2 },
    };
    int i, len = sizeof(inputs) / sizeof(struct Object);

    for (i = 0; i < len; i++) {
        int *nums = inputs[i].nums;
        int rows = inputs[i].rows;
        int cols = inputs[i].cols;
        int target = inputs[i].target;
        int **matrix = make_matrix(nums, rows, cols);

        printf("\n Input:\n");
        print_matrix(matrix, rows, cols);
        printf(" target = %d\n", target);

        bool found = search_matrix(matrix, rows, cols, target);
        printf("\n Output: %s\n", found ? "true" : "false");

        delete_matrix(matrix, rows);
    }
    return EXIT_SUCCESS;
}
