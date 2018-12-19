#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int my_atoi(char *str)
{
    char *s;
    int n = 0, sign = 0, digit = 0;

    while (*str == ' ' || *str == '\t') {
        str++;
    }

    for (s = str; *s != '\0'; s++) {
        if (isdigit(*s)) {
            digit = 1;
            int d = *s - '0';
            if (sign) {
                if (-n < (INT_MIN + d) / 10) {
                    n = INT_MIN;
                    break;
                }
            } else {
                if (n > (INT_MAX -d) / 10) {
                    n = INT_MAX;
                    break;
                }
            }
            n = n * 10 + d;
        } else if (*s == '-' && isdigit(*(s+1))) {
            if (digit == 1) { break; }
            sign = 1;
        } else if (*s == '+' && isdigit(*(s+1))) {
            if (digit == 1) { break; }
            sign = 0;
        } else {
            break;
        }
    }

    return sign ? -n : n;
}

int main(int argc, char **argv)
{
    int i;
    char *arr[] = {"42", "   -42", "4193 with words", "words and 987", "-91283472332", "0-1"};
    int len = sizeof(arr) / sizeof(char *);

    for (i = 0; i < len; i++) {
        printf("Input: %s\nOutput: %d\n", arr[i], my_atoi(arr[i]));
    }

    return 0;
}
