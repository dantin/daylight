#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

struct Object {
    char *s;
};

bool valid(char c)
{
    return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool is_palindrome(char *s)
{
    int len = strlen(s);
    int low = 0;
    int high = len - 1;

    while (low < high) {
        if (!valid(s[low])) {
            low++;
        } else if (!valid(s[high])) {
            high--;
        } else if (s[low] == s[high]) {
            low++;
            high--;
        } else {
            if (isalpha(s[low]) && isalpha(s[high])) {
                int diff = s[low] > s[high] ? s[low] - s[high] : s[high] - s[low];
                if (diff == 'a' - 'A') {
                    low++;
                    high--;
                } else {
                    return false;
                }
            } else {
                return false;
            }
        }
    }

    return low >= high;
}

int main(int argc, char **argv)
{
    struct Object inputs[] = {
        { .s = "A man, a plan, a canal: Panama" },
        { .s = "race a car" },
    };
    int i, len = sizeof(inputs) / sizeof(struct Object);

    for (i = 0; i < len; i++) {
        char *s = inputs[i].s;

        printf("\n Input: \"%s\"\n", s);
        bool valid = is_palindrome(s);
        printf(" Output: %s\n", valid ? "true" : "false");
    }

    return EXIT_SUCCESS;
}
