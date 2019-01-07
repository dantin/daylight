#include <stdio.h>
#include <stdlib.h>

struct object {
    int *array;
    int len;
};

void print_array(int *array, int size)
{
    if (size < 1) {
        return;
    }

    int i;
    putchar('[');
    printf("%d", array[0]);
    for (i = 1; i < size; i++) {
        printf(", %d", array[i]);
    }
    printf("]\n");
}

int remove_duplicates(int *array, int size)
{
    if (size == 0) {
        return 0;
    }
    int i, count= 1, val = array[0];
    for (i = 1; i < size; i++) {
        if (array[i] != val) {
            array[count++] = array[i];
            val = array[i];
        }
    }
    return count;
}

int main(int argc, char **argv)
{
    int arr1[] = {1, 1, 2},                      len1 = sizeof(arr1) / sizeof(int);
    int arr2[] = {0, 0, 1, 1, 1, 2, 2, 3, 3, 4}, len2 = sizeof(arr2) / sizeof(int);
    struct object inputs[] = {
        {.array = arr1, .len = len1},
        {.array = arr2, .len = len2},
    };
    int i, size, len = sizeof(inputs) / sizeof(struct object);

    for (i = 0; i < len; i++) {
        printf("\n nums = "); print_array(inputs[i].array, inputs[i].len);
        size = remove_duplicates(inputs[i].array, inputs[i].len);
        printf(" Output: "); print_array(inputs[i].array, size);
    }

    return EXIT_SUCCESS;
}
