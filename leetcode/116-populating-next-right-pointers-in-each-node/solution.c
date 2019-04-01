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

void connect(struct TreeLinkNode *root)
{
    if (root == NULL) {
        return;
    }

    struct TreeLinkNode *head = root;
    while (head->left != NULL) {
        struct TreeLinkNode *p;
        for (p = head; p != NULL; p = p->next) {
            p->left->next = p->right;
            p->right->next = p->next == NULL ? NULL : p->next->left;
        }
        head = head->left;
    }
}

int main(int argc, char **argv)
{
    int nums1[] = { 1, 2, 3, 4, 5, 6, 7 }, len1 = sizeof(nums1) / sizeof(int);
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
