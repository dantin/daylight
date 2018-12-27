#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

void print_array(int *array, int len)
{
    int i;

    printf("[");
    for (i = 0; i < len; i++) {
        if (i == 0) {
            printf("%d", array[i]);
        } else {
            printf(", %d", array[i]);
        }
    }
    printf("]\n");
}

int compare(const void *lhs, const void *rhs)
{
    return *(int *) lhs - *(int *) rhs;
}

int three_sum_closest(int *nums, int nums_size, int target)
{
    int i, min_diff = INT_MAX;

    if (nums_size < 3) {
        return min_diff;
    }
    
    qsort(nums, nums_size, sizeof(*nums), compare);

    for (i = 0; i < nums_size-2; i++) {
        int left = i + 1;
        int right = nums_size - 1;
        while (left < right) {
            int diff = nums[i] + nums[left] + nums[right] - target;
            if (abs(diff) < abs(min_diff)) {
                min_diff = diff;
            }
            if (diff < 0) {
                left++;
            } else if (diff > 0) {
                right--;
            } else {
                return target;
            }
        }
    }

    return min_diff + target;
}

int main(int argc, char **argv)
{
    int nums[] = {-1, 2, 1, -4};
    int target = 1;
    int len = sizeof(nums) / sizeof(int);

    printf(" Input: ");
    print_array(nums, len);
    printf(" Target: %d\n", target);
    printf(" %d\n", three_sum_closest(nums, len, target));

    return 0;
}
