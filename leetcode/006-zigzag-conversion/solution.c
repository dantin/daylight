#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct object {
    char *s;
    int rows;
};

char *convert(char *s, int rows)
{
    if (rows <= 1) return s;

    int len = strlen(s);
    char *str = malloc(len+1);
    char *p = str;
    int row;

    for (row = 0; row < rows; row++) {
        int interval1 = rows + (rows-2) - row * 2;
        int interval2 = row * 2;
        int flag = 0;
        int i = row;
        while (i < len) {
            *p++ = s[i];
            int delta = 0;
            do {
                delta = (flag == 0) ? interval1 : interval2;
                flag = !flag;
            } while (delta == 0);
            i += delta;
        }
    }
    str[len] = '\0';

    return str;
}

int main(int argc, char **argv)
{
    int i;
    struct object arr[] = {
        {"PAYPALISHIRING", 3},
        {"PAYPALISHIRING", 4},
    };
    int len = sizeof(arr) / sizeof(struct object);

    for (i = 0; i < len; i++) {
        printf("\n Input: %s\n Output: %s\n", arr[i].s, convert(arr[i].s, arr[i].rows));
    }

    return 0;
}
