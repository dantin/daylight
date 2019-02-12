#include <stdio.h>
#include <stdlib.h>

struct Object {
    int *nums;
    int rows;
    int cols;
};

int **make_grid(int *nums, int rows, int cols)
{
    if (rows <= 0 || cols <= 0) {
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
    printf("[\n");
    printf("%*s", indent, "");
    print_nums(grid[0], cols);
    for (i = 1; i < rows; i++) {
        printf(",\n%*s", indent, "");
        print_nums(grid[i], cols);
    }
    printf("\n]\n");
}

int unique_paths_with_obstacles(int **obstacle_grid, int obstacle_grid_row_size, int obstacle_grid_col_size)
{
    int row, col, reset = 0;
    for (row = 0; row < obstacle_grid_row_size; row++) {
        if (reset) {
            obstacle_grid[row][0] = 1;
        } else {
            if (obstacle_grid[row][0] == 1) {
                reset = 1;
            }
        }
    }

    reset = 0;
    for (col = 0; col < obstacle_grid_col_size; col++) {
        if (reset) {
            obstacle_grid[0][col] = 1;
        } else {
            if (obstacle_grid[0][col] == 1) {
                reset = 1;
            }
        }
    }

    for (row = 0; row < obstacle_grid_row_size; row++) {
        int *line = obstacle_grid[row];
        for (col = 0; col < obstacle_grid_col_size; col++) {
            line[col] ^= 1;
        }
    }

    for (row = 1; row < obstacle_grid_row_size; row++) {
        int *last_line = obstacle_grid[row - 1];
        int *line = obstacle_grid[row];
        for (col = 1; col < obstacle_grid_col_size; col++) {
            if (line[col] != 0) {
                line[col] = line[col - 1] + last_line[col];
            }
        }
    }

    return obstacle_grid[obstacle_grid_row_size - 1][obstacle_grid_col_size - 1];
}

int main(int argc, char **argv)
{
    int nums1[] = {0, 0, 0, 0, 1, 0, 0, 0, 0};
    int nums2[] = {0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1 ,0 ,1 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1 ,0 ,0 ,0 ,0 ,0 ,1 ,0 ,0 ,0 ,0 ,0 ,0 ,0 , 0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1 ,0 ,0 ,0 ,0 ,1 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1 , 0 ,0 ,0 ,0 ,0 ,1 ,0 ,1 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1 ,0 ,0 ,0 ,0 ,1 ,0 ,0 ,0 ,0 ,0 ,0 , 1 ,1 ,1 ,0 ,0 ,0 ,0 ,1 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1 ,0 ,0 ,1 ,1 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1 ,0 ,0 ,1 , 0 ,0 ,1 ,0 ,0 ,1 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1 ,0 ,0 ,0 ,1 ,0 ,0 ,0 ,0 ,0 , 0 ,0 ,0 ,1 ,0 ,1 ,0 ,0 ,0 ,0 ,1 ,1 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1 ,1 ,0 , 1 ,0 ,1 ,1 ,1 ,0 ,0 ,0 ,0 ,1 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1 ,0 ,0 ,0 ,0 ,0 ,1 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 , 0 ,0 ,1 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1 ,0 ,0 ,1 ,0 ,1 ,0 ,0 ,0 ,1 ,0 ,1 ,0 ,0 ,0 ,0 ,0 ,0 , 0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1 ,1 ,0 ,0 ,1 ,0 , 0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1 ,1 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1 ,1 ,0 ,0 ,0 ,1 ,0 ,0 ,0 ,0 ,0 , 0 ,1 ,1 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1 ,0 ,0 ,0 ,1 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 , 1 ,0 ,1 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1 ,0 ,0 ,1 ,0 ,0 ,0 ,0 ,1 ,0 ,1 ,0 ,0 ,0 ,1 ,0 ,1 ,0 ,0 ,0 ,0 ,1 , 0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1 ,0 ,0 ,0 ,0 ,0 ,1 ,0 ,1 ,0 ,0 ,0 ,0 ,0 ,0 ,1 ,1 ,0 ,0 ,0 ,0 ,0 , 0 ,1 ,0 ,1 ,0 ,0 ,0 ,0 ,1 ,0 ,0 ,1 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1 ,1 ,0 ,0 ,0 ,0 ,0 ,0 ,1 ,0 ,0 ,0 ,0 ,0 , 0 ,1 ,0 ,0 ,0 ,0 ,0 ,0 ,1 ,0 ,0 ,1 ,1 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1 ,0 ,0 ,1 ,1 ,0 ,1 , 1 ,0 ,0 ,0 ,0 ,1 ,0 ,0 ,1 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 , 0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1 ,0 ,0 ,1 ,0 ,0 ,0 ,0 ,1 ,1 ,0 ,0 ,1 ,0 ,0 ,0 ,0 ,0 ,0 , 0 ,0 ,1 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1 ,0 ,0 ,1 ,0 ,0 ,1 ,0 ,0 ,0 ,0 ,0 ,0 ,1 ,1 ,0 ,1 ,0 ,0 ,0 ,0 ,1 ,1 , 0 ,1 ,0 ,0 ,1 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1 ,0 ,1 ,1 ,0 ,1 ,0 ,1 , 1 ,1 ,1 ,0 ,1 ,0 ,0 ,0 ,0 ,1 ,0 ,0 ,0 ,0 ,0 ,0 ,1 ,0 ,1 ,0 ,1 ,1 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 , 0 ,0 ,0 ,0 ,1 ,1 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1 ,0 ,0 ,0 ,1 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1 ,1 , 0 ,0 ,0 ,1 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,1 ,0 ,0 ,0 ,0 ,0 ,1 ,0 ,1 ,0 ,0 ,0 ,1 ,0 ,0 ,0};
    struct Object inputs[] = {
        {.nums = nums1, .rows = 3, .cols = 3},
        {.nums = nums2, .rows = 22, .cols = 33},
    };
    int i, len = sizeof(inputs) / sizeof(struct Object);

    for (i = 0; i < len; i++) {
        int *nums = inputs[i].nums;
        int rows = inputs[i].rows, cols = inputs[i].cols;
        int **grid = make_grid(nums, rows, cols);
        printf("\n Inputs:\n");
        print_grid(grid, rows, cols);
        int solution = unique_paths_with_obstacles(grid, rows, cols);
        printf(" Output: %d\n", solution);
    }

    return EXIT_SUCCESS;
}
