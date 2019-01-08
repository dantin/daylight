#include <stdio.h>
#include <stdlib.h>

struct object {
    int *array;
    int len;
    int val;
};


void print_array(int *nums, int size)
{
    if (size < 1) {
        return;
    }

    int i;
    putchar('[');
    printf("%d", nums[0]);
    for (i = 1; i < size; i++) {
        printf(", %d", nums[i]);
    }
    printf("]\n");
}

int remove_element(int *nums, int nums_size, int val)
{
    int i, count = 0;

    for (i = 0; i < nums_size; i++) {
        if (nums[i] != val) {
            nums[count++] = nums[i];
        }
    }

    return count;
}

int main(int argc, char **argv)
{
    int arr1[] = {3, 2, 2, 3},             len1 = sizeof(arr1) / sizeof(int);
    int arr2[] = {0, 1, 2, 2, 3, 0, 4, 2}, len2 = sizeof(arr2) / sizeof(int);
    struct object inputs[] = {
        {.array = arr1, .len = len1, .val = 3},
        {.array = arr2, .len = len2, .val = 2},
    };
    int i, size, len = sizeof(inputs) / sizeof(struct object);

    for (i = 0; i < len; i++) {
        printf("\n nums = "); print_array(inputs[i].array, inputs[i].len);
        printf(" val  = %d\n", inputs[i].val);
        size = remove_element(inputs[i].array, inputs[i].len, inputs[i].val);
        printf(" Output: "); print_array(inputs[i].array, size);
    }

    return EXIT_SUCCESS;
}
