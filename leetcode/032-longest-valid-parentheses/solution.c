#include <stdio.h>
#include <stdlib.h>

/**
 * During the scanning of current substring, you can NOT tell whether the current substring is valid.
 * 
 * E.g. In scanning string '(()',
 *
 *      the next character may be ')', which makes the final string '(())'
 *      or it is just finished with EOL, which make the final string '(()'.
 *
 * Both of the conditions need to be considered, we need to keep track of the start position of current matching string
 * as well as the location of last '('!
 */
int longest_valid_parentheses(char *s)
{
    int length = 0, max_length = 0;
    int cap = 8000;
    int begin = -1; // 'begin' is the start position of current matching substring.
    char *p = s;

    // stack only keeps the location of '('.
    int *stack = malloc(cap * sizeof(int));
    int *top = stack;

    while (*p != '\0') {
        if (*p == '(') { 
            // current char is '(', push location into stack.
            if (top + 1 - stack >= cap) {
                cap *= 2;
                stack = realloc(stack, cap * sizeof(int));
            }
            *top++ = p - s;
        } else {
            if (top > stack) {
                // there is '(' in stack, match it, and update length.
                if (--top == stack) {
                    // '(' has been used up, update length from start of substring.
                    length = p - (s + begin);
                } else {
                    // '*(top - 1)' is the index of the last kept '('.
                    length = p - (s + *(top - 1));
                }
                if (length > max_length) {
                    max_length = length;
                }
            } else {
                // invalid parentheses, update start position of substring.
                begin = p - s;
            }
        }
        p++;
    }

    return max_length;
}

int main(int argc, char **argv)
{
    char *inputs[] = {
        "(()",
        ")()())",
    };
    int i, o, len = sizeof(inputs) / sizeof(char *);

    for (i = 0; i < len; i++) {
        char *s = inputs[i];
        printf("\n Input: \"%s\"\n", s);
        o = longest_valid_parentheses(s);
        printf(" Output: %d\n", o);
    }

    return EXIT_SUCCESS;
}
