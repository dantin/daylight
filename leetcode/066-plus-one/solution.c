#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Object {
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

int *plus_one(int *digits, int digits_size, int *return_size)
{
    int i, j, len = 0, carry = 1;
    int *result = malloc((digits_size + 1) * sizeof(int));

    for (i = digits_size - 1; i >= 0 || carry; i--) {
        int n = i >= 0 ? digits[i] + carry : carry;
        result[len++] = n % 10;
        carry = n / 10;
    }

    for (i = 0, j = len - 1; i < j; i++, j--) {
        int tmp = result[i];
        result[i] = result[j];
        result[j] = tmp;
    }

    *return_size = len;
    return result;
}

int main(int argc, char **argv)
{
    int nums1[] = {1, 2, 3},    len1 = sizeof(nums1) / sizeof(int);
    int nums2[] = {4, 3, 2, 1}, len2 = sizeof(nums2) / sizeof(int);
    int nums3[] = {9},          len3 = sizeof(nums3) / sizeof(int);
    struct Object inputs[] = {
        {.nums = nums1, .len = len1},
        {.nums = nums2, .len = len2},
        {.nums = nums3, .len = len3},
    };
    int i, return_size, len = sizeof(inputs) / sizeof(struct Object);

    for (i = 0; i < len; i++) {
        int *nums = inputs[i].nums;
        int size = inputs[i].len;
        printf("\n Inputs: ");
        print_nums(nums, size);

        int *ret = plus_one(nums, size, &return_size);
        printf(" Output: ");
        print_nums(ret, return_size);
        free(ret);
    }

    return EXIT_SUCCESS;
}
