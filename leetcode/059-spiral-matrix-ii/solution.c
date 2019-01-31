#include <stdio.h>
#include <stdlib.h>

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

void print_matrix(int **matrix, int n)
{
    int i, indent = 2;

    if (n < 1) {
        printf("[]\n");
        return;
    }

    printf("[\n");
    printf("%*s", indent, "");
    print_nums(matrix[0], n);
    for (i = 1; i < n; i++) {
        printf(",\n%*s", indent, "");
        print_nums(matrix[i], n);
    }
    printf("\n]\n");
}

int **generate_matrix(int n)
{
    int i;
    int **matrix = malloc(n * sizeof(int *));
    for (i = 0; i < n; i++) {
        matrix[i] = malloc(n * sizeof(int));
    }

    int direction = 0, num = 0;
    int top = 0, bottom = n - 1, left = 0, right = n - 1;

    while (num < n * n) {
        switch (direction) {
            case 0:
                for (i = left; i <= right; i++) {
                    matrix[top][i] = ++num;
                }
                top++;
                break;
            case 1:
                for (i = top; i <= bottom; i++) {
                    matrix[i][right] = ++num;
                }
                right--;
                break;
            case 2:
                for (i = right; i >= left; i--) {
                    matrix[bottom][i] = ++num;
                }
                bottom--;
                break;
            case 3:
                for (i = bottom; i >= top; i--) {
                    matrix[i][left] = ++num;
                }
                left++;
                break;
        }
        direction++;
        direction %= 4;
    }

    return matrix;
}

int main(int argc, char **argv)
{
    int inputs[] = { 3 };
    int i, len = sizeof(inputs) / sizeof(int);

    for (i = 0; i < len; i++) {
        int n = inputs[i];
        printf("\n Input: %d\n", n);
        int **matrix = generate_matrix(n);
        printf(" Output:\n"); print_matrix(matrix, n);
    }
    return EXIT_SUCCESS;
}
