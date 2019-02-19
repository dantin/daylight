#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

struct Object {
    char *s;
    char *t;
};

char *min_window(char *s, char *t)
{
    // f[]: stores char in s.
    // m[]: stores chars in t.
    int i, f[256], m[256], pat_len = 0;
    memset(m, 0, sizeof(m));
    memset(f, 0, sizeof(f));

    for (i = 0; t[i] != '\0'; i++) {
        m[(int) t[i]]++;
        pat_len++;
    }

    int start = -1;
    int size = INT_MAX;
    int found = 0;
    int begin = 0;
    for (i = 0; s[i] != '\0'; i++) {
        // find right side of the window.
        int right = (int) s[i];
        if (m[right] > 0) {
            if (++f[right] <= m[right]) {
                found++;
            }

            if (found == pat_len) {
                /*
                 * find the left side of the window
                 *
                 * 1) m[s[begin]] == 0 => Both left and right side should be found in t
                 * 2) f[s[begin]] > m[s[begin]] => duplicate chars are more than excepted in the window,
                 *    and we can shrink the size.
                 */
                int left = -1;
                while ((left = (int) s[begin]) && (m[left] == 0 || f[left] > m[left])) {
                    if (f[left] > m[left]) {
                        f[left]--;
                    }
                    begin++;
                }

                // update window size.
                if (size > i - begin + 1) {
                    start = begin;
                    size = i - begin + 1;
                }
            }
        }
    }

    char *result;
    if (start >= 0 && size > 0) {
        result = malloc(size + 1);
        memcpy(result, s + start, size);
        result[size] = '\0';
    } else {
        result = malloc(1);
        result[0] = '\0';
    }
    return result;
}

int main(int argc, char **argv)
{
    struct Object inputs[] = {
        { .s = "ADOBECODEBANC", .t = "ABC" },
    };
    int i, len = sizeof(inputs) / sizeof(struct Object);

    for (i = 0; i < len; i++) {
        char *s = inputs[i].s;
        char *t = inputs[i].t;
        printf("\n Input: S = \"%s\", T = \"%s\"\n", s, t);

        char *window = min_window(s, t);
        printf(" Output: \"%s\"\n", window);

        free(window);
    }

    return EXIT_SUCCESS;
}
