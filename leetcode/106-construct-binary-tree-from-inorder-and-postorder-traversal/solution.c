#include <stdio.h>
#include <stdlib.h>

struct Object {
    int *inorder;
    int *postorder;
    int len;
};

void print_nums(int *nums, int size)
{
    if (size < 1) {
        printf("[]\n");
        return;
    }
    int i;
    printf("[%d", nums[0]);
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

struct hlist_node;

struct hlist_head {
    struct hlist_node *first;
};

struct hlist_node {
    struct hlist_node *next;
    struct hlist_node **prev;
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
        h->first->prev = &n->next;
    }
    n->next = h->first;
    n->prev = &h->first;
    h->first = n;
}

void hlist_del(struct hlist_node *n)
{
    struct hlist_node *next = n->next;
    struct hlist_node **prev = n->prev;
    *prev = next;
    if (next != NULL) {
        next->prev = prev;
    }
}

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct order_node {
    struct hlist_node node;
    int val;
    int index;
};

int find(int num, int size, struct hlist_head *heads)
{
    struct hlist_node *p;
    int hash = (num < 0 ? -num : num) % size;
    hlist_for_each(p, &heads[hash]) {
        struct order_node *on = list_entry(p, struct order_node, node);
        if (num == on->val) {
            return on->index;
        }
    }
    return -1;
}

void print_tree(struct TreeNode *node)
{
    if (node == NULL) {
        printf("# ");
        return;
    }
    printf("%d ", node->val);
    print_tree(node->left);
    print_tree(node->right);
}

void free_tree(struct TreeNode *node)
{
    if (node == NULL) {
        return;
    }
    free_tree(node->left);
    free_tree(node->right);
    free(node);
}

void node_add(int val, int index, int size, struct hlist_head *heads)
{
    struct order_node *on = malloc(sizeof(*on));
    on->val = val;
    on->index = index;
    int hash = (val < 0 ? -val : val) % size;
    hlist_add_head(&on->node, &heads[hash]);
}

struct TreeNode *dfs(int *inorder, int in_low, int in_high,
                     int *postorder, int post_low, int post_high,
                     struct hlist_head *in_heads, int size)
{
    if (in_low > in_high || post_low > post_high) {
        return NULL;
    }
    struct TreeNode *tn = malloc(sizeof(*tn));
    tn->val = postorder[post_high];
    int index = find(postorder[post_high], size, in_heads);
    tn->left = dfs(inorder, in_low, index - 1, postorder, post_low, post_low + (index - 1 - in_low), in_heads, size);
    tn->right = dfs(inorder, index + 1, in_high, postorder, post_high - (in_high - index), post_high - 1, in_heads, size);
    return tn;
}

struct TreeNode *build_tree(int *inorder, int inorder_size, int *postorder, int postorder_size)
{
    int i;
    if (inorder_size != postorder_size) {
        return NULL;
    }
    struct hlist_head *in_heads = malloc(inorder_size * sizeof(*in_heads));
    for (i = 0; i < inorder_size; i++) {
        INIT_HLIST_HEAD(&in_heads[i]);
    }
    for (i = 0; i < inorder_size; i++) {
        node_add(inorder[i], i, inorder_size, in_heads);
    }

    return dfs(inorder, 0, inorder_size - 1, postorder, 0, postorder_size - 1, in_heads, inorder_size);
}

int main(int argc, char **argv)
{
    int inorder1[]   = { 9, 3, 15, 20, 7 };
    int postorder1[] = { 9, 15, 7, 20, 3 };
    int len1 = sizeof(postorder1) / sizeof(int);
    struct Object inputs[] = {
        { .inorder = inorder1, .postorder = postorder1, .len = len1 },
    };
    int i, len = sizeof(inputs) / sizeof(struct Object);

    for (i = 0; i < len; i++) {
        int *inorder = inputs[i].inorder;
        int *postorder = inputs[i].postorder;
        int size = inputs[i].len;

        printf("\n Input:\n");
        printf("  inorder: ");
        print_nums(inorder, size);
        printf("  postorder: ");
        print_nums(postorder, size);

        struct TreeNode *root = build_tree(inorder, size, postorder, size);
        printf("\n Output:\n ");
        print_tree(root);
        printf("\n");
        free_tree(root);
    }

    return EXIT_SUCCESS;
}
