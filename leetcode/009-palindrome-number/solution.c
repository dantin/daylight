#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define btoa(x) ((x) ? "true" : "false")


int reverse(int x)
{
    int y = 0;
    while (x) {
        y = y * 10 + x % 10;
        x /= 10;
    }
    return y;
}

bool is_palindrome(int x)
{
    if (x == 0) {
        return true;
    }
    if (x < 0) {
        return false;
    }
    return x == reverse(x);
}

int main(int argc, char **argv)
{
    int i;
    int arr[] = {121, -121, 10};
    int len = sizeof(arr) / sizeof(int);

    for (i = 0; i < len; i++) {
        printf("Input: %d\nOutput: %s\n", arr[i], btoa(is_palindrome(arr[i])));
    }

    return 0;
}
