#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct Object {
    char *s;
    char **dict;
    int len;
};

void print_words(char **words, int size)
{
    int i;
    char *s = "";
    printf("[");
    for (i = 0; i < size; i++) {
        printf("%s\"%s\"", s, words[i]);
        s = ", ";
    }
    printf("]");
}

#define container_of(ptr, type, member) \
    ((type *)((char *)(ptr)) - (size_t)&(((type *)0)->member))

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
    return (head->next == head);
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

struct dfs_cache *resize(struct dfs_cache **caches, int index)
{
    int i;
    struct dfs_cache *cache = caches[index];
    if (cache->num + 1 > cache->capacity) {
        cache->capacity *= 2;
        struct list_head **heads = malloc(cache->capacity * sizeof(*heads));
        for (i = 0; i < cache->capacity; i++) {
            if (i < cache->num) {
                heads[i] = cache->heads[i];
            } else {
                heads[i] = malloc(sizeof(struct list_head));
                INIT_LIST_HEAD(heads[i]);
            }
        }
    }
    free(cache->heads);

    return cache;
}

struct dfs_cache *dfs(char *s, char **words, int *sizes, int num,
                      struct dfs_cache **caches, int index)
{

    if (*s == '\0') {
        return NULL;
    } else if (caches[index] != NULL) {
        return caches[index];
    } else {
        int i, j;
        struct dfs_cache *result = malloc(sizeof(*result));
        result->num = 0;
        result->capacity = 1;
        result->heads = malloc(sizeof(struct list_head *));
        result->heads[0] = malloc(sizeof(struct list_head));
        INIT_LIST_HEAD(result->heads[0]);
        caches[index] = result;
        for (i = 0; i < num; i++) {
            if (strlen(s) >= sizes[i] && !memcmp(s, words[i], sizes[i])) {
                struct dfs_cache *next = dfs(s + sizes[i], words, sizes, num, caches, index + sizes[i]);
                if (next != NULL) {
                    int k = result->num;
                    for (j = k; j < k + next->num; j++) {
                        result = resize(caches, index);
                        struct word_node *wn = malloc(sizeof(*wn));
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
                    return NULL;
                }
            }
        }

        return result;
    }
}

bool word_break(char *s, char **word_dict, int word_dict_size)
{
    if (word_dict_size < 1) {
        return false;
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
    bool ret = (dfs(s, word_dict, sizes, word_dict_size, caches, 0) == NULL);

    free(sizes);
    free(caches);

    return ret;
}

int main(int argc, char **argv)
{
    char *dict1[] = { "leet", "code" }, *s1 = "leetcode";
    int len1 = sizeof(dict1) / sizeof(char *);
    char *dict2[] = { "apple", "pen" }, *s2 = "applepenapple";
    int len2 = sizeof(dict2) / sizeof(char *);
    char *dict3[] = { "cats", "dog", "sand", "and", "cat" }, *s3 = "catsandog";
    int len3 = sizeof(dict3) / sizeof(char *);
    struct Object inputs[] = {
        //{ .s = s1, .dict = dict1, .len = len1 },
        //{ .s = s2, .dict = dict2, .len = len2 },
        { .s = s3, .dict = dict3, .len = len3 },
    };
    int i, len = sizeof(inputs) / sizeof(struct Object);

    for (i = 0; i < len; i++) {
        char *s = inputs[i].s;
        char **dict = inputs[i].dict;
        int size = inputs[i].len;

        printf("\n Input: s = \"%s\", wordDict = ", s);
        print_words(dict, size);
        printf("\n");

        bool can = word_break(s, dict, size);
        printf("\n Output: %s\n", can ? "true" : "false");
    }

    return EXIT_SUCCESS;
}
