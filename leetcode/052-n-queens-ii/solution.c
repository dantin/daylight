#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

inline int conflict(int *stack, int row, int col)
{
    int i;
    // check if occupied or in one line.
    for (i = 0; i < row; i++) {
        if (col == stack[i] || abs(row - i) == abs(col - stack[i])) {
            return 1;
        }
    }

    return 0;
}

inline void push(int *stack, int row, int col)
{
    stack[row] = col;
}

inline int pop(int *stack, int n)
{
    int col = stack[n];
    stack[n] = -1;
    return col;
}

inline int top(int *stack, int n)
{
    int row;

    for (row = n - 1; row >= 0; row--) {
        if (stack[row] != -1) {
            return row;
        }
    }

    return 0;
}

int total_n_queens(int n)
{
    int row = 0, col = 0, sum = 0;
    int *stack = malloc(n * sizeof(int));
    for (row = 0; row < n; row++) {
        stack[row] = -1;
    }

    if (n == 1) {
        return 1;
    }

    while (true) {
        for (; row < n; row++) {
            while (col < n) {
                if (conflict(stack, row, col)) {
                    while(col == n - 1) {
                        // no other position in this row, backtracking.
                        if (--row < 0) {
                            // all solutions found!
                            free(stack);
                            return sum;
                        }
                        col = pop(stack, row);
                    }
                    col++;
                } else {
                    push(stack, row, col);
                    break;
                }
            }
            col = 0;
        }

        row = top(stack, n);
        if (row == n - 1) {
            // found a new solution.
            sum++;
        }

        // move on to find if there are other solutions.
        col = pop(stack, row);
        col++;
    }
}

int main(int argc, char **argv)
{
    int inputs[] = {4};
    int i, len = sizeof(inputs) / sizeof(int);

    for (i = 0; i < len; i++) {
        int n = inputs[i];
        printf("\n Input: %d\n", n);
        int count = total_n_queens(n);
        printf(" Output: %d\n", count);
    }

    return EXIT_SUCCESS;
}
