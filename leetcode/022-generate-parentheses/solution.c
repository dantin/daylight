#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **generate_parenthesis(int n, int *return_size)
{
    int left, right, cap = 5000, count = 0;
    char *stack = malloc(2*n + 1);
    char **parentheses = malloc(cap * sizeof(char *));

    char *p = stack;
    left = right = 0;
    stack[2 * n] = '\0';

    while (p != stack || count == 0) {
        if (left == n && right == n) {
            parentheses[count] = malloc(2*n + 1);
            strcpy(parentheses[count], stack);
            count++;

            while (--p != stack) {
                if (*p == '(') {
                    if (--left > right) {
                        *p++ = ')';
                        right++;
                        break;
                    }
                } else {
                    right--;
                }
            }
        } else {
            while (left < n) {
                *p++ = '(';
                left++;
            }
            while (right < n) {
                *p++ = ')';
                right++;
            }
        }
    }

    *return_size = count;
    return parentheses;
}

int main(int argc, char **argv)
{
    int i, n = 3, count;

    char **results = generate_parenthesis(n, &count);

    for (i = 0; i < count; i++) {
        printf("%s\n", results[i]);
    }

    return EXIT_SUCCESS;
}
