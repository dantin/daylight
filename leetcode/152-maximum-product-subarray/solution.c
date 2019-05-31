#include <stdio.h>
#include <stdlib.h>

struct Object {
    int *nums;
    int len;
};

void print_nums(int *nums, int size)
{
    char *s = "";
    int i;

    printf("[");
    for (i = 0; i < size; i++) {
        printf("%s%d", s, nums[i]);
        s = ", ";

    }
    printf("]");
}

int max_product(int *nums, int nums_size)
{
    if (nums_size == 0) {
        return 0;
    }

    int i, global_max = nums[0], product;
    int local_min = 1, local_max = 1;
    for (i = 0; i < nums_size; i++) {
        int n = nums[i];
        if (n > 0) {
            product = local_max * n;
            global_max = product > global_max ? product : global_max;
            local_max *= n;
            local_min *= n;
        } else if (n < 0) {
            product = local_min * n;
            global_max = product > global_max ? product : global_max;
            int tmp = local_max;
            local_max = product > 1 ? product : 1;
            local_min = tmp * n;
        } else {
            global_max = global_max > 0 ? global_max : 0;
            local_max = 1;
            local_min = 1;
        }
    }

    return global_max;
}

int main(int argc, char **argv)
{
    int nums1[] = { 2, 3, -2, 4 }, len1 = sizeof(nums1) / sizeof(int);
    int nums2[] = { -2, 0, -1 }, len2 = sizeof(nums2) / sizeof(int);
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

        int product = max_product(nums, size);

        printf("\n Output: %d\n", product);
    }

    return EXIT_SUCCESS;
}
