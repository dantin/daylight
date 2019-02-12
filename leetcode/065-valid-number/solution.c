#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

bool is_number(char *s)
{
    while (*s == ' ') {
        ++s;
    }
    bool found_num = false;
    if (*s == '-' || *s == '+') {
        ++s;
    }
    while (isdigit(*s)) {
        found_num = true;
        ++s;
    }
    if (*s == '.') {
        ++s;
    }
    while (isdigit(*s)) {
        found_num = true;
        ++s;
    }

    if (found_num && *s == 'e') {
        ++s;
        if (*s == '+' || *s == '-') {
            ++s;
        }
        found_num = false;
        while (isdigit(*s)) {
            found_num = true;
            ++s;
        }
    }
    while (*s == ' ') {
        ++s;
    }

    return *s == '\0' && found_num;
}

int main(int argc, char **argv)
{
    char *inputs[] = {
        "0",
        " 0.1 ",
        "abc",
        "1 a",
        "2e10",
        " -90e3    ",
        " 1e",
        "e3",
        " 6e-1",
        " 99e2.5 ",
        "53.5e93",
        " --6 ",
        "-+3",
        "95a54e53",
    };
    int i, len = sizeof(inputs) / sizeof(char *);

    for (i = 0; i < len; i++) {
        char *s = inputs[i];
        bool valid = is_number(s);
        printf("\"%s\" => %s\n", s, valid ? "true" : "false");
    }

    return EXIT_SUCCESS;
}
