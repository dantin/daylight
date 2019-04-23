#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_strs(char **strs, int size)
{
    if (size < 1) {
        printf("[]");
        return;
    }
    int i = 0;
    printf("[\"%s\"", strs[i]);
    for (i = 1; i < size; i++) {
        printf(", \"%s\"", strs[i]);
    }
    printf("]");
}

void print_palindromes(char ***palindromes, int *column_sizes, int size)
{
    if (size < 1) {
        printf("[]\n");
        return;
    }
    int i = 0, indent = 2;
    printf("[\n%*s", indent, "");
    print_strs(palindromes[i], column_sizes[i]);
    for (i = 1; i < size; i++) {
        printf(",\n%*s", indent, "");
        print_strs(palindromes[i], column_sizes[i]);
    }
    printf("\n]\n");
}

void free_strs(char ***strs, int *column_sizes, int size)
{
    int i, j;
    for (i = 0; i < size; i++) {
        for (j = 0; j < column_sizes[i]; j++) {
            free(strs[i][j]);
        }
        free(strs[i]);
    }
    free(strs);
}

struct palindrome {
    int low;
    int high;
};

void collect(char *s, int len, int low, int high, struct palindrome *results, int *count)
{
    while (low >= 0 && high < len && s[low] == s[high]) {
        results[*count].low = low;
        results[*count].high = high;
        (*count)++;
        low--;
        high++;
    }
}

void dfs(struct palindrome *pal_set, int num, int start,
         char *s, int len, struct palindrome **stack, int size,
         char ***results, int *col_sizes, int *count)
{
    int i;
    if (size > 0 && stack[size - 1]->high == len - 1) {
        col_sizes[*count] = size;
        results[*count] = malloc(size * sizeof(char *));
        for (i = 0; i < size; i++) {
            int low = stack[i]->low;
            int high = stack[i]->high;
            results[*count][i] = malloc(high - low + 2);
            memcpy(results[*count][i], s + low, high - low + 1);
            results[*count][i][high - low + 1] = '\0';
        }
        (*count)++;
    } else {
        for (i = start; i < num; i++) {
            if ((size == 0 && pal_set[i].low == 0) ||
                    (size > 0 && stack[size - 1]->high + 1 == pal_set[i].low)) {
                stack[size] = &pal_set[i];
                dfs(pal_set, num, i + 1, s, len, stack, size + 1, results, col_sizes, count);
            }
        }
    }
}

char ***partition(char *s, int **column_sizes, int *result_size)
{
    int len = strlen(s);
    if (len == 0) {
        *result_size = 0;
        return NULL;
    }

    int i, capacity = 800, count = 0;
    struct palindrome *pal_set = malloc(capacity * sizeof(*pal_set));
    for (i = 0; i < len; i++) {
        collect(s, len, i, i, pal_set, &count);
        collect(s, len, i, i + 1, pal_set, &count);
    }

    char ***results = malloc(capacity * sizeof(char **));
    struct palindrome **stack = malloc(count * sizeof(*stack));
    *column_sizes = malloc(capacity * sizeof(int));
    dfs(pal_set, count, 0, s, len, stack, 0, results, *column_sizes, result_size);

    free(pal_set);
    return results;
}

int main(int argc, char **argv)
{
    char *inputs[] = {
        "aab",
    };
    int i, len = sizeof(inputs) / sizeof(char *);
    int *column_sizes, result_size;

    for (i = 0; i < len; i++) {
        char *s = inputs[i];

        printf("\n Input: \"%s\"\n", s);
        char ***palindromes = partition(s, &column_sizes, &result_size);
        printf("\n Output:\n");
        print_palindromes(palindromes, column_sizes, result_size);

        free_strs(palindromes, column_sizes, result_size);
        free(column_sizes);
    }
    return EXIT_SUCCESS;
}
