#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define container_of(ptr, type, member) \
        ((type *)((char *)(ptr) - (size_t)&(((type *)0)->member)))

#define list_entry(ptr, type, member) \
        container_of(ptr, type, member)

#define hlist_for_each(pos, head) \
    for (pos = (head)->first; pos; pos = pos->next)

struct object {
    char *s;
    char **words;
    int size;
};

void print_array(char **words, int size)
{
    int i;
    if (size == 0) {
        printf("[]\n");
        return;
    }

    printf("[\"%s\"", words[0]);
    for (i = 1; i < size; i++) {
        printf(", \"%s\"", words[i]);
    }
    printf("]\n");
}

void print_nums(int *nums, int size)
{
    int i;
    if (size == 0) {
        printf("[]\n");
        return;
    }

    printf("[%d", nums[0]);
    for (i = 1; i < size; i++) {
        printf(", %d", nums[i]);
    }
    printf("]\n");
}

struct hlist_node{
    struct hlist_node *next, **pprev;
};

struct hlist_head {
    struct hlist_node *first;
};

struct word_node {
    struct hlist_node node;
    char *word;
    int idx;
};

inline void INIT_HLIST_HEAD(struct hlist_head *h)
{
    h->first = NULL;
}

inline int hlist_empty(struct hlist_head *h) {
    return !h->first;
}

inline void hlist_add_head(struct hlist_node *n, struct hlist_head *h)
{
    if (h->first != NULL) {
        h->first->pprev = &n->next;
    }
    n->next = h->first;
    n->pprev = &h->first;
    h->first = n;
}

inline int BKDRHash(char *s, size_t size)
{
    int seed = 131; /* 131 1313 13131... */
    unsigned long hash = 0;
    while (*s != '\0') {
        hash = hash * seed + *s++;
    }
    return hash % size;
}

int find(char *word, struct hlist_head *heads, int size)
{
    int hash = BKDRHash(word, size);
    struct hlist_node *pos;
    hlist_for_each(pos, &heads[hash]) {
        struct word_node *wn = list_entry(pos, struct word_node, node);
        if (!strcmp(wn->word, word)) {
            return wn->idx;
        }
    }
    return -1;
}

void add(char **words, int idx, struct hlist_head *heads, int size, int *freqs)
{
    int hash = BKDRHash(words[idx], size);
    struct hlist_node *pos;
    struct word_node *wn;

    hlist_for_each(pos, &heads[hash]) {
        wn = list_entry(pos, struct word_node, node);
        if (!strcmp(wn->word, words[idx])) {
            freqs[wn->idx]++;
            return;
        }
    }
    wn = malloc(sizeof(*wn));
    wn->word = words[idx];
    wn->idx = idx;
    hlist_add_head(&wn->node, &heads[hash]);
    freqs[wn->idx]++;
}

int *find_substring(char *s, char **words, int words_size, int *return_size)
{
    if (*s == '\0' || words_size == 0) {
        *return_size = 0;
        return NULL;
    }

    int i, j, cap = 10000, count = 0;
    int hash_size = words_size;
    struct hlist_head *heads = malloc(hash_size * sizeof(*heads));
    for (i = 0; i < hash_size; i++) {
        INIT_HLIST_HEAD(&heads[i]);
    }

    int *freqs = malloc(words_size * sizeof(int));
    memset(freqs, 0, words_size * sizeof(int));

    for (i = 0; i < words_size; i++) {
        add(words, i, heads, hash_size, freqs);
    }

    int len = strlen(words[0]);
    int length = len * words_size - 1;
    char *word = malloc(len + 1);
    word[len] = '\0';
    int *indexes = malloc(cap * sizeof(int));
    for (i = 0; s[i] != '\0'; i++) {
        memcpy(word, s+i, len);
        indexes[i] = find(word, heads, hash_size);
    }

    int *results = malloc(cap * sizeof(int));
    int *fqs = malloc(words_size * sizeof(int));
    for (i = 0; s[i + length] != '\0'; i++) {
        memset(fqs, 0, words_size * sizeof(int));
        for (j = 0; j < words_size; j++) {
            int idx = indexes[i + j * len];
            if (idx < 0 || ++fqs[idx] > freqs[idx]) {
                break;
            }
        }
        if (j == words_size) {
            results[count++] = i;
        }
    }

    *return_size = count;
    return results;
}

int main(int argc, char **argv)
{
    char *words1[] = {"foo", "bar"};
    char *words2[] = {"word", "good", "best", "word"};
    int len1 = sizeof(words1) / sizeof(char *);
    int len2 = sizeof(words2) / sizeof(char *);

    struct object inputs[] = {
        {.s = "barfoothefoobarman",       .words = words1, .size = len1},
        {.s = "wordgoodgoodgoodbestword", .words = words2, .size = len2},
    };
    int i, count, len = sizeof(inputs) / sizeof(struct object);

    for (i = 0; i < len; i++) {
        char *s  = inputs[i].s, **words = inputs[i].words;
        int size = inputs[i].size;

        printf("\n s = %s\n", s);
        printf(" words = "); print_array(words, size);

        int *results = find_substring(s, words, size, &count);
        printf(" Output: "); print_nums(results, count);
    }

    return EXIT_SUCCESS;
}
