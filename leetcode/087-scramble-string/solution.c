#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define N 128

struct Object {
    char *s1;
    char *s2;
};

/**
 * The recursive way.
 *
 *  1) break the string to two parts: 
 *        s1[0..j]   s1[j+1..n]
 *        s2[0..j]   s2[j+1..n]
 *  2) then
 *       scramble(s1[0..j], s2[0..j]) && scramble(s1[j+1..n], s2[j+1..n])
 *     or
 *       scramble(s1[0..j], s2[n - j - 1, n]) && scramble(s1[j+1..n], s2[0..n - j])
 */
bool scramble(char *s1, int low1, int high1, char *s2, int low2, int high2)
{
    if (high1 - low1 != high2 - low2) {
        return false;
    } else if (!memcmp(s1 + low1, s2 + low2, high1 - low1 + 1)) {
        return true;
    } else {
        int i, chr, c1[N], c2[N];
        memset(c1, 0, N * sizeof(int));
        memset(c2, 0, N * sizeof(int));
        for (i = low1; i <= high1; i++) {
            chr = s1[i];
            c1[chr]++;
        }
        for (i = low2; i <= high2; i++) {
            chr = s2[i];
            c2[chr]++;
        }
        if (memcmp(c1, c2, N * sizeof(int))) {
            return false;
        } else {
            int len = high1 - low1 + 1;
            for (i = 1; i < len; i++) {
                if (scramble(s1, low1, low1 + i - 1, s2, low2, low2 + i - 1) &&
                    scramble(s1, low1 + i, high1, s2, low2 + i, high2)) {
                    return true;
                }
                if (scramble(s1, low1, low1 + i - 1, s2, high2 - i + 1, high2) &&
                    scramble(s1, low1 + i, high1, s2, low2, high2 - i)) {
                    return true;
                }
            }
            return false;
        }
    }
}

bool is_scramble(char *s1, char *s2)
{
    return scramble(s1, 0, strlen(s1) - 1, s2, 0, strlen(s2) - 1);
}

int main(int argc, char **argv)
{
    struct Object inputs[] = {
        { .s1 = "great", .s2 = "rgeat" },
        { .s1 = "abcde", .s2 = "caebd" },
        { .s1 = "abc",   .s2 = "cab" },
    };
    int i, len = sizeof(inputs) / sizeof(struct Object);

    for (i = 0; i < len; i++) {
        char *s1 = inputs[i].s1;
        char *s2 = inputs[i].s2;

        printf("\n Input: s1 = \"%s\", s2 = \"%s\"\n", s1, s2);
        bool result = is_scramble(s1, s2);
        printf(" Output: %s\n", result ? "true" : "false");
    }
    return EXIT_SUCCESS;
}
