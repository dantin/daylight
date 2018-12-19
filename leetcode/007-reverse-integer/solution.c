#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int reverse(int x)
{
    int y = 0;

    while (x != 0) {
        int n = x % 10;
        // Checking the over/underflow.
        // Actually, it should be y > (INT_MAX-n)/10, but n/10 is 0, so omit it.
        if (y > INT_MAX / 10 || y < INT_MIN / 10) {
            return 0;
        }
        y = y * 10 + n;
        x /= 10;
    }

    return y;
}

int main(int argc, char **argv)
{
    int i;
    int arr[] = {123, -123, 120};
    int len = sizeof(arr) / sizeof(int);

    for (i = 0; i < len; i++) {
        printf("Input: %d\nOutput: %d\n", arr[i], reverse(arr[i]));
    }
    
    return 0;
}
