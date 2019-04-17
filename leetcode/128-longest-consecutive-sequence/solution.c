#include <stdio.h>
#include <stdlib.h>

struct Object {
    int *nums;
    int len;
};

void print_nums(int *nums, int size)
{
    if (size < 1) {
        printf("[]\n");
        return;
    }
    int i = 0;
    printf("[%d", nums[i]);
    for (i = 1; i < size; i++) {
        printf(", %d", nums[i]);
    }
    printf("]\n");
}

#define container_of(ptr, type, member) \
    ((type *)((char *)(ptr) - (size_t)&(((type *)0)->member)))

#define list_entry(ptr, type, member) \
    container_of(ptr, type, member)

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

int hlist_empty(struct hlist_head *h)
{
    return !h->first;
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

void hlist_del(struct hlist_node *n)
{
    struct hlist_node *next = n->next;
    struct hlist_node **pprev = n->pprev;
    *pprev = next;
    if (next != NULL) {
        next->pprev = pprev;
    }
}

struct seq_node {
    int num;
    struct hlist_node node;
};

unsigned int hash_code(unsigned int num, unsigned int size)
{
    return num % size;
}

struct seq_node *find(int num, int size, struct hlist_head *heads)
{
    int hash = hash_code(num, size);
    struct hlist_node *pos;
    hlist_for_each(pos, &heads[hash]) {
        struct seq_node *node = list_entry(pos, struct seq_node, node);
        if (node->num == num) {
            return node;
        }
    }
    return NULL;
}

int longest_consecutive(int *nums, int nums_size)
{
    int i, hash, length = 0;
    struct seq_node *node;
    struct hlist_head *heads = malloc(nums_size * sizeof(*heads));

    for (i = 0; i < nums_size; i++) {
        INIT_HLIST_HEAD(&heads[i]);
    }

    for (i = 0; i < nums_size; i++) {
        if (!find(nums[i], nums_size, heads)) {
            hash = hash_code(nums[i], nums_size);
            node = malloc(sizeof(*node));
            node->num = nums[i];
            hlist_add_head(&node->node, &heads[hash]);
        }
    }

    for (i = 0; i < nums_size; i++) {
        int len = 0;
        int num;
        node = find(nums[i], nums_size, heads);
        while (node != NULL) {
            len++;
            num = node->num;
            hlist_del(&node->node);

            int left = num;
            while ((node = find(--left, nums_size, heads)) != NULL) {
                len++;
                hlist_del(&node->node);
            }

            int right = num;
            while ((node = find(++right, nums_size, heads)) != NULL) {
                len++;
                hlist_del(&node->node);
            }

            length = len > length ? len : length;
        }
    }

    return length;
}

int main(int argc, char **argv)
{
    int nums1[] = { 100, 4, 200, 1, 3, 2 }, len1 = sizeof(nums1) / sizeof(int);
    int nums2[] = { 2147483646, -2147483647, 0, 2, 2147483644, -2147483645, 2147483645}, len2 = sizeof(nums2) / sizeof(int);
    struct Object inputs[] = {
        { .nums = nums1, .len = len1 },
        { .nums = nums2, .len = len2 },
    };
    int i, len = sizeof(inputs) / sizeof(struct Object);

    for (i = 0; i < len; i++) {
        int *nums = inputs[i].nums;
        int size = inputs[i].len;
        
        printf(" Input: ");
        print_nums(nums, size);

        int length = longest_consecutive(nums, size);
        printf(" Output: %d\n", length);
    }

    return EXIT_SUCCESS;
}
