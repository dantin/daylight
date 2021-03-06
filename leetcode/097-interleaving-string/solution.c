#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct Object {
    char *s1;
    char *s2;
    char *s3;
};

bool is_interleave(char *s1, char *s2, char *s3)
{
    int i, j;
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    int len3 = strlen(s3);
    if (len1 + len2 != len3) {
        return false;
    }

    bool *table = malloc((len1 + 1) * (len2 + 1) * sizeof(bool));
    bool **dp = malloc((len1 + 1) * sizeof(bool *));
    for (i = 0; i < len1 + 1; i++) {
        dp[i] = &table[i * (len2 + 1)];
    }

    dp[0][0] = true;

    for (i = 1; i < len1 + 1; i++) {
        dp[i][0] = dp[i - 1][0] && s1[i - 1] == s3[i - 1];
    }

    for (i = 1; i < len2 + 1; i++) {
        dp[0][i] = dp[0][i - 1] && s2[i - 1] == s3[i - 1];
    }

    for (i = 1; i < len1 + 1; i++) {
        for (j = 1; j < len2 + 1; j++) {
            bool up = dp[i - 1][j] && s1[i - 1] == s3[i + j - 1];
            bool left = dp[i][j - 1] && s2[j - 1] == s3[i + j - 1];
            dp[i][j] = up || left;
        }
    }

    bool result = dp[len1][len2];
    free(dp);
    free(table);
    return result;
}

int main(int argc, char **argv)
{
    struct Object inputs[] = {
        { .s1 = "aabcc", .s2 = "dbbca", .s3 = "aadbbcbcac" },
        { .s1 = "aabcc", .s2 = "dbbca", .s3 = "aadbbbaccc" },
    };
    int i, len = sizeof(inputs) / sizeof(struct Object);

    for (i = 0; i < len; i++) {
        char *s1 = inputs[i].s1;
        char *s2 = inputs[i].s2;
        char *s3 = inputs[i].s3;

        printf("\n Input: s1 = \"%s\", s2 = \"%s\", s3 = \"%s\"\n", s1, s2, s3);
        bool result = is_interleave(s1, s2, s3);
        printf(" Output: %s\n", result ? "true" : "fasle");
    }
    return EXIT_SUCCESS;
}
