#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

void show_board(char **board, int n)
{
    int row, col;

    for (row = 0; row < n; row++) {
        char *line = board[row];
        for (col = 0;  col < n; col++) {
            putchar(line[col]);
        }
        putchar('\n');
    }
}

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

char **solution(int *stack, int n)
{
    int row, col;
    char **solution = malloc(n * sizeof(char *));

    for (row = 0; row < n; row++) {
        char *line = malloc(n + 1);
        for (col = 0; col < n; col++) {
            line[col] = (col == stack[row]) ? 'Q' : '.';
        }
        line[n] = '\0';
        solution[row] = line;
    }

    return solution;
}

char ***solve_n_queens(int n, int *return_size)
{
    int cap = 1000;
    int row = 0, col = 0, sum = 0;
    char ***solutions = malloc(cap * sizeof(char **));

    int *stack = malloc(n * sizeof(int));
    for (row = 0; row < n; row++) {
        stack[row] = -1;
    }

    if (n == 1) {
        stack[0] = 0;
        solutions[0] = solution(stack, n);
        *return_size = 1;
        return solutions;
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
                            *return_size = sum;
                            return solutions;
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
            solutions[sum++] = solution(stack,n);
        }

        // move on to find if there are other solutions.
        col = pop(stack, row);
        col++;
    }

    assert(0);
}

int main(int argc, char **argv)
{
    int inputs[] = {4};
    int i, j, num_of_solution, len = sizeof(inputs) / sizeof(int);

    for (i = 0; i < len; i++) {
        int n = inputs[i];
        printf("\n Input: %d\n\n", n);
        char ***solutions = solve_n_queens(n, &num_of_solution);
        for (j = 0; j < num_of_solution; j++) {
            char **solution = solutions[j];
            show_board(solution, n);
            printf(" The %dth solution.\n\n", j + 1);
        }

    }

    return EXIT_SUCCESS;
}
