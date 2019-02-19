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

void swap(int *lhs, int *rhs)
{
    int tmp = *lhs;
    *lhs = *rhs;
    *rhs = tmp;
}

void sort_colors(int *nums, int num_size)
{
    int i = 0, j = num_size - 1;
    while (i < j) {
        while (nums[i] == 0 && i < j) {
            i++;
        }
        while (nums[j] != 0 && j > i) {
            j--;
        }
        swap(nums + i, nums + j);
    }
    j = num_size - 1;
    while (i < j) {
        while (nums[i] == 1 && i < j) {
            i++;
        }
        while (nums[j] != 1 && j > i) {
            j--;
        }
        swap(nums + i, nums + j);
    }
}

int main(int argc, char **argv)
{
    int nums1[] = {2, 0, 2, 1, 1, 0}, len1 = sizeof(nums1) / sizeof(int);
    struct Object inputs[] = {
        { .nums = nums1, .len = len1 },
    };
    int i, len = sizeof(inputs) / sizeof(struct Object);
    
    for (i = 0; i < len; i++) {
        int *nums = inputs[i].nums;
        int size = inputs[i].len;
        printf("\n Inputs: ");
        print_nums(nums, size);
        sort_colors(nums, size);
        printf(" Output: ");
        print_nums(nums, size);
    }
    return EXIT_SUCCESS;
}
