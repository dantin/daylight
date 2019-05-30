#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Object {
    char *s;
};

void reverse(char *s, int low, int high)
{
    while (low < high) {
        char c = s[low];
        s[low] = s[high];
        s[high] = c;
        low++;
        high--;
    }
}

char *reverse_words(char *s)
{
    int i = 0, j = 0;
    while (s[i] != '\0') {
        while (s[i] == ' ') {
            i++;
        }
        if (s[i] == '\0') {
            break;
        }
        while (s[i] != '\0' && s[i] != ' ') {
            s[j++] = s[i++];
        }
        s[j++] = s[i];
    }
    if (j == 0) {
        if (i > 0) {
            s[j] = '\0';
        }
        return s;
    }
    s[--j] = '\0';
    reverse(s, 0, j - 1);

    for (i = 0, j = 0; s[i] != '\0';) {
        for (j = i; s[j] != '\0' && s[j] != ' '; j++) {}
        reverse(s, i, j - 1);
        for (i = j; s[i] != '\0' && s[i] == ' '; i++) {}
    }

    return s;
}

int main(int argc, char **argv)
{
    struct Object inputs[] = {
        { .s = "the sky is blue" },
        { .s = "  hello world!" },
        { .s = "a good   example" },
        { .s = "" },
        { .s = " " },
    };
    int i, len = sizeof(inputs) / sizeof(struct Object);

    for (i = 0; i < len; i++) {
        char *s = inputs[i].s;
        char *buf = malloc(strlen(s) + 1);
        strcpy(buf, s);

        printf("\n Input: \"%s\"", buf);
        char *r = reverse_words(buf);
        printf("\n Output: \"%s\"\n", r);

        free(buf);
    }

    return EXIT_SUCCESS;
}
