#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct object {
    int *nums;
    int len;
    int target;
};

void print_nums(int *nums, int size)
{
    if (size < 1) {
        return;
    }

    printf("[%d", nums[0]);

    int i;
    for (i = 1; i < size; i++) {
        printf(", %d", nums[i]);
    }
    putchar(']');
}

void dfs(int *nums, int size, int target, int start, int *stack,
         int top, int **results, int *column_sizes, int *count)
{
    int i;
    if (target == 0) {
        results[*count] = malloc(top * sizeof(int));
        memcpy(results[*count], stack, top * sizeof(int));
        column_sizes[*count] = top;
        (*count)++;
    } else if (target > 0) {
        for (i = start; i < size; i++) {
            if (i > 0 && nums[i] == nums[i-1]) {
                continue;
            }
            stack[top] = nums[i];
            dfs(nums, size, target - nums[i], i, stack, top+1, results, column_sizes, count);
        }
    }
}

int ** combination_sum(int *candidates, int candidates_size, int target, int **column_sizes, int *return_size)
{
    int cap = 10000;
    int **results = malloc(cap * sizeof(int *));
    int *stack = malloc(target * sizeof(int));

    *column_sizes = malloc(cap * sizeof(int *));
    *return_size = 0;

    dfs(candidates, candidates_size, target, 0, stack, 0, results, *column_sizes, return_size);

    return results;
}

int main(int argc, char **argv)
{
    int nums1[] = {2, 3, 6, 7},                   len1 = sizeof(nums1) / sizeof(int);
    int nums2[] = {2, 3, 5},                      len2 = sizeof(nums2) / sizeof(int);
    int nums3[] = {8, 10, 6, 3, 4, 12, 11, 5, 9}, len3 = sizeof(nums3) / sizeof(int);
    struct object inputs[] = {
        {.nums = nums1, .len = len1, .target = 7},
        {.nums = nums2, .len = len2, .target = 8},
        {.nums = nums3, .len = len3, .target = 28},
    };
    int i, j, len = sizeof(inputs) / sizeof(struct object);
    int *column_sizes = NULL, size;

    for (i = 0; i < len; i++) {
        int *candidates = inputs[i].nums;
        int candidates_size = inputs[i].len;
        int target = inputs[i].target;

        printf("\n candidates = "); print_nums(candidates, candidates_size);
        printf(", target = %d\n", target);

        int **results = combination_sum(candidates, candidates_size, target, &column_sizes, &size);

        printf(" A solution set is:\n");
        if (size < 1) {
            printf(" []\n");
            continue;
        }
        printf(" [\n");
        printf("   "); print_nums(results[0], column_sizes[0]);
        for (j = 1; j < size; j++) {
            printf(",\n   ");
            print_nums(results[j], column_sizes[j]);
        }
        printf("\n ]\n");
    }

    return EXIT_SUCCESS;
}
