#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define WIDTH 4

void print_strs(char **strs, int size)
{
    if (size < 1) {
        printf("[]");
        return;
    }
    int i;
    printf("[\"%s\"", strs[0]);
    for (i = 1; i < size; i++) {
        printf(", \"%s\"", strs[i]);
    }
    printf("]");
}

void free_strs(char **strs, int size)
{
    int i;
    for (i = 0; i < size; i++) {
        free(strs[i]);
    }
    free(strs);
}

bool valid(char *ip, int len)
{
    if (len > 1 && ip[0] == '0') {
        return false;
    }
    if (len == 3) {
        int n = (ip[0] - '0') * 100 + (ip[1] - '0') * 10 + (ip[2] - '0');
        if (n > 255) {
            return false;
        }
    }
    return true;
}

void dfs(char *s, int start, char *stack, int num, char **results, int *count)
{
    int i, j;
    if (num == 4) {
        if (s[start] == '\0') {
            results[*count] = malloc(3 * 4 + 3 + 1);
            char *p = results[*count];
            for (j = 0; j < num; j++) {
                char *q = stack + j * WIDTH;
                while ((*p++ = *q++) != '\0') {}
                if (j != 3) {
                    *(p - 1) = '.';
                }
            }
        }
        (*count)++;
    } else {
        char *p = stack + num * WIDTH;
        char *q = p;
        for (i = start; s[i] != '\0' && i < start + 3; i++) {
            *q++ = s[i];
            *q = '\0';
            if (!valid(p, q - p)) {
                return;
            }
            dfs(s, i + 1, stack, num + 1, results, count);
            if (num + 1 < 4) {
                memset(stack + (num + 1) * WIDTH, 0, WIDTH);
            }
        }
    }

}

char **restore_ip_addresses(char *s, int *return_size)
{
    int count = 0, capacity = 100;
    char **results = malloc(capacity * sizeof(char *));
    char addr[16] = { '\0' };
    dfs(s, 0, addr, 0, results, &count);

    *return_size = count;
    return results;
}

int main(int argc, char **argv)
{
    char *inputs[] = {
        "25525511135",
    };
    int i, len = sizeof(inputs) / sizeof(char *);
    int return_size;

    for (i = 0; i < len; i++) {
        char *s = inputs[i];

        printf("\n Input: \"%s\"\n", s);
        char **ip_addresses = restore_ip_addresses(s, &return_size);
        printf(" Output: ");
        print_strs(ip_addresses, return_size);
        free_strs(ip_addresses, 100);
    }

    return EXIT_SUCCESS;
}
