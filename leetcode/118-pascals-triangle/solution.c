#include <stdio.h>
#include <stdlib.h>

void print_nums(int *nums, int size)
{
    if (size < 1) {
        printf("[]");
        return;
    }
    printf("[%d", nums[0]);
    int i;
    for (i = 1; i < size; i++) {
        printf(", %d", nums[i]);
    }
    printf("]");
}

int **generate(int num_rows, int **column_sizes)
{
    int i, j;
    int **triangle = malloc(num_rows * sizeof(int *));
    *column_sizes = malloc(num_rows * sizeof(int *));
    for (i = 0; i < num_rows; i++) {
        int num = i + 1;
        (*column_sizes)[i] = num;
        triangle[i] = malloc(num * sizeof(int));
        triangle[i][0] = 1;
        triangle[i][num - 1] = 1;
        for (j = 1; j <= num - 2; j++) {
            triangle[i][j] = triangle[i - 1][j - 1] + triangle[i - 1][j];
        }
    }
    return triangle;
}

int main(int argc, char **argv)
{
    int inputs[] = { 5 };
    int i, j, len = sizeof(inputs) / sizeof(int);
    int *sizes, indent = 2;

    for (i = 0; i < len; i++) {
        int rows = inputs[i];

        printf("\n Input: %d\n", rows);
        int **triangle = generate(rows, &sizes);
        if (rows < 1) {
            printf("[]\n");
            continue;
        }
        printf("[\n%*s", indent, "");
        j = 0;
        print_nums(triangle[j], sizes[j]);
        for (j = 1; j < rows; j++) {
            printf(",\n%*s", indent, "");
            print_nums(triangle[j], sizes[j]);
        }
        printf("\n]\n");

        for (j = 0; j < rows; j++) {
            free(triangle[j]);
        }
        free(triangle);
        free(sizes);
    }

    return EXIT_SUCCESS;
}
