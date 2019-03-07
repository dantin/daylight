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

bool dfs(struct TreeNode *node, long min, long max)
{
    if (node == NULL) return true;
    if (node->val < min || node->val > max) return false;
    if (node->left != NULL && node->val == LONG_MIN) return false;
    if (node->right != NULL && node->val == LONG_MAX) return false;

    return dfs(node->left, min, (long) node->val - 1) && dfs(node->right, (long) node->val + 1, max);
}

bool is_valid_bst(struct TreeNode *root)
{
    return dfs(root, LONG_MIN, LONG_MAX);
}

int main(int argc, char **argv)
{
    int nums1[] = { 2, 1, 3 }, len1 = sizeof(nums1) / sizeof(int);
    int nums2[] = { 5, 1, 4, INT_MIN, INT_MIN, 3, 6 }, len2 = sizeof(nums2) / sizeof(int);
    int nums3[] = { 2147483647 }, len3 = sizeof(nums3) / sizeof(int);
     struct Object inputs[] = {
        { .nums = nums1, .len = len1 },
        { .nums = nums2, .len = len2 },
        { .nums = nums3, .len = len3 },
    };
    int i, len = sizeof(inputs) / sizeof(struct Object);

    for (i = 0; i < len; i++) {
        int *nums = inputs[i].nums;
        int size = inputs[i].len;
        struct TreeNode *root = make_tree(nums, 0, size);
        printf("\n Input: ");
        print_tree(root);
        printf("\n");
        bool is_valid = is_valid_bst(root);
        printf(" Output: %s\n", is_valid ? "true" : "false");
        free_tree(root);
    }

    return EXIT_SUCCESS;
}
