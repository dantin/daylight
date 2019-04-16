#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Object {
    char *begin_word;
    char *end_word;
    char **word_list;
    int len;
};

void print_words(char **words, int size)
{
    if (size < 1) {
        printf("[]");
        return;
    }
    int i = 0;
    printf("[\"%s\"", words[i]);
    for (i = 1; i < size; i++) {
        printf(", \"%s\"", words[i]);
    }
    printf("]");
}

#define container_of(ptr, type, member) \
    ((type *)((char *)(ptr) - (size_t)&(((type *)0)->member)))

#define list_entry(ptr, type, member) \
    container_of(ptr, type, member)

#define list_first_entry(ptr, type, field) list_entry((ptr)->next, type, field)
#define list_last_entry(ptr, type, field) list_entry((ptr)->prev, type, field)

#define list_for_each(p, head) \
    for (p = (head)->next; p != (head); p = p->next)

#define list_for_each_safe(p, n, head) \
    for (p = (head)->next, n = p->next; p != (head); p = n, n = p->next)

#define hlist_for_each(pos, head) \
    for (pos = (head)->first; pos; pos = pos->next)

#define hlist_for_each_safe(pos, n, head) \
    for (pos = (head)->first; pos && ({ n = pos->next; true; }); pos = n)

struct hlist_node;

struct hlist_head {
    struct hlist_node *first;
};

struct hlist_node {
    struct hlist_node *next, **pprev;
};

void INIT_HLIST_HEAD(struct hlist_head *h)
{
    h->first = NULL;
}

void hlist_add_head(struct hlist_node *n, struct hlist_head *h)
{
    if (h->first != NULL) {
        h->first->pprev = &n->next;
    }
    n->next = h->first;
    n->pprev = &h->first;
    h->first = n;
}

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
    int step;
    char *word;
    struct hlist_node node;
    struct list_head link;
};

int BKDRHash(char *str, int size)
{
    int seed = 131;
    unsigned int hash = 0;
    while (*str != '\0') {
        hash = hash * seed + (*str++);
    }
    return hash % size;
}

struct word_node *find(char *word, struct hlist_head *hhead, int size)
{
    struct hlist_node *p;
    int hash = BKDRHash(word, size);
    hlist_for_each(p, &hhead[hash]) {
        struct word_node *node = list_entry(p, struct word_node, node);
        if (node->step == 0 && !strcmp(node->word, word)) {
            return node;
        }
    }
    return NULL;
}

int ladder_length(char *begin_word, char *end_word, char **word_list, int word_list_size)
{
    int i, len = strlen(begin_word);
    char *word = malloc(len + 1);
    struct list_head queue;
    struct word_node *node;

    struct hlist_head *hhead = malloc(word_list_size * sizeof(*hhead));
    for (i = 0; i < word_list_size; i++) {
        INIT_HLIST_HEAD(hhead + i);
    }

    for (i = 0; i < word_list_size; i++) {
        node = malloc(sizeof(*node));
        node->word = word_list[i];
        node->step = 0;
        int hash = BKDRHash(word_list[i], word_list_size);
        hlist_add_head(&node->node, &hhead[hash]);
    }

    INIT_LIST_HEAD(&queue);
    struct word_node *first = malloc(sizeof(*node));
    first->word = begin_word;
    first->step = 1;

    while (strcmp(first->word, end_word)) {
        strcpy(word, first->word);
        for (i = 0; i < len; i++) {
            char c;
            char o = word[i];
            for (c = 'a'; c <= 'z'; c++) {
                if (c == o) continue;
                word[i] = c;
                node = find(word, hhead, word_list_size);
                if (node != NULL) {
                    list_add_tail(&node->link, &queue);
                    node->step = first->step + 1;
                }
            }
            word[i] = o;
        }

        if (list_empty(&queue)) {
            return 0;
        } else {
            first = list_first_entry(&queue, struct word_node, link);
            list_del(&first->link);
        }
    }

    return first->step;
}

int main(int argc, char **argv)
{
    char *begin_word1 = "hit", *end_word1 = "cog";
    char *word_list1[] = { "hot", "dot", "dog", "lot", "log", "cog" };
    int len1 = sizeof(word_list1) / sizeof(char *);
    struct Object inputs[] = {
        { .begin_word = begin_word1, .end_word = end_word1, .word_list = word_list1, .len = len1 },
    };
    int i, len = sizeof(inputs) / sizeof(struct Object);

    for (i = 0; i < len; i++) {
        char *begin_word = inputs[i].begin_word;
        char *end_word = inputs[i].end_word;
        char **word_list = inputs[i].word_list;
        int size = inputs[i].len;

        printf("\n Input:\n");
        printf(" beginWord = \"%s\"\n", begin_word);
        printf(" endWord = \"%s\"\n", end_word);
        printf(" wordList = ");
        print_words(word_list, size);
        printf("\n");

        int length = ladder_length(begin_word, end_word, word_list, size);

        printf("\n Output: %d\n", length);
    }

    return EXIT_SUCCESS;
}
