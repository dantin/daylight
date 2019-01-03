#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int length_of_longest_substring(const unsigned char *s)
{
    int offset[128];
    int max_len = 0;
    int len = 0;
    int idx = 0;

    memset(offset, 0xff, sizeof(offset));
    while (*s != '\0') {
        if (offset[*s] == -1) {
            len++;
        } else {
            if (idx - offset[*s] > len) {
                len++;
            } else {
                len = idx - offset[*s];
            }
        }
        if (len > max_len) {
            max_len = len;
        }
        offset[*s++] = idx++;
    }

    return max_len;
}

int main(int argc, const char **argv)
{
    char *s[] = {"abcabcbb", "bbbbb", "pwwkew"};
    int i, len = sizeof(s) / sizeof(char *);

    for (i = 0; i < len; i++) {
        printf("\n Input: %s\n Output: %d\n", s[i], length_of_longest_substring((const unsigned char *)s[i]));
    }

    return EXIT_SUCCESS;
}
