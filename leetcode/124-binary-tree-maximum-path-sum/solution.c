#include <stdio.h>
#include <stdlib.h>
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

int partition(struct TreeNode *node, int *max)
{
    if (node == NULL) {
        return 0;
    }
    int left = partition(node->left, max);
    int right = partition(node->right, max);

    int current = node->val;

    if (left > 0) {
        current += left;
    }
    if (right > 0) {
        current += right;
    }

    *max = *max > current ? *max : current;
    int end_by_root = (node->val + left) > (node->val + right) ? node->val + left : node->val + right;
    return node->val > end_by_root ? node->val : end_by_root;
}

int max_path_sum(struct TreeNode *root)
{
    if (root == NULL) {
        return 0;
    }

    int max = INT_MIN;
    partition(root, &max);
    return max;
}

int main(int argc, char **argv)
{
    int nums1[] = { 1, 2, 3 }, len1 = sizeof(nums1) / sizeof(int);
    int nums2[] = { -10, 9, 20, INT_MIN, INT_MIN, 15, 7 }, len2 = sizeof(nums2) / sizeof(int);
    int nums3[] = { 2, -1 }, len3 = sizeof(nums3) / sizeof(int);
    struct Object inputs[] = {
        { .nums = nums1, .len = len1 },
        { .nums = nums2, .len = len2 },
        { .nums = nums3, .len = len3 },
    };
    int i, len = sizeof(inputs) / sizeof(struct Object);

    for (i = 0; i < len; i++) {
        int *nums = inputs[i].nums;
        int size = inputs[i].len;

        struct TreeNode *root = make_tree(nums, size);
        printf("\n Input: ");
        print_tree(root);
        printf("\n");

        int path_sum = max_path_sum(root);
        printf(" Output: %d\n", path_sum);

        free_tree(root);
    }

    return EXIT_SUCCESS;
}
