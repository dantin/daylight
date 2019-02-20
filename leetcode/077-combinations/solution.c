#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct Object {
    int n;
    int k;
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

void print_combination(int **combination, int *column_sizes, int size)
{
    int i, indent = 2;

    if (size < 1) {
        printf("[]\n");
        return;
    }

    printf("[\n");
    printf("%*s", indent, "");
    print_nums(combination[0], column_sizes[0]);
    for (i = 1; i < size; i++) {
        printf(",\n%*s", indent, "");
        print_nums(combination[i], column_sizes[i]);
    }
    printf("\n]\n");
}

void free_combination(int **combination, int *column_sizes, int size)
{
    if (size < 1) {
        return;
    }

    int i;
    for (i = 0; i < size; i++) {
        free(combination[i]);
    }
    free(combination);
    free(column_sizes);
    return;
}

void dfs(int n, int k, int start, int *stack, int len,
         bool *used, int *column_sizes, int **results, int *count)
{
    int i;
    if (len == k) {
        column_sizes[*count] = k;
        results[*count] = malloc(k * sizeof(int));
        memcpy(results[*count], stack, k * sizeof(int));
        (*count)++;
    } else {
        for (i = start; i <= n; i++) {
            if (!used[i]) {
                stack[len] = i;
                used[i] = true;
                dfs(n, k, i + 1, stack, len + 1, used, column_sizes, results, count);
                used[i] = false;
            }
        }
    }
}

int **combine(int n, int k, int **column_sizes, int *return_size)
{
    int capacity = 10000;
    int count = 0;
    int **results = malloc(capacity * sizeof(int *));
    int *stack = malloc(k * sizeof(int));
    bool *used = malloc((n + 1) * sizeof(bool));

    memset(used, false, n + 1);
    *column_sizes = malloc(capacity * sizeof(int));
    dfs(n, k , 1, stack, 0, used, *column_sizes, results, &count);
    free(stack);
    free(used);

    *return_size = count;
    return results;
}

int main(int argc, char **argv)
{
    struct Object inputs[] = {
        { .n = 4, .k = 2 },
    };
    int i, len = sizeof(inputs) / sizeof(struct Object);
    int *column_sizes, return_size;

    for (i = 0; i < len; i++) {
        int n = inputs[i].n;
        int k = inputs[i].k;

        printf("\n Input: n = %d, k = %d\n", n, k);
        int **combination = combine(n, k, &column_sizes, &return_size);

        print_combination(combination, column_sizes, return_size);
        free_combination(combination, column_sizes, return_size);
    }

    return EXIT_SUCCESS;
}
