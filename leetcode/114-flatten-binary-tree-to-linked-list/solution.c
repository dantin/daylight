#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

struct Object {
    int *nums;
    int len;
};

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct TreeNode *make_tree_node(int *nums, int pos, int size)
{
    if (pos < 0 || pos >= size || nums[pos] == INT_MIN) {
        return NULL;
    }

    int left = 2 * pos + 1;
    int right = 2 * pos + 2;

    struct TreeNode *node = malloc(sizeof(*node));
    node->val = nums[pos];
    node->left = make_tree_node(nums, left, size);
    node->right = make_tree_node(nums, right, size);

    return node;
}

struct TreeNode *make_tree(int *nums, int size)
{
    return make_tree_node(nums, 0, size);
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

struct TreeNode *partition(struct TreeNode *node)
{
    if (node == NULL) {
        return NULL;
    }

    if (node->right == NULL && node->left == NULL) {
        return node;
    }

    struct TreeNode *left_last = partition(node->left);
    struct TreeNode *right_last = partition(node->right);

    if (left_last != NULL) {
        left_last->right = node->right;
        node->right = node->left;
        node->left = NULL;
    }

    return right_last != NULL ? right_last : left_last;
}

void flatten(struct TreeNode *root)
{
    partition(root);
}

int main(int argc, char **argv)
{
    int nums1[] = { 1, 2, 5, 3, 4, INT_MIN, 6 }, len1 = sizeof(nums1) / sizeof(int);
    struct Object inputs[] = {
        { .nums = nums1, .len = len1 },
    };
    int i, len = sizeof(inputs) / sizeof(struct Object);

    for (i = 0; i < len; i++) {
        int *nums = inputs[i].nums;
        int size = inputs[i].len;

        struct TreeNode *root = make_tree(nums, size);
        printf("\n Input: ");
        print_tree(root);
        printf("\n");

        flatten(root);
        printf(" Output: ");
        print_tree(root);
        printf("\n");

        free_tree(root);
    }

    return EXIT_SUCCESS;
}
