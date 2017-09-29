#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 20
#define MAX  1000

int exponent(char *s, int n, char *buf, const int size);

int main(void)
{
    char s[SIZE];
    int n, r;

    while(scanf("%s%d", s, &n) == 2)
    {
        char *e = (char *) malloc(sizeof(char) * MAX);
        r = exponent(s, n, e, MAX);
        if(r) continue;
        printf("%s\n", e);
        free(e);
    }

    return 0;
}

/**
 * Compute exponentiation.
 *
 *   str: base in string
 *     n: index number
 *     r: char array contains return value
 *  size: size of the char array
 */
int exponent(char *str, int n, char *r, const int size)
{
    int i, num, s, c;
    int dotpos = 0, nLen = 0;
    char buf[MAX];

    memset(buf, 0, size * sizeof(char));
    if(size <= SIZE)
    {
        return -1;
    }

    if(n == 0)
    {
        strcpy(r, "1.0");
        return 0;
    }

    // omit '.' in string 'str'.
    nLen = strlen(str);
    i = 0;
    while(str[i] != '.')
        i++;
    dotpos = nLen - i - 1;
    for(; i < nLen; i++)
        str[i] = str[i+1];
    // convert real number to integer.
    num = atoi(str);
    // find the dot position.
    dotpos = dotpos * n;
    // reset response buffer.
    memset(r, 0, size * sizeof(char));
    // start compute, result in reverse sequence.
    buf[1] = 1;
    while(n > 0)
    {
        s = 0, c = 0;
        for(i = 0; i < size; i++)
        {
            s = num * buf[i] + c;
            c = s / 10;
            buf[i] = s % 10;
        }
        --n;
    }
    // heading '.' checking
    for(i = size - 1; buf[i] == 0; --i);
    i = (i < dotpos) ? dotpos : i;
    while(i > 0)
    {
        char n[2];
        if(i == dotpos) strcat(r, ".");
        sprintf(n, "%d", buf[i--]);
        strcat(r, n);
    }
    // omit tailing '0'
    nLen = strlen(r);
    for(i = nLen - 1; i > 0; --i)
        if(r[i] == '0')
        {
            r[i] = 0;
        }
        else
        {
            break;
        }
    if(r[i] == '.') r[i] = 0;

    return 0;
}
