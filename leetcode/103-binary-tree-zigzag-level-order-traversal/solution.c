#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define BST_MAX_LEVEL 800

#define container_of(ptr, type, member) \
    ((type *)((char *)(ptr) - (size_t)&(((type *)0)->member)))

#define list_entry(ptr, type, member) \
    container_of(ptr, type, member)

#define list_first_entry(ptr, type, field) list_entry((ptr)->next, type, field)
#define list_last_entry(ptr, type, field) list_entry((ptr)->prev, type, field)

#define list_for_each(p, head) \
    for (p = (head)->next; p != (head); p = p->next)

#define list_for_each_reverse(p, head) \
    for (p = (head)->prev; p != (head); p = p->prev)

#define list_for_each_safe(p, n, head) \
    for (p = (head)->next, n = p->next; p != (head); p = n, n = p->next)

#define list_for_each_safe_reverse(p, n, head) \
    for (p = (head)->prev, n = p->prev; p != (head); p = n, n = p->prev)

struct Object {
    int *nums;
    int len;
};

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct list_head {
    struct list_head *next, *prev;
};

struct bfs_node {
    struct TreeNode *node;
    struct list_head link;
};

struct TreeNode *make_tree(int *nums, int pos, int size)
{
    if (nums[pos] == INT_MIN) {
        return NULL;
    }

    struct TreeNode *node = malloc(sizeof(*node));
    node->val = nums[pos];

    int left = 2 * pos + 1;
    int right = 2 * pos + 2;
    if (left >= size) {
        node->left = NULL;
    } else {
        node->left = make_tree(nums, left, size);
    }
    if (right >= size) {
        node->right = NULL;
    } else {
        node->right = make_tree(nums, right, size);
    }

    return node;
}

void free_tree(struct TreeNode *node)
{
    if (node == NULL) {
        return;
    }

    if (node->left != NULL) {
        free_tree(node->left);
    }
    if (node->right != NULL) {
        free_tree(node->right);
    }
    free(node);
}

void print_tree(struct TreeNode *node)
{
    printf("%d ", node->val);
    if (node->left != NULL) {
        print_tree(node->left);
    } else {
        printf("# ");
    }
    if (node->right != NULL) {
        print_tree(node->right);
    } else {
        printf("# ");
    }
}

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

struct bfs_node *node_new(struct list_head *free_list, struct TreeNode *node)
{
    struct bfs_node *new;
    if (list_empty(free_list)) {
        new = malloc(sizeof(*new));
    } else {
        new = list_first_entry(free_list, struct bfs_node, link);
        list_del(&new->link);
    }
    new->node = node;
    return new;
}

void queue(struct list_head *parents, struct list_head *children, int reverse,
           struct list_head *free_list, int **results, int *col_sizes, int level)
{
    struct list_head *p, *n;
    struct bfs_node *new, *parent;

    list_for_each(p, parents) {
        parent = list_entry(p, struct bfs_node, link);
        if (parent->node->left != NULL) {
            new = node_new(free_list, parent->node->left);
            list_add_tail(&new->link, children);
        }
        if (parent->node->right != NULL) {
            new = node_new(free_list, parent->node->right);
            list_add_tail(&new->link, children);
        }
        col_sizes[level]++;
    }

    int i = 0;
    results[level] = malloc(col_sizes[level] * sizeof(int));
    if (reverse) {
        list_for_each_safe_reverse(p, n, parents) {
            parent = list_entry(p, struct bfs_node, link);
            results[level][i++] = parent->node->val;
            list_del(p);
            list_add(p, free_list);
        }
    } else {
        list_for_each_safe(p, n, parents) {
            parent = list_entry(p, struct bfs_node, link);
            results[level][i++] = parent->node->val;
            list_del(p);
            list_add(p, free_list);
        }
    }
}

int ** zigzag_level_order(struct TreeNode *root, int **column_sizes, int *return_size)
{
    if (root == NULL) {
        *return_size = 0;
        return NULL;
    }

    struct list_head free_list;
    struct list_head q0;
    struct list_head q1;
    INIT_LIST_HEAD(&free_list);
    INIT_LIST_HEAD(&q0);
    INIT_LIST_HEAD(&q1);

    int **results = malloc(BST_MAX_LEVEL * sizeof(int *));
    *column_sizes = malloc(BST_MAX_LEVEL * sizeof(int));
    memset(*column_sizes, 0, BST_MAX_LEVEL * sizeof(int));

    int level = 0;
    struct bfs_node *new = node_new(&free_list, root);
    list_add_tail(&new->link, &q0);

    while (!list_empty(&q0) || !list_empty(&q1)) {
        if (level & 0x1) {
            queue(&q1, &q0, 1, &free_list, results, *column_sizes, level);
        } else {
            queue(&q0, &q1, 0, &free_list, results, *column_sizes, level);
        }
        level++;
    }

    *return_size = level;
    return results;
}

int main(int argc, char **argv)
{
    int nums1[] = { 3, 9, 20, INT_MIN, INT_MIN, 15, 7  }, len1 = sizeof(nums1) / sizeof(int);
    struct Object inputs[] = {
        { .nums = nums1, .len = len1  },
    };
    int i, j, k, *col_sizes, len = sizeof(inputs) / sizeof(struct Object);

    for (i = 0; i < len; i++) {
        int *nums = inputs[i].nums;
        int size = inputs[i].len;

        struct TreeNode *root = make_tree(nums, 0, size);
        printf("\n Input: ");
        print_tree(root);
        printf("\n Output:\n");
        int count;
        int **lists = zigzag_level_order(root, &col_sizes, &count);
        for (j = 0; j < count; j++) {
            for (k = 0; k < col_sizes[j]; k++) {
                printf("%d ", lists[j][k]);
            }
            printf("\n");
        }

        free_tree(root);
    }

    return EXIT_SUCCESS;
}
