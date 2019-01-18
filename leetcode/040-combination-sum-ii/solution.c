#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct object {
    int *candidates;
    int len;
    int target;
};

void print_nums(int *nums, int size)
{
    int i;
    if (size < 1) {
        printf("[]");
    }

    printf("[%d", nums[0]);
    for (i = 1; i < size; i++) {
        printf(", %d", nums[i]);
    }
    putchar(']');
}

int compare(const void *lhs, const void *rhs)
{
    return *(int *) lhs - *(int *) rhs;
}

void dfs(int *nums, int size, int target, int start, int *stack, int top,
         bool *used, int **results, int *column_sizes, int *count)
{
    int i;
    if (target == 0) {
        results[*count] = malloc(top * sizeof(int));
        memcpy(results[*count], stack, top * sizeof(int));
        column_sizes[*count] = top;
        (*count)++;
    } else if (target > 0) {
        for (i = start; i < size; i++) {
            if (!used[i]) {
                if (i > 0 && !used[i-1] && nums[i-1] == nums[i]) continue;

                used[i] = true;
                stack[top] = nums[i];
                dfs(nums, size, target-nums[i], i+1, stack, top+1, used, results, column_sizes, count);
                used[i] = false;
            }
        }
    }

}

int **combination_sum(int *candidates, int candidates_size, int target, int **column_sizes, int *return_size)
{
    int cap = 1000;
    qsort(candidates, candidates_size, sizeof(int), compare);

    *column_sizes = malloc(cap * sizeof(int));
    *return_size = 0;

    int *stack = malloc(target * sizeof(int));
    int **results = malloc(cap * sizeof(int *));
    bool *used = malloc(candidates_size);
    memset(used, false, candidates_size);

    dfs(candidates, candidates_size, target, 0, stack, 0, used, results, *column_sizes, return_size);

    return results;
}

int main(int argc, char **argv)
{
    int nums1[] = {10, 1, 2, 7, 6, 1, 5}, len1 = sizeof(nums1) / sizeof(int);
    int nums2[] = {2, 5, 2, 1, 2},        len2 = sizeof(nums2) / sizeof(int);
    struct object inputs[] = {
        {.candidates = nums1, .len = len1, .target = 8},
        {.candidates = nums2, .len = len2, .target = 5},
    };
    int i, j, return_size, *column_sizes, len = sizeof(inputs) / sizeof(struct object);

    for (i = 0; i < len; i++) {
        int *candidates = inputs[i].candidates;
        int size = inputs[i].len;
        int target = inputs[i].target;

        printf("\n candidates = "); print_nums(candidates, size);
        printf(", target = %d\n", target);

        int **results = combination_sum(candidates, size, target, &column_sizes, &return_size);

        printf(" [\n");
        printf("   "); print_nums(results[0], column_sizes[0]);
        for (j = 0; j < return_size; j++) {
            printf(",\n   ");
            print_nums(results[j], column_sizes[j]);
        }
        printf("\n ]\n");
    }

    return EXIT_SUCCESS;
}
