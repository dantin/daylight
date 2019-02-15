#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *simplify_path(char *path)
{
    int len = strlen(path);
    if (len == 0) {
        return path;
    }

    char *p = path;
    int *indexes = malloc(len * sizeof(int));
    int depth = 0;
    int name_start = 1;
    while (*p != '\0') {
        if (*p == '/') {
            if (p > path && *(p - 1) != '/' && *(p - 1) != '.') {
                name_start = 1;
            }
        } else if (*p == '.') {
            if (*(p + 1) == '\0' || *(p + 1) == '/') {
                p += 1;
            } else if (*(p + 1) == '.' && (*(p + 2) == '\0' || *(p + 2) == '/')) {
                if (depth > 0) {
                    depth--;
                    name_start = 1;
                }
                p += 2;
            } else {
                indexes[depth++] = p - path;
                while (*p != '/' && *p != '\0') {
                    p++;
                }
            }
            if (*p == '\0') {
                break;
            }
        } else {
            if (name_start && depth >= 0) {
                // store index.
                indexes[depth++] = p - path;
                name_start = 0;
            }
        }
        p++;
    }

    int i;
    char *result = malloc(len + 1);
    char *q = result;
    if (depth <= 0) {
        *q++ = '/';
    } else {
        for (i = 0; i < depth; i++) {
            p = path + indexes[i];
            *q++ = '/';
            while (*p != '/' && *p != '\0') {
                *q++ = *p++;
            }
        }
    }
    *q = '\0';
    free(indexes);

    return result;
}

int main(int argc, char **argv)
{
    char *inputs[] = {
        "/home/",
        "/../",
        "/home//foo/",
        "/a/./b/../../c/",
        "/a/../../b/../c//.//",
        "/a//b////c/d//././/..",
        "/...",
    };
    int i, len = sizeof(inputs) / sizeof(char *);

    for (i = 0; i < len; i++) {
        char *path = inputs[i];
        printf("\n Input: \"%s\"\n", path);
        char *simple_path = simplify_path(path);
        printf(" Output: \"%s\"\n", simple_path);
        free(simple_path);
    }

    return EXIT_SUCCESS;
}
