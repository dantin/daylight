#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Object {
    int *nums;
    size_t len;
};

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct TreeNode *make_tree_node(int *nums, size_t pos, size_t size)
{
    if (pos >= size || nums[pos] == INT_MIN) {
        return NULL;
    }

    size_t left = 2 * pos + 1;
    size_t right = 2 * pos + 2;

    struct TreeNode *node = malloc(sizeof(*node));
    node->val = nums[pos];
    node->left = make_tree_node(nums, left, size);
    node->right = make_tree_node(nums, right, size);

    return node;
}

struct TreeNode *make_tree(int *nums, size_t size)
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

int dfs(struct TreeNode *node, int sum)
{
    int total = 0;
    sum = sum * 10 + node->val;

    if (node->left == NULL && node->right == NULL) {
        return sum;
    } else {
        if (node->left != NULL) {
            total += dfs(node->left, sum);
        }
        if (node->right != NULL) {
            total += dfs(node->right, sum);
        }
        return total;
    }
}

int sum_numbers(struct TreeNode *root)
{
    if (root == NULL) {
        return 0;
    }

    return dfs(root, 0);
}

int main(int argc, char **argv)
{
    int nums1[] = { 1, 2, 3 };
    size_t len1 = sizeof(nums1) / sizeof(int);
    int nums2[] = { 4, 9, 0, 5, 1 };
    size_t len2 = sizeof(nums2) / sizeof(int);
    struct Object inputs[] = {
        { .nums = nums1, .len = len1 },
        { .nums = nums2, .len = len2 },
    };
    size_t i, len = sizeof(inputs) / sizeof(struct Object);

    for (i = 0; i < len; i++) {
        int *nums = inputs[i].nums;
        int size = inputs[i].len;

        struct TreeNode *root = make_tree(nums, size);
        printf("\n Input: ");
        print_tree(root);

        int sum = sum_numbers(root);
        printf("\n Output: %d\n", sum);

        free_tree(root);
    }

    return EXIT_SUCCESS;
}
