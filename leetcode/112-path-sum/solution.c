#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

struct Object {
    int *nums;
    int len;
    int target;
};

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct TreeNode *make_tree_node(int *nums, int pos, int size) {
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
    return make_tree_node(nums, 0 , size);
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

bool has_path_sum(struct TreeNode *root, int sum)
{
    if (root == NULL) {
        return false;
    } else if (root->left == NULL && root->right == NULL && root->val == sum) {
        return true;
    } else {
        return has_path_sum(root->left, sum - root->val) || has_path_sum(root->right, sum - root->val);
    }
}

int main(int argc, char **argv)
{
    int nums1[] = { 5, 4, 8, 11, INT_MIN, 13, 4, 7, 2, INT_MIN, INT_MIN, INT_MIN, 1 }, len1 = sizeof(nums1) / sizeof(int), target1 = 22;
    struct Object inputs[] = {
        { .nums = nums1, .len = len1, .target = target1 },
    };
    int i, len = sizeof(inputs) / sizeof(struct Object);

    for (i = 0; i < len; i++) {
        int *nums = inputs[i].nums;
        int size = inputs[i].len;
        int target = inputs[i].target;

        struct TreeNode *root = make_tree(nums, size);
        printf("\n Input: ");
        print_tree(root);
        printf("\n");

        bool exists = has_path_sum(root, target);
        printf(" Output: %s\n", exists ? "true" : "false");

        free_tree(root);
    }
    return EXIT_SUCCESS;
}
