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

void swap(int *lhs, int *rhs)
{
    int tmp = *lhs;
    *lhs = *rhs;
    *rhs = tmp;
}

void dfs(int *nums, int size, int start, int **results, int *count)
{
    int i;
    if (start == size) {
        results[*count] = malloc(size * sizeof(int));
        memcpy(results[*count], nums, size * sizeof(int));
        (*count)++;
    } else {
        for (i = start; i < size; i++) {
            swap(nums + start, nums + i);
            dfs(nums, size, start + 1, results, count);
            swap(nums + start, nums + i);
        }
    }
}

int **permute(int *nums, int nums_size, int *return_size)
{
    int cap = 5000;
    int **results = malloc(cap * sizeof(int));
    *return_size = 0;

    dfs(nums, nums_size, 0, results, return_size);

    return results;
}

int main(int argc, char **argv)
{
    int nums1[] = {1, 2, 3}, len1 = sizeof(nums1) / sizeof(int);
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
