#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct object {
    int *nums;
    int rows;
    int cols;
};

void print_nums(int *nums, int size)
{
    int i;

    if (size < 1) {
        printf("[]\n");
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

    printf("[\n%*s", indent, "");
    print_nums(matrix[0], cols);
    for (i = 1; i < rows; i++) {
        printf(",\n%*s", indent, ""); print_nums(matrix[i], cols);
    }
    printf("\n]\n");
}

int **build_matrix(int *nums, int rows, int cols)
{
    int i, j;

    int **matrix = malloc(rows * sizeof(int *));

    for (i = 0; i < rows; i++) {
        int *row = malloc(cols* sizeof(int));
        for (j = 0; j < cols; j++) {
            row[j] = nums[i * cols + j];
        }
        matrix[i] = row;
    }

    return matrix;
}

int *spiral_order(int **matrix, int matrix_row_size, int matrix_col_size)
{
    int top = 0, bottom = matrix_row_size - 1, left = 0, right = matrix_col_size - 1;
    int count = 0, i, direction  = 0;
    int *nums = malloc(matrix_row_size * matrix_col_size * sizeof(int));

    while (top <= bottom && left <= right) {
        switch (direction) {
            case 0:
                for (i = left; i <= right; i++) {
                    nums[count++] = matrix[top][i];
                }
                top++;
                break;
            case 1:
                for (i = top; i <= bottom; i++) {
                    nums[count++] = matrix[i][right];
                }
                right--;
                break;
            case 2:
                for (i = right; i >= left; i--) {
                    nums[count++] = matrix[bottom][i];
                }
                bottom--;
                break;
            case 3:
                for (i = bottom; i >= top; i--) {
                    nums[count++] = matrix[i][left];
                }
                left++;
                break;
            default:
                break;
        }
        direction++;
        direction %= 4;
    }

    return nums;
}

int main(int argc, char **argv)
{
    int nums1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9},             rows1 = 3, cols1 = 3;
    int nums2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}, rows2 = 3, cols2 = 4;
    struct object inputs[] = {
        {.nums = nums1, .rows = rows1, .cols = cols1},
        {.nums = nums2, .rows = rows2, .cols = cols2},
    };
    int i, len = sizeof(inputs) / sizeof(struct object);

    for (i = 0; i < len; i++) {
        int *nums = inputs[i].nums;
        int rows = inputs[i].rows;
        int cols = inputs[i].cols;
        int **matrix = build_matrix(nums, rows, cols);
        printf("\n Input:\n");
        print_matrix(matrix, rows, cols);
        int *sprial = spiral_order(matrix, rows, cols);
        printf(" Output: "); print_nums(sprial, rows * cols);
        printf("\n");
    }

    return EXIT_SUCCESS;
}
