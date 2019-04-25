#include <stdio.h>
#include <stdlib.h>

struct Object {
    int *nums;
    int len;
};

void print_nums(int *nums, int size)
{
    if (size < 1) {
        printf("[]");
        return;
    }

    int i = 0;
    printf("[%d", nums[i]);
    for (i = 1; i < size; i++) {
        printf(", %d", nums[i]);
    }
    printf("]");
}

int single_number(int *nums, int nums_size)
{
    int i, s = 0;
    for (i = 0; i < nums_size; i++) {
        s ^= nums[i];
    }

    return s;
}

int main(int argc, char **argv)
{
    int nums1[] = { 2, 2, 1 }, len1 = sizeof(nums1) / sizeof(int);
    int nums2[] = { 4, 1, 2, 1, 2 }, len2 = sizeof(nums2) / sizeof(int);
    struct Object inputs[] = {
        { .nums = nums1, .len = len1 },
        { .nums = nums2, .len = len2 },
    };
    int i, len = sizeof(inputs) / sizeof(struct Object);

    for (i = 0; i < len; i++) {
        int *nums = inputs[i].nums;
        int size = inputs[i].len;

        printf("\n Input: ");
        print_nums(nums, size);

        int n = single_number(nums, size);

        printf("\n Output: %d\n", n);
    }

    return EXIT_SUCCESS;
}
