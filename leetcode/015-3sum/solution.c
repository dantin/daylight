#include <stdio.h>
#include <stdlib.h>

#define CAPACITY 50000

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

/*
 * Find `-nums[i]` in `nums` with index range `[i+1, nums_size)`.
 *
 * args
 * ---
 *
 *   nums:    integer array
 *   low:     low bound
 *   high:    high bound
 *   target:  target integer
 *   results: result record
 *   count:   result count
 *
 */
void two_sum(int *nums, int low, int high, int target, int **results, int *count)
{
    while (low < high) {
        int diff = target - nums[low];
        if (diff > nums[high]) {
            while (++low < high && nums[low] == nums[low-1]) {}
        } else if (diff < nums[high]) {
            while (--high > low && nums[high] == nums[high+1]) {}
        } else {
            results[*count] = malloc(3*sizeof(int)); // triple integer array
            results[*count][0] = -target;
            results[*count][1] = nums[low];
            results[*count][2] = nums[high];
            (*count)++;
            while (++low < high && nums[low] == nums[low-1]) {}
            while (--high > low && nums[high] == nums[high+1]) {}
        }
    }
}

int **three_sum(int *nums, int nums_size, int *return_size)
{
    if (nums_size < 3) {
        return NULL;
    }

    qsort(nums, nums_size, sizeof(*nums), compare);

    *return_size = 0;
    int i, capacity = CAPACITY;
    int **results = malloc(capacity * sizeof(int *));

    for (i = 0; i < nums_size; i++) {
        if (i == 0 || (i > 0 && nums[i] != nums[i-1])) {
            // find `-nums[i]` in `nums` with index range `[i+1, nums_size)`.
            two_sum(nums, i+1, nums_size-1, -nums[i], results, return_size);
        }
    }

    return results;
}

int main(int argc, char **argv)
{
    int i, count;
    int nums[] = {-1, 0, 1, 2, -1, -4};
    int len = sizeof(nums) / sizeof(int);
    int **triplets = three_sum(nums, len, &count);

    printf(" Input: ");
    print_array(nums, len);
    printf(" Output:\n [\n");
    for (i = 0; i < count; i++) {
        printf("   ");
        print_array(triplets[i], 3);
    }
    printf(" ]\n");

    return 0;
}
