#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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

void print_sets(int **sets, int *column_sizes, int size)
{
    if (size < 1) {
        printf("[]\n");
        return;
    }
    int i, indent = 2;
    printf("[\n%*s", indent, "");
    print_nums(sets[0], column_sizes[0]);
    for (i = 1; i < size; i++) {
        printf(",\n%*s", indent, "");
        print_nums(sets[i], column_sizes[i]);
    }
    printf("\n]\n");
}

void free_sets(int **sets, int size)
{
    int i;
    for (i = 0; i < size; i++) {
        free(sets[i]);
    }
    free(sets);
}

int compare(const void *lhs, const void *rhs)
{
    return *(int *) lhs - *(int *) rhs;
}

void dfs(int *nums, int size, int start, int *buf, int level,
         bool *used, int **sets, int *sizes, int *count)
{
    int i;
    sets[*count] = malloc(level * sizeof(int));
    memcpy(sets[*count], buf, level * sizeof(int));
    sizes[*count] = level;
    (*count)++;
    for (i = start; i < size; i++) {
        if (!used[i]) {
            if (i > 0 && !used[i - 1] && nums[i - 1] == nums[i]) continue;
            used[i] = true;
            buf[level] = nums[i];
            dfs(nums, size, i + 1, buf, level + 1, used, sets, sizes, count);
            used[i] = false;
        }
    }
}

int **subsets(int *nums, int nums_size, int **column_sizes, int *return_size)
{
    int capacity = 5000;
    int **sets = malloc(capacity * sizeof(int *));
    int *buf = malloc(nums_size * sizeof(int));
    bool *used = malloc(nums_size);

    *column_sizes = malloc(capacity * sizeof(int));
    *return_size = 0;
    memset(used, false, nums_size);

    qsort(nums, nums_size, sizeof(int), compare);
    dfs(nums, nums_size, 0, buf, 0, used, sets, *column_sizes, return_size);

    free(buf);
    free(used);

    return sets;
}

int main(int argc, char **argv)
{
    int nums1[] = { 1, 2, 2 }, len1 = sizeof(nums1) / sizeof(int);
    struct Object inputs[] = {
        { .nums = nums1, .len = len1 },
    };
    int i, len = sizeof(inputs) / sizeof(struct Object);
    int *column_sizes, return_size;

    for (i = 0; i < len; i++) {
        int *nums = inputs[i].nums;
        int size = inputs[i].len;

        printf("\n Input:");
        print_nums(nums, size);
        printf("\n");
        int **sets = subsets(nums, size, &column_sizes, &return_size);

        printf(" Output:");
        print_sets(sets, column_sizes, return_size);
        free_sets(sets, return_size);
        free(column_sizes);
    }

    return EXIT_SUCCESS;
}
