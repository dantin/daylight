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

    struct TreeNode *node = malloc(sizeof(struct TreeNode));
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

bool traverse(struct TreeNode *lhs, struct TreeNode *rhs)
{
    if (lhs == NULL && rhs == NULL) {
        return true;
    }
    if (lhs == NULL || rhs == NULL) {
        return false;
    }
    if (lhs->val != rhs ->val) {
        return false;
    }

    return traverse(lhs->left, rhs->right) && traverse(lhs->right, rhs->left);
}

bool is_symmetric_tree(struct TreeNode *root) {
    if (root == NULL) {
        return true;
    }

    return traverse(root->left, root->right);
}

int main(int argc, char **argv)
{
    int nums1[] = { 1, 2, 2, 3, 4, 4, 3 }, len1 = sizeof(nums1) / sizeof(int);
    int nums2[] = { 1, 2, 2, INT_MIN, 3, INT_MIN, 3 }, len2 = sizeof(nums2) / sizeof(int);
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
        bool result = is_symmetric_tree(root);
        printf("\n Output: %s\n", result ? "true" : "false");
        free_tree(root);
    }

    return EXIT_SUCCESS;
}
