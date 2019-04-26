#include <stdio.h>
#include <stdlib.h>

struct Object {
    int *nums;
    int len;
};

void print_nums(int *nums, int size)
{
    int i;
    char *s = "";
    printf("[");
    for (i = 0; i < size; i++) {
        printf("%s%d", s, nums[i]);
        s = ", ";
    }
    printf("]");
}

int single_number(int *nums, int nums_size)
{
    int i, j, count[32], mask = 0;

    for (i = 0; i < 32; i++) {
        count[i] = 0;
        for (j = 0; j < nums_size; j++) {
            if ((1U << i) & nums[j]) {
                count[i]++;
            }
        }
        mask |= ((unsigned) (count[i] % 3)) << i;
    }

    return mask;
}

int main(int argc, char **argv)
{
    int nums1[] = { 2, 2, 3, 2 }, len1 = sizeof(nums1) / sizeof(int);
    int nums2[] = { 0, 1, 0, 1, 0, 1, 99 }, len2 = sizeof(nums2) / sizeof(int);
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
        int num = single_number(nums, size);
        printf("\n Output: %d\n", num);
    }

    return EXIT_SUCCESS;
}
