#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **generate_parenthesis(int n, int *return_size)
{
    int left, right, cap = 5000, count = 0;
    char **parentheses = malloc(cap * sizeof(char *));

    char *stack = malloc(2*n + 1);

    char *p = stack;
    left = right = 0;
    stack[2 * n] = '\0';

    /* begin and end condition of loop */
    while (p != stack || count == 0) {
        if (left == n && right == n) {
            /* found solution */
            parentheses[count] = malloc(2*n + 1);
            strcpy(parentheses[count], stack);
            count++;

            /* back tracking */
            while (--p != stack) {
                if (*p == '(') {
                    /* until ')' is no more than '(' is guaranteed */
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
            /* forward */
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
