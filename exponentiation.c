#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 10
#define MAX  1024

char *exponent(char *s, int n);

int main(void)
{
    char s[SIZE];
    int n;

    while(scanf("%s%d", s, &n) == 2)
    {
        char *e = exponent(s, n);
        printf("%s\n", e);
        free(e);
    }

    return 0;
}

char *exponent(char *s, int n)
{
    char *r = (char *)malloc(100);

    strcpy(r, "hello");

    return r;
}
