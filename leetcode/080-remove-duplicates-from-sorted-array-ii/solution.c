#include <stdio.h>
#include <stdlib.h>

struct Object {
    int *nums;
    int len;
};

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

int remove_duplicates(int *nums, int nums_size)
{
    if (nums_size == 0) {
        return 0;
    }

    int i;
    int len = 0;
    int count = 1;
    for (i = 1; i < nums_size; i++) {
        if (nums[len] == nums[i]) {
            if (count < 2) {
                count++;
                nums[++len] = nums[i];
            }
        } else {
            count = 1;
            nums[++len] = nums[i];
        }
    }

    return len + 1;
}

int main(int argc, char **argv)
{
    int nums1[] = {1, 1, 1, 2, 2, 3},          len1 = sizeof(nums1) / sizeof(int);
    int nums2[] = {0, 0, 1, 1, 1, 1, 2, 3, 3}, len2 = sizeof(nums2) / sizeof(int);
    struct Object inputs[] = {
        { .nums = nums1, .len = len1 },
        { .nums = nums2, .len = len2 },
    };
    int i, len = sizeof(inputs) / sizeof(struct Object);

    for (i = 0; i < len; i++) {
        int *nums = inputs[i].nums;
        int size = inputs[i].len;

        printf("\n nums = ");
        print_nums(nums, size);

        int length = remove_duplicates(nums, size);
        printf(" length = %d\n", length);
    }

    return EXIT_SUCCESS;
}
