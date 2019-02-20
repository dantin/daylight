#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Object {
    int *nums;
    int len;
};

void print_nums(int *nums, int size)
{
    if (size < 1) {
        printf("[]");
        return;
    }
    int i;

    printf("[%d", nums[0]);
    for (i = 1; i < size; i++) {
        printf(", %d", nums[i]);
    }
    printf("]");
}

void print_subsets(int **subset, int *column_sizes, int size)
{
    if (size < 1) {
        printf("[]\n");
        return;
    }
    int i, indent = 2;

    printf("[\n%*s", indent, "");
    print_nums(subset[0], column_sizes[0]);
    for (i = 1; i < size; i++) {
        printf(",\n%*s", indent, "");
        print_nums(subset[i], column_sizes[i]);
    }
    printf("\n]\n");
}

void free_subsets(int **subset, int *column_sizes, int size)
{
    int i;
    for (i = 0; i < size; i++) {
        free(subset[i]);
    }
    free(subset);
    free(column_sizes);
}

void dfs(int *nums, int size, int start, int *buf,
         int len, int **sets, int *sizes, int *count)
{
    int i;
    sets[*count] = malloc(len * sizeof(int));
    memcpy(sets[*count], buf, len * sizeof(int));
    sizes[*count] = len;
    (*count)++;
    for (i = start; i < size; i++) {
        buf[len] = nums[i];
        dfs(nums, size, i + 1, buf, len + 1, sets, sizes, count);
    }
}

int **subsets(int *nums, int nums_size, int **column_sizes, int *return_size)
{
    int capacity = 5000;
    int **sets = malloc(capacity * sizeof(int *));
    int *buf = malloc(nums_size * sizeof(int));
    *column_sizes = malloc(capacity * sizeof(int));
    *return_size = 0;

    dfs(nums, nums_size, 0, buf, 0, sets, *column_sizes, return_size);
    free(buf);

    return sets;
}

int main(int argc, char **argv)
{
    int nums1[] = {1, 2, 3}, len1 = sizeof(nums1) / sizeof(int);
    struct Object inputs[] = {
        { .nums = nums1, .len = len1 },
    };
    int i, len = sizeof(inputs) / sizeof(struct Object);
    int *column_sizes, return_size;

    for (i = 0; i < len; i++) {
        int *nums = inputs[i].nums;
        int size = inputs[i].len;

        printf("\n Inputs: nums = ");
        print_nums(nums, size);
        printf("\n");

        int **subset = subsets(nums, size, &column_sizes, &return_size);
        printf(" Output:\n");
        print_subsets(subset, column_sizes, return_size);
        free_subsets(subset, column_sizes, return_size);
    }

    return EXIT_SUCCESS;
}
