#include <stdio.h>
#include <stdlib.h>

void print_nums(int *nums, int size)
{
    if (size < 1) {
        printf("[]\n");
        return;
    }

    int i;
    printf("[%d", nums[0]);
    for (i = 1; i < size; i++) {
        printf(", %d", nums[i]);
    }
    printf("]\n");
}

int *get_row(int row_index, int *return_size)
{
    int *row = malloc((row_index + 1) * sizeof(int));
    *return_size = row_index + 1;

    int num = row_index + 1;
    if (row_index < 1) {
        row[0] = 1;
        return row;
    }

    int i, j;
    for (i = 1; i <= row_index; i++) {
        num = i + 1;
        row[0] = 1;
        row[num - 1] = 1;
        for (j = num - 2; j >= 1; j--) {
            row[j] = row[j - 1] + row[j];
        }
    }

    return row;
}

int main(int argc, char **argv)
{
    int inputs[] = { 3 };
    int i, return_size, len = sizeof(inputs) / sizeof(int);

    for (i = 0; i < len; i++) {
        int row_index = inputs[i];

        printf("\n Input: %d\n", row_index);
        int *row = get_row(row_index, &return_size);
        printf(" Output: ");
        print_nums(row, return_size);
        free(row);
    }

    return EXIT_SUCCESS;
}
