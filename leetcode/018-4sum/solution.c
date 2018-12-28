#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_SIZE 4

void print_array(int *nums, int size)
{
    int i;

    printf("[");
    for (i = 0; i < size; i++) {
        if (i != 0) {
            printf(", ");
        }
        printf("%d", nums[i]);
    }
    printf("]\n");
}

int compare(const void *lhs, const void *rhs)
{
    return *(int *) lhs - *(int *) rhs;
}

/**
 * find `k` numbers in `nums` between `[low, high]`, whose sum is `target`.
 *
 * arguments:
 *
 *  nums:    int array
 *  low:     low index
 *  high:    high index
 *  target:  target sum
 *  total:   size of an item of result array
 *  k:       k num remaining
 *  stack:   stack that keep choosen integer
 *  top:     top pointer position of stack
 *  results: result 2D integer array
 *  count:   current size of results
 *
 */
void k_sum(int *nums, int low, int high, int target, int total,
           int k, int *stack, int top, int **results, int *count)
{
    int i;

    if (k == 2) {
        /* k == 2*/
        while (low < high) {
            int diff = target - nums[low];
            if (diff > nums[high]) {
                while (++low < high && nums[low] == nums[low-1]) {}
            } else if (diff < nums[high]) {
                while (--high > low && nums[high] == nums[high+1]) {}
            } else {
                // found match!
                stack[top++] = nums[low];
                stack[top++] = nums[high];
                results[*count] = malloc(total * sizeof(int));
                memcpy(results[*count], stack, total * sizeof(int));
                (*count)++;
                // recovery top, prepare to find next match!
                top -= 2;
                while (++low < high && nums[low] == nums[low-1]) {}
                while (--high > low && nums[high] == nums[high+1]) {}
            }
        }
    } else {
        /* k > 2 */
        for (i = low; i <= high-k+1; i++) {
            // quick skip to avoid duplicate result.
            if (i > low && nums[i] == nums[i-1]) continue;
            stack[top++] = nums[i];
            k_sum(nums, i+1, high, target-nums[i], NUM_SIZE, k-1, stack, top, results, count);
            top--;
        }
    }
}

int **four_sum(int *nums, int nums_size, int target, int *return_size)
{
    if (nums_size < NUM_SIZE) {
        return NULL;
    }

    // sort nums in ascending order.
    qsort(nums, nums_size, sizeof(*nums), compare);

    *return_size = 0;
    int capacity = 50000;                             // predefined size of the result array
    int **results = malloc(capacity * sizeof(int *)); // result array
    int *stack = malloc(NUM_SIZE * sizeof(int));

    k_sum(nums, 0, nums_size-1, target, NUM_SIZE, NUM_SIZE, stack, 0, results, return_size);

    return results;
}

int main(int argc, char **argv)
{
    int nums[] = {1, 0, -1, 0, -2, 2};
    int i, count, target = 0;
    int len = sizeof(nums) / sizeof(int);

    printf(" nums:    "); print_array(nums, len);
    printf(" targets: %d\n", target);

    int **quadruplets = four_sum(nums, len, target, &count);

    printf(" [\n");
    for (i = 0; i < count; i++) {
        printf("   "); print_array(quadruplets[i], NUM_SIZE);
    }
    printf(" ]\n");

    return 0;
}
