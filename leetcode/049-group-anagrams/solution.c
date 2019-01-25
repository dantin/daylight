#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct object {
    char **strs;
    int len;
};

void print_strs(char **strs, int size)
{
    int i;
    if (size < 0) {
        printf("[]\n");
        return;
    }

    printf("[\"%s\"", strs[0]);
    for (i = 1; i < size; i++) {
        printf(", \"%s\"", strs[i]);
    }
    printf("]\n");
}

struct word_hash {
    char *word;
    int num;
    int indexes[10];
};

int compare(const void *lhs, const void *rhs)
{
    return *(char *) lhs - *(char *) rhs;
}

inline int BKDRHash(char *s, size_t size)
{
    int seed = 31; /* 131 1313 13131... */
    unsigned long hash = 0;

    while (*s != '\0') {
        hash = hash * seed + *s++;
    }

    return hash % size;
}

char *** group_anagrams(char **strs, int strs_size, int **column_sizes, int *return_size)
{
    int i, j, count = 0;
    int hash_size = strs_size;
    struct word_hash *ht = calloc(hash_size, sizeof(*ht));

    char **words = malloc(strs_size * sizeof(char *));
    for (i = 0; i < strs_size; i++) {
        int len = strlen(strs[i]);
        words[i] = malloc(len + 1);
        strcpy(words[i], strs[i]);
        // sort words here to make sure anagram have the same hash code.
        qsort(words[i], len, sizeof(char), compare);
        int hash = BKDRHash(words[i], hash_size);
        // find avaible hash bucket.
        for (j = hash; ht[j].num > 0 && strcmp(ht[j].word, words[i]);) {
            j = ++j % hash_size;
        }
        if (ht[j].num == 0) {
            ht[j].word = words[i];
            count++;
        }
        ht[j].indexes[ht[j].num++] = i;
    }

    int k = 0;
    char ***lists = malloc(count * sizeof(char **));
    *column_sizes = malloc(count * sizeof(int));

    for (i = 0; i < hash_size; i++) {
        if (ht[i].num > 0) {
            (*column_sizes)[k] = ht[i].num;
            lists[k] = malloc(ht[i].num * sizeof(char *));
            for (j = 0; j < ht[i].num; j++) {
                int idx = ht[i].indexes[j];
                lists[k][j] = strs[idx];
            }
            k++;
        }
    }

    *return_size = count;
    return lists;
}

int main(int argc, char **argv)
{
    char *strs1[] = {"eat", "tea", "tan", "ate", "nat", "bat"};
    int len1 = sizeof(strs1) / sizeof(char *);
    struct object inputs[] = {
        {.strs = strs1, .len = len1},
    };
    int i, j, len = sizeof(inputs) / sizeof(struct object);
    int *column_sizes, count = 0, indent = 1;
    
    for (i = 0; i < len; i++) {
        char **strs = inputs[i].strs;
        int size = inputs[i].len;
        printf("\n Input: "); print_strs(strs, size);
        char ***lists = group_anagrams(strs, size, &column_sizes, &count);

        printf(" Output:\n");
        if (count < 1) {
            printf("%*s[]", indent, "");
            continue;
        }
        printf("%*s[\n", indent, "");
        indent += 2;
        for (j = 0; j < count; j++) {
            printf("%*s", indent, "");
            print_strs(lists[j], column_sizes[j]);
        }
        indent -= 2;
        printf("%*s]\n", indent, "");
    }

    return EXIT_SUCCESS;
}
