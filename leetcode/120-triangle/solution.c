#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct Object {
    int row_size;
    int *nums;
};

int **make_triangle(int *nums, int row_size, int **col_sizes) {
    if (row_size < 1) {
        return NULL;
    }

    int i, j, pos = 0;
    *col_sizes = malloc(row_size * sizeof(int));
    int **triangle = malloc(row_size * sizeof(int *));
    for (i = 0; i < row_size; i++) {
        int size = i + 1;
        (*col_sizes)[i] = size;
        triangle[i] = malloc(size * sizeof(int));
        for (j = 0; j < size; j++) {
            triangle[i][j] = nums[pos++];
        }
    }

    return triangle;
}

void print_nums(int *nums, int size)
{
    if (size < 1) {
        printf("[]");
        return;
    }
    int i;
    printf("[%d", nums[0]);
    for (i = 1; i < size; i++) {
        printf(", %d", nums[i]);
    }
    printf("]");
}

void print_triangle(int **triangle, int row_size, int *triangle_col_sizes)
{
    if (row_size < 1) {
        printf("[]\n");
        return;
    }
    int i = 0, indent = 2;
    printf("[\n%*s", indent, "");
    print_nums(triangle[i], triangle_col_sizes[i]);
    for (i = 1; i < row_size; i++) {
        printf(",\n%*s", indent, "");
        print_nums(triangle[i], triangle_col_sizes[i]);
    }
    printf("\n]\n");
}

void free_triangle(int **triangle, int row_size)
{
    int i;
    for (i = 0; i < row_size; i++) {
        free(triangle[i]);
    }
    free(triangle);
}

int dfs(int **triangle, int row_size, int *col_sizes,
        int row, int col, int **sums, bool **passes)
{
    if (row == row_size - 1) {
        return triangle[row][col];
    } else if (passes[row][col]) {
        return sums[row][col];
    } else {
        int s1 = dfs(triangle, row_size, col_sizes, row + 1, col, sums, passes);
        int s2 = dfs(triangle, row_size, col_sizes, row + 1, col + 1, sums, passes);
        sums[row][col] = triangle[row][col] + (s1 < s2 ? s1 : s2);
        passes[row][col] = true;
        return sums[row][col];
    }
}

int minimum_total(int **triangle, int triangle_row_size, int *triangle_col_sizes)
{
    int i;
    bool **passes = malloc(triangle_row_size * sizeof(bool *));
    for (i = 0; i < triangle_row_size; i++) {
        passes[i] = malloc(triangle_col_sizes[i]);
        memset(passes[i], false, triangle_col_sizes[i]);
    }
    int **sums = malloc(triangle_row_size * sizeof(int *));
    for (i = 0; i < triangle_row_size; i++) {
        sums[i] = malloc(triangle_col_sizes[i] * sizeof(int));
    }
    int weight = dfs(triangle, triangle_row_size, triangle_col_sizes, 0, 0, sums, passes);

    for (i = 0; i < triangle_row_size; i++) {
        free(passes[i]);
        free(sums[i]);
    }
    free(passes);
    free(sums);

    return weight;
}

int main(int argc, char **argv)
{
    int nums1[] = { 2, 3, 4, 5, 6, 7, 4, 1, 8, 3 }, row_size1 = 4;
    struct Object inputs[] = {
        { .nums = nums1, .row_size = row_size1},
    };
    int i, len = sizeof(inputs) / sizeof(struct Object);

    for (i = 0; i < len; i++) {
        int *nums = inputs[i].nums;
        int row_size = inputs[i].row_size;

        int *triangle_col_sizes = NULL;
        int **triangle = make_triangle(nums, row_size, &triangle_col_sizes);
        printf("\n Input:\n");
        print_triangle(triangle, row_size, triangle_col_sizes);
        
        int total = minimum_total(triangle, row_size, triangle_col_sizes);
        printf("\n Output: %d\n", total);

        free_triangle(triangle, row_size);
        free(triangle_col_sizes);
    }

    return EXIT_SUCCESS;
}
