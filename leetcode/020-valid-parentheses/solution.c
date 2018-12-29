#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool is_valid(char *s)
{
    int top = 0, cap = 100;
    char *stack = malloc(cap);

    while (*s != '\0') {
        switch (*s) {
            case '(':
            case '[':
            case '{':
                if (top + 1 >= cap) {
                    cap *= 2;
                    stack = realloc(stack, cap);
                }
                stack[top++] = *s;
                break;
            case ')':
                if (stack[--top] != '(') return false;
                break;
            case ']':
                if (stack[--top] != '[') return false;
                break;
            case '}':
                if (stack[--top] != '{') return false;
                break;
            default:
                return false;
        }
        s++;
    }

    return top == 0;
}

int main(int argc, char **argv)
{
    char *array[] = {"()", "()[]{}", "(]", "([)]", "{[]}"};
    int i, len = sizeof(array) / sizeof(char *);

    for (i = 0; i < len; i++) {
        char *s = array[i];
        bool v = is_valid(s);
        printf(" Input: %s\n Output: %s\n", s, v ? "true" : "false");
    }

    return 0;
}
