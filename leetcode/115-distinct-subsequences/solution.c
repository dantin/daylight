#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Object {
    char *s;
    char *t;
};

int num_distinct(char *s, char *t)
{
    int s_len = strlen(s);
    int t_len = strlen(t);
    // empty result.
    if (t_len == 0 || s_len < t_len) {
        return 0;
    }

    // t[0] start from the end of s.
    int start = 0;
    while (start < s_len && s[start] != t[0]) {
        start++;
    }
    if (start == s_len) {
        return 0;
    }

    // initialize dp 2d-array.
    int i, j;
    long *table = malloc((s_len - start) * t_len * sizeof(long));
    long **dp = malloc((s_len - start) * sizeof(long *));
    for (i = 0; i < s_len - start; i++) {
        dp[i] = &table[i * t_len];
    }

    // dp
    dp[0][0] = 1;
    for (i = 1; i < t_len; i++) {
        dp[0][i] = 0;
    }

    for (i = 1; i < s_len - start; i++) {
        dp[i][0] = dp[i - 1][0];
        if (s[start + i] == t[0]) {
            dp[i][0]++;
        }
    }

    for (i = 1; i < s_len - start; i++) {
        for (j = 1; j < t_len; j++) {
            dp[i][j] = dp[i - 1][j];
            if (s[start + i] == t[j]) {
                dp[i][j] += dp[i - 1][j - 1];
            }
        }
    }

    int num = (int) dp[s_len - start - 1][t_len - 1];

    free(table);
    free(dp);

    return num;
}

int main(int argc, char **argv)
{
    char *s1 = "rabbbit", *t1 = "rabbit";
    char *s2 = "babgbag", *t2 = "bag";
    struct Object inputs[] = {
        { .s = s1, .t = t1 },
        { .s = s2, .t = t2 },
    };
    int i, len = sizeof(inputs) / sizeof(struct Object);

    for (i = 0; i < len; i++) {
        char *s = inputs[i].s;
        char *t = inputs[i].t;

        printf("\n Input: S = \"%s\", T = \"%s\"\n", s, t);
        int num = num_distinct(s, t);
        printf(" Output: %d\n", num);
    }

    return EXIT_SUCCESS;
}
