#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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

int depth(struct TreeNode *root, bool *balance)
{
    if (!(*balance) || root == NULL) {
        return 0;
    }

    int l = depth(root->left, balance) + 1;
    int r = depth(root->right, balance) + 1;
    if (*balance) {
        int diff = l > r ? l - r : r - l;
        *balance = diff < 2;
    }
    return l > r ? l : r;
}

bool is_balanced(struct TreeNode *root)
{
    bool balance = true;
    depth(root, &balance);
    return balance;
}

int main(int argc, char **argv)
{
    int nums1[] = { 3, 9, 20, INT_MIN, INT_MIN, 15, 7 }, len1 = sizeof(nums1) / sizeof(int);
    int nums2[] = { 1, 2, 2, 3, 3, INT_MIN, INT_MIN, 4, 4 }, len2 = sizeof(nums2) / sizeof(int);
    struct Object inputs[] = {
        { .nums = nums1, .len = len1 },
        { .nums = nums2, .len = len2 },
    };
    int i, len = sizeof(inputs) / sizeof(struct Object);

    for (i = 0; i < len; i++) {
        int *nums = inputs[i].nums;
        int size = inputs[i].len;

        struct TreeNode *root = make_tree(nums, 0, size);
        printf("\n Input: ");
        print_tree(root);
        printf("\n");
        bool balanced = is_balanced(root);
        printf(" Output: %s\n", balanced ? "true" : "false");

        free_tree(root);
    }

    return EXIT_SUCCESS;
}
