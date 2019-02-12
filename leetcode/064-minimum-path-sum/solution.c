#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Object {
    int *nums;
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
    printf("[%d", nums[0]);
    for (i = 1; i < size; i++) {
        printf(", %d", nums[i]);
    }
    printf("]");
}

void print_grid(int **grid, int rows, int cols)
{
    int i, indent = 2;
    if (rows < 1) {
        printf("[]\n");
        return;
    }
    printf("[\n%*s", indent, "");
    print_nums(grid[0], cols);
    for (i = 1; i < rows; i++) {
        printf(",\n%*s", indent, "");
        print_nums(grid[i], cols);
    }
    printf("\n]\n");
}

int **make_grid(int *nums, int rows, int cols)
{
    if (rows < 1 || cols < 1) {
        return NULL;
    }

    int **grid = malloc(rows * sizeof(int *));
    int i, j;
    for (i = 0; i < rows; i++) {
        grid[i] = malloc(cols * sizeof(int));
        for (j = 0; j < cols; j++) {
            grid[i][j] = nums[i * cols + j];
        }
    }

    return grid;
}

inline int min(int lhs, int rhs)
{
    return lhs < rhs ? lhs : rhs;
}

int min_path_sum(int **grid, int grid_row_size, int grid_col_size)
{
    int i, j;
    int **dp = malloc(grid_row_size * sizeof(int *));
    for (i = 0; i < grid_row_size; i++) {
        dp[i] = malloc(grid_col_size * sizeof(int));
    }

    dp[0][0] = grid[0][0];
    int sum = dp[0][0];
    for (i = 1; i < grid_row_size; i++) {
        sum += grid[i][0];
        dp[i][0] = sum;
    }
    sum = dp[0][0];
    for (i = 1; i < grid_col_size; i++) {
        sum += grid[0][i];
        dp[0][i] = sum;
    }

    for (i = 1; i < grid_row_size; i++) {
        for (j = 1; j < grid_col_size; j++) {
            dp[i][j] = grid[i][j] + min(dp[i - 1][j], dp[i][j - 1]);
        }
    }

    return dp[grid_row_size - 1][grid_col_size - 1];
}

int main(int argc, char **argv)
{
    int nums1[] = {1, 3, 1, 1, 5, 1, 4, 2, 1};
    struct Object inputs[] = {
        {.nums = nums1, .rows = 3, .cols = 3},
    };
    int i, len = sizeof(inputs) / sizeof(struct Object);

    for (i = 0; i < len; i++) {
        int *nums = inputs[i].nums;
        int rows = inputs[i].rows, cols = inputs[i].cols;
        int **grid = make_grid(nums, rows, cols);
        printf("\n Inputs:\n");
        print_grid(grid, rows, cols);
        int path = min_path_sum(grid, rows, cols);
        printf(" Output: %d\n", path);
    }

    return EXIT_SUCCESS;
}
