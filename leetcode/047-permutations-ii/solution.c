#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct object {
    int *nums;
    int len;
};

void print_nums(int *nums, int size)
{
    int i;
    if (size < 1) {
        printf("[]");
        return;
    }

    printf("[%d", nums[0]);
    for (i = 1; i < size; i++) {
        printf(", %d", nums[i]);
    }
    printf("]");
}

int compare(const void *lhs, const void *rhs)
{
    return *(int *) lhs - *(int *) rhs;
}

void dfs(int *nums, int size, int *stack, bool *used, int top, int **results, int *count)
{
    int i;
    if (top == size) {
        results[*count] = malloc(size * sizeof(int));
        memcpy(results[*count], stack, size * sizeof(int));
        (*count)++;
    } else {
        for (i = 0; i < size; i++) {
            if (!used[i]) {
                if (i > 0 && nums[i] == nums[i - 1] && !used[i - 1]) continue;
                used[i] = true;
                stack[top] = nums[i];
                dfs(nums, size, stack, used, top + 1, results, count);
                used[i] = false;
            }
        }
    }
}

int **permute(int *nums, int nums_size, int *return_size)
{
    *return_size = 0;

    qsort(nums, nums_size, sizeof(int), compare);

    int cap = 5000;
    int *stack = malloc(nums_size * sizeof(int));
    int **results = malloc(cap * sizeof(int));
    bool *used = malloc(nums_size);
    memset(used, false, nums_size);

    dfs(nums, nums_size, stack, used, 0, results, return_size);

    return results;
}

int main(int argc, char **argv)
{
    int nums1[] = {1, 1, 2}, len1 = sizeof(nums1) / sizeof(int);
    struct object inputs[] = {
        {.nums = nums1, .len = len1},
    };
    int i, j, count, len = sizeof(inputs) / sizeof(struct object);

    for (i = 0; i < len; i++) {
        int *nums = inputs[i].nums;
        int size = inputs[i].len;
        printf("\n Inputs: "); print_nums(nums, size); puts("\n");

        int **result = permute(nums, size, &count);
        
        printf(" Output:\n");
        if (count < 1) {
            printf(" []\n");
            continue;
        }
        printf(" [\n");
        printf("    "); print_nums(result[0], size);
        for (j = 1; j < count; j++) {
            printf(",\n    ");
            print_nums(result[j], size);
        }
        puts("\n ]\n");

    }

    return EXIT_SUCCESS;
}
