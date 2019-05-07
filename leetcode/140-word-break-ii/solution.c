#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Object {
    char *s;
    char **word_dict;
    int len;
};

void print_strs(char **strs, int size)
{
    char *s = "";
    int i;

    printf("[");
    for (i = 0; i < size; i++) {
        printf("%s\"%s\"", s, strs[i]);
        s = ", ";
    }
    printf("]");
}

#define container_of(ptr, type, member) \
    ((type *)((char *)(ptr) - (size_t)&(((type *)0)->member)))

#define list_entry(ptr, type, member) \
    container_of(ptr, type, member)

#define list_for_each(p, head) \
    for (p = (head)->next; p != (head); p = p->next)

#define list_for_each_safe(p, n, head) \
    for (p = (head)->next, n = p->next; p != (head); p = n, n = p->next)

struct list_head {
    struct list_head *next, *prev;
};

void INIT_LIST_HEAD(struct list_head *list)
{
    list->next = list->prev = list;
}

int list_empty(const struct list_head *head)
{
    return head->next == head;
}

void __list_add(struct list_head *new, struct list_head *prev, struct list_head *next)
{
    next->prev = new;
    new->next = next;
    new->prev = prev;
    prev->next = new;
}

void list_add(struct list_head *_new, struct list_head *head)
{
    __list_add(_new, head, head->next);
}

void list_add_tail(struct list_head *_new, struct list_head *head)
{
    __list_add(_new, head->prev, head);
}

void __list_del(struct list_head *entry)
{
    entry->next->prev = entry->prev;
    entry->prev->next = entry->next;
}

void list_del(struct list_head *entry)
{
    __list_del(entry);
    entry->next = entry->prev = NULL;
}

struct word_node {
    char *word;
    struct list_head link;
};

struct dfs_cache {
    int num;
    int capacity;
    struct list_head **heads;
};

struct dfs_cache *resize(struct dfs_cache **caches, int idx)
{
    struct dfs_cache *cache = caches[idx];
    if (cache->num + 1 > cache->capacity) {
        cache->capacity *= 2;
        struct list_head **heads = malloc(cache->capacity * sizeof(*heads));
        int i;
        for (i = 0; i < cache->capacity; i++) {
            if (i < cache->num) {
                heads[i] = cache->heads[i];
            } else {
                heads[i] = malloc(sizeof(struct list_head));
                INIT_LIST_HEAD(heads[i]);
            }
        }
        free(cache->heads);
        cache->heads = heads;
    }

    return cache;
}

struct dfs_cache *dfs(char *s, char **words, int *sizes, int num,
                      struct dfs_cache **caches, int idx)
{
    struct dfs_cache *result;

    if (*s == '\0') {
        return NULL;
    } else if (caches[idx] != NULL) {
        return caches[idx];
    } else {
        result = malloc(sizeof(*result));
        result->num = 0;
        result->capacity = 1;
        result->heads = malloc(sizeof(struct list_head *));
        result->heads[0] = malloc(sizeof(struct list_head));
        INIT_LIST_HEAD(result->heads[0]);
        caches[idx] = result;

        int i, j;
        for (i = 0; i < num; i++) {
            if (strlen(s) >= sizes[i] && !memcmp(s, words[i], sizes[i])) {
                struct dfs_cache *next = dfs(s + sizes[i], words, sizes, num, caches, idx + sizes[i]);
                struct word_node *wn;
                if (next != NULL) {
                    int k = result->num;
                    for (j = k; j < k + next->num; j++) {
                        result = resize(caches, idx);
                        wn = malloc(sizeof(*wn));
                        wn->word = words[i];
                        list_add(&wn->link, result->heads[j]);

                        struct list_head *p;
                        list_for_each(p, next->heads[j - k]) {
                            struct word_node *wnn = list_entry(p, struct word_node, link);
                            wn = malloc(sizeof(*wn));
                            wn->word = wnn->word;
                            list_add_tail(&wn->link, result->heads[j]);
                        }
                        result->num++;
                    }
                } else {
                    wn = malloc(sizeof(*wn));
                    wn->word = words[i];
                    list_add(&wn->link, result->heads[result->num++]);
                }
            }
        }
    }
    return result;
}

char **word_break(char *s, char **word_dict, int word_dict_size, int *return_size)
{
    if (word_dict_size == 0) {
        *return_size = 0;
        return NULL;
    }

    int i, total = 0;
    int len = strlen(s);
    int *sizes = malloc(word_dict_size * sizeof(int));

    for (i = 0; i < word_dict_size; i++) {
        sizes[i] = strlen(word_dict[i]);
        total += sizes[i];
    }

    struct dfs_cache **caches = malloc(len * sizeof(*caches));
    memset(caches, 0, len * sizeof(*caches));
    struct dfs_cache *cache = dfs(s, word_dict, sizes, word_dict_size, caches, 0);

    char **results = malloc(cache->num * sizeof(char *));
    for (i = 0; i < cache->num; i++) {
        results[i] = malloc(total + 100);
        char *p = results[i];
        struct list_head *n;
        list_for_each(n, cache->heads[i]) {
            struct word_node *wn = list_entry(n, struct word_node, link);
            char *q = wn->word;
            while ((*p++ = *q++) != '\0') {}
            *(p - 1) = ' ';
        }
        *(p - 1) = '\0';
    }

    free(sizes);
    free(caches);

    *return_size = cache->num;
    return results;
}

int main(int argc, char **argv)
{
    char *word_dict1[] = { "cat", "cats", "and", "sand", "dog" }, *s1 = "catsanddog";
    int len1 = sizeof(word_dict1) / sizeof(char *);
    struct Object inputs[] = {
        { .word_dict = word_dict1, .len = len1, .s = s1},
    };
    int i, len = sizeof(inputs) / sizeof(struct Object);

    for (i = 0; i < len; i++) {
        char **word_dict = inputs[i].word_dict;
        int size = inputs[i].len;
        char *s = inputs[i].s;

        printf("\n Input:\n  word dict: ");
        print_strs(word_dict, size);
        printf("\n  s = \"%s\"\n", s);

        int count = 0;
        char **list = word_break(s, word_dict, size, &count);
        printf("\n Output:\n");
        print_strs(list, count);
        printf("\n");
    }

    return EXIT_SUCCESS;
}
