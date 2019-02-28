#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int num_decodings(char *s)
{
    int len = strlen(s);
    if (len == 0) {
        return 0;
    }

    int dp[len + 1];
    memset(dp, 0, (len + 1) * sizeof(int));

    dp[0] = 1;
    dp[1] = s[0] == '0' ? 0 : 1;
    for (int i = 2; i <= len; i++) {
        if (s[i - 1] != '0') {
            dp[i] = dp[i - 1];
        }

        int num = (s[i - 2] - '0') * 10 + (s[i - 1] - '0');
        if (num >= 10 && num <= 26) {
            dp[i] += dp[i - 2];
        }
    }

    return dp[len];
}

int main(int argc, char **argv)
{
    char *inputs[] = {
        "12",
        "226",
    };
    int i, len = sizeof(inputs) / sizeof(char *);

    for (i = 0; i < len; i++) {
        char *s = inputs[i];

        printf("\n Input: \"%s\"\n", s);
        int num = num_decodings(s);
        printf(" Output: %d\n", num);
    }

    return EXIT_SUCCESS;
}
