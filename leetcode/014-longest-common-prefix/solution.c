#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define BUFFER_SIZE 1000

char * longest_common_prefix(char **strs, int strs_size)
{
    int i, count = 0;
    char *result = malloc(BUFFER_SIZE);

    while (strs_size > 0) {
        char c = strs[0][count];
        for (i = 1; i < strs_size; i++) {
            if (c != strs[i][count]) break;
        }
        if (i == strs_size && c != '\0') {
            result[count++] = c;
        } else {
            break;
        }
    }

    result[count++] = '\0';
    return result;
}

int main(int argc, char **argv)
{
    int i, j;
    char *array[][3] = {
        {"flower", "flow", "flight"},
        {"dog", "racecar", "car"},
    };
    int len = sizeof(array) / sizeof(array[0]);

    for (i = 0; i < len; i++) {
        int size = sizeof(array[i]) / sizeof(char *);
        printf("\n Input: [");
        for (j = 0; j < size; j++) {
            if (j == 0) {
                printf("\"%s\"", array[i][j]);
            } else {
                printf(", \"%s\"", array[i][j]);
            }
        }
        printf("]\n");
        printf(" Output: \"%s\"\n", longest_common_prefix(array[i], size));
    }

    return 0;
}
