#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct object {
    int *nums;
    int len;
};

void print_nums(int *nums, int size)
{
    int i;
    if (size < 1) {
        printf("[]\n");
        return;
    }

    printf("[%d", nums[0]);
    for (i = 1; i < size; i++) {
        printf(", %d", nums[i]);
    }
    printf("]\n");
}

inline int max(int lhs, int rhs)
{
    return lhs > rhs ? lhs : rhs;
}

bool can_jump(int *nums, int nums_size)
{
    int i, pos = 0;

    for (i = 0; i < nums_size - 1; i++) {
        if (pos < i || pos >= nums_size - 1) {
            break;
        }
        pos = max(i + nums[i], pos);
    }

    return pos >= nums_size - 1;
}

int main(int argc, char **argv)
{
    int nums1[] = {2, 3, 1, 1, 4}, len1 = sizeof(nums1) / sizeof(int);
    int nums2[] = {3, 2, 1, 0, 4}, len2 = sizeof(nums2) / sizeof(int);
    struct object inputs[] = {
        {.nums = nums1, .len = len1},
        {.nums = nums2, .len = len2},
    };
    int i, len = sizeof(inputs) / sizeof(struct object);

    for (i = 0; i < len; i++) {
        int *nums = inputs[i].nums;
        int size = inputs[i].len;
        printf("\n Input: "); print_nums(nums, size);
        bool can = can_jump(nums, size);
        printf(" Output: %s\n", can ? "true" : "false");
    }
    return EXIT_SUCCESS;
}
