#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define PAL_BUFFER_SIZE 2000
#define PAL_PADBUF_SIZE (PAL_BUFFER_SIZE + (PAL_BUFFER_SIZE / 2))

#define PAL_CHAR_END    '\0'
#define PAL_CHAR_DOLLAR '$'
#define PAL_CHAR_POND   '#'

inline int min(int lhs, int rhs)
{
    return lhs < rhs ? lhs : rhs;
}

int manacher(char *s, char *output)
{
    int i, j;
    char s2[PAL_PADBUF_SIZE] = { PAL_CHAR_END };

    s2[0] = PAL_CHAR_DOLLAR;
    for (i = 0; s[i] != PAL_CHAR_END; i++) {
        s2[(i<<1)+1] = PAL_CHAR_POND;
        s2[(i<<1)+2] = s[i];
    }
    s2[(i<<1)+1] = PAL_CHAR_POND;
    int len = (i<<1)+2;
    s2[len] = PAL_CHAR_END;

    int p[PAL_PADBUF_SIZE] = { 0 };
    int id = 0;      // center index of palindrom.
    int limit = 0;   // right side of max palindrom.
    int max_len = 0; // length of max palindrom.
    int max_id = 0;  // center index of max palindrom.

    for (i = 1; i < len; i++) {
        if (i < limit) {
            p[i] = min(p[2*id-i], limit-i);
        } else {
            p[i] = 1;
        }

        while (s2[i+p[i]] == s2[i-p[i]]) {
            p[i]++;
        }

        if (i+p[i] > limit) {
            limit = i+p[i];
            id = i;
        }
        if (max_len < p[i]-1) {
            max_len = p[i] - 1;
            max_id = i;
        }
    }

    for (j = 0, i = max_id - max_len; i <= max_id + max_len; i++) {
        if (s2[i] != PAL_CHAR_POND) {
            output[j++] = s2[i];
        }
    }

    return max_len;
}

char *longest_palindrom(char *s)
{
    int i;
    if (s == NULL) {
        return NULL;
    }

    int len = strlen(s);
    if (len <= 1) {
        return s;
    }

    char *palindrom = malloc(PAL_BUFFER_SIZE);
    memset(palindrom, 0, sizeof(palindrom));

    int size = manacher(s, palindrom);
    palindrom[size] = PAL_CHAR_END;

    return palindrom;
}

int main(int argc, const char *argv[])
{
    int i;
    char *inputs[] = {"babad", "cbbd"};
    int len = sizeof(inputs) / sizeof(char *);

    for (i = 0; i < len; i++) {
        printf("%s\n%s\n", inputs[i], longest_palindrom(inputs[i]));
    }

    return 0;
}
