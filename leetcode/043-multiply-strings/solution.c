#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct object {
    char *num1;
    char *num2;
};

void reverse(char *s, int size)
{
    int low = 0, high = size - 1;

    while (low < high) {
        char c = s[low];
        s[low] = s[high];
        s[high] = c;
        low++;
        high--;
    }
}

char *multiply(char *num1, char *num2)
{
    if (*num1 == '\0') {
        return num2;
    }
    if (*num2 == '\0') {
        return num1;
    }

    int i, j, cap = 110;
    char *result = malloc(cap * 2);
    memset(result, '0', cap * 2);
    int len1 = strlen(num1), len2 = strlen(num2);
    reverse(num1, len1);
    reverse(num2, len2);

    for (i = 0; i < len1; i++) {
        int carry = 0;
        for (j = 0; j < len2; j++) {
            carry += (num1[i] - '0') * (num2[j] - '0') + (result[i+j] - '0');
            result[i+j] = carry % 10 + '0';
            carry /= 10;
        }
        if (carry != 0) {
            result[len2+i] = carry + '0';
        }
    }
    int len = cap * 2;
    while (--len >= 0) {
        if (result[len] > '0') {
            result[++len] = '\0';
            break;
        }
    }
    if (len == -1) {
        len = 1;
        result[len] = '\0';
    }
    reverse(result, len);

    return result;
}

int main(int argc, char **argv)
{
    struct object inputs[] = {
        {.num1 = "2", .num2 = "3"},
    };
    int i, len = sizeof(inputs) / sizeof(struct object);

    for (i = 0; i < len; i++) {
        char *num1 = inputs[i].num1;
        char *num2 = inputs[i].num2;
        printf("\n Input: num1 = \"%s\", num2 = \"%s\"\n", num1, num2);
        char *answer = multiply(num1, num2);
        printf(" Output: \"%s\"\n", answer);
    }

    return EXIT_SUCCESS;
}
