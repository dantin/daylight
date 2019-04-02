#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Object {
    int *nums;
    int len;
};

struct TreeLinkNode {
    int val;
    struct TreeLinkNode *left;
    struct TreeLinkNode *right;
    struct TreeLinkNode *next;
};

struct TreeLinkNode *make_tree_node(int *nums, int pos, int size)
{
    if (pos < 0 || pos >= size || nums[pos] == INT_MIN) {
        return NULL;
    }

    int left = 2 * pos + 1;
    int right = 2 * pos + 2;

    struct TreeLinkNode *node = malloc(sizeof(*node));
    node->val = nums[pos];
    node->next = NULL;
    node->left = make_tree_node(nums, left, size);
    node->right = make_tree_node(nums, right, size);

    return node;
}

struct TreeLinkNode *make_tree(int *nums, int size)
{
    return make_tree_node(nums, 0, size);
}

void print_tree(struct TreeLinkNode *node)
{
    if (node == NULL) {
        printf("# ");
        return;
    }

    printf("%d ", node->val);
    print_tree(node->left);
    print_tree(node->right);
}

void free_tree(struct TreeLinkNode *node)
{
    if (node == NULL) {
        return;
    }

    free_tree(node->left);
    free_tree(node->right);
    free(node);
}

#define container_of(ptr, type, member) \
    ((type *)((char *)(ptr) - (size_t)&(((type *)0)->member)))

#define list_entry(ptr, type, member) \
    container_of(ptr, type, member)

#define list_first_entry(ptr, type, field)  list_entry((ptr)->next, type, field)
#define list_last_entry(ptr, type, field)  list_entry((ptr)->prev, type, field)

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

struct bfs_node {
    struct TreeLinkNode *node;
    struct list_head link;
};

struct bfs_node *node_fetch(struct list_head *free_list, struct TreeLinkNode *node)
{
    struct bfs_node *bn = list_first_entry(free_list, struct bfs_node, link);
    list_del(&bn->link);
    bn->node = node;
    return bn;
}

void queue(struct list_head *parents, struct list_head *children, struct list_head *free_list)
{
    struct list_head *p, *n;
    struct TreeLinkNode *prev = NULL;
    list_for_each_safe(p, n, parents) {
        struct bfs_node *new;
        struct bfs_node *parent = list_entry(p, struct bfs_node, link);
        struct TreeLinkNode *lch = parent->node->left;
        struct TreeLinkNode *rch = parent->node->right;
        if (lch != NULL) {
            if (prev != NULL) {
                prev->next = lch;
            }
            prev = lch;
            new = node_fetch(free_list, lch);
            list_add_tail(&new->link, children);
        }
        if (rch != NULL) {
            if (prev != NULL) {
                prev->next = rch;
            }
            prev = rch;
            new = node_fetch(free_list, rch);
            list_add_tail(&new->link, children);
        }

        list_del(p);
        list_add(p, free_list);
    }
}

void connect(struct TreeLinkNode *root)
{
    int buffer_size = 4096;

    if (root == NULL) {
        return;
    }

    struct list_head free_list;
    struct list_head q0;
    struct list_head q1;
    struct bfs_node nodes[buffer_size];
    INIT_LIST_HEAD(&free_list);
    INIT_LIST_HEAD(&q0);
    INIT_LIST_HEAD(&q1);

    int i;
    for (i = 0; i < buffer_size; i++) {
        list_add(&nodes[i].link, &free_list);
    }

    int level = 0;
    struct bfs_node *new = node_fetch(&free_list, root);
    list_add_tail(&new->link, &q0);

    while (!list_empty(&q0) || !list_empty(&q1)) {
        if (level & 0x1) {
            queue(&q1, &q0, &free_list);
        } else {
            queue(&q0, &q1, &free_list);
        }
        level++;
    }
}

int main(int argc, char **argv)
{
    int nums1[] = { 1, 2, 3, 4, 5, INT_MIN, 7 }, len1 = sizeof(nums1) / sizeof(int);
    struct Object inputs[] = {
        { .nums = nums1, .len = len1 },
    };
    int i, len = sizeof(inputs) / sizeof(struct Object);

    for (i = 0; i < len; i++) {
        int *nums = inputs[i].nums;
        int size = inputs[i].len;

        struct TreeLinkNode *root = make_tree(nums, size);
        printf("\n Input: ");
        print_tree(root);
        printf("\n");

        connect(root);

        printf("\n Output: ");
        print_tree(root);
        printf("\n");

        free_tree(root);
    }

    return EXIT_SUCCESS;
}
