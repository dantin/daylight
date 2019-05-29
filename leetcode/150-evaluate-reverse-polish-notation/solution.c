#include <stdio.h>
#include <stdlib.h>

struct Object {
    char **tokens;
    int len;
};

void print_strs(char **strs, int size)
{
    char *s = "";
    int i;
    printf("[");
    for (i = 0; i < size; i++) {
        printf("%s\"%s\"", s, strs[i]);
        s = ", ";
    }
    printf("]");
}

int a2i(char *s)
{
    int n = 0;
    int sign = 0;

    while (*s != '\0') {
        switch (s[0]) {
            case '+':
                break;
            case '-':
                sign = 1;
                break;
            case '*':
                break;
            case '/':
                break;
            default:
                n = n * 10 + (s[0] - '0');
                break;
        }
        s++;
    }

    return sign ? -n : n;
}

int eval_rpn(char **tokens, int tokens_size)
{
    int i, lhs, rhs;
    int stack[500], top = 0;

    for (i = 0; i < tokens_size; i++) {
        switch (tokens[i][0]) {
            case '\0':
                break;
            case '+':
                if (top > 0) {
                    rhs = stack[--top];
                }
                if (top > 0) {
                    lhs = stack[--top];
                    stack[top++] = lhs + rhs;
                }
                break;
            case '*':
                if (top > 0) {
                    rhs = stack[--top];
                }
                if (top > 0) {
                    lhs = stack[--top];
                    stack[top++] = lhs * rhs;
                }
                break;
            case '/':
                if (top > 0) {
                    rhs = stack[--top];
                }
                if (top > 0) {
                    lhs = stack[--top];
                    stack[top++] = lhs / rhs;
                }
                break;
            case '-':
                if (tokens[i][1] == '\0') {
                    if (top > 0) {
                        rhs = stack[--top];
                    }
                    if (top > 0) {
                        lhs = stack[--top];
                        stack[top++] = lhs - rhs;
                    }
                    break;
                }
            default:
                stack[top++] = a2i(tokens[i]);
                break;
        }
    }

    return top > 0 ? stack[top - 1] : 0;
}

int main(int argc, char **argv)
{
    char *tokens1[] = { "2", "1", "+", "3", "*" };
    int len1 = sizeof(tokens1) / sizeof(char *);
    char *tokens2[] = { "4", "13", "5", "/", "+" };
    int len2 = sizeof(tokens2) / sizeof(char *);
    char *tokens3[] = { "10", "6", "9", "3", "+", "-11", "*", "/", "*", "17", "+", "5", "+" };
    int len3 = sizeof(tokens3) / sizeof(char *);
    struct Object inputs[] = {
        { .tokens = tokens1, .len = len1 },
        { .tokens = tokens2, .len = len2 },
        { .tokens = tokens3, .len = len3 },
    };
    int i, len = sizeof(inputs) / sizeof(struct Object);

    for (i = 0; i < len; i++) {
        char **tokens = inputs[i].tokens;
        int size = inputs[i].len;

        printf("\n Input: ");
        print_strs(tokens, size);

        int val = eval_rpn(tokens, size);
        printf("\n Output: %d\n", val);
    }

    return EXIT_SUCCESS;
}
