#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct object {
    char *s;
    int rows;
};

int main(int argc, char **argv)
{
    int i;
    struct object arr[] = {
        {"PAYPALISHIRING", 3},
        {"PAYPALISHIRING", 4},
    };

    for (i = 0; i < (sizeof(arr) /sizeof(struct object)) ; i++) {
        printf("%s, %d\n", arr[i].s, arr[i].rows);
    }

    return 0;
}
