#include <stdio.h>
#include <stdlib.h>

int roman_to_digit(char c)
{
    switch (c) {
        case 'I':
            return 1;
        case 'V':
            return 5;
        case 'X':
            return 10;
        case 'L':
            return 50;
        case 'C':
            return 100;
        case 'D':
            return 500;
        case 'M':
            return 1000;
        default:
            return 0;
    }
}

int roman_to_int(char *s)
{
    int i, result = roman_to_digit(s[0]);

    for (i = 1; s[i] != '\0'; i++) {
        int prev = roman_to_digit(s[i-1]);
        int curr = roman_to_digit(s[i]);

        if (prev < curr) {
            result = result - prev + (curr - prev);
        } else {
            result += curr;
        }
    }

    return result;
}

int main(int argc, char **argv)
{
    int i;
    char *array[] = {
        "III",
        "IV",
        "IX",
        "LVIII",
        "MCMXIV",
    };
    int len = sizeof(array) / sizeof(char *);

    for (i = 0; i < len; i++) {
        char *s = array[i];
        printf("\n Input: %s\n Output: %d\n", s, roman_to_int(s));
    }

    return 0;
}
