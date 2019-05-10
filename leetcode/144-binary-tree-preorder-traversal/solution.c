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

void print_nums(int *nums, int size)
{
    char *s = "";
    int i;
    printf("[");
    for (i = 0; i < size; i++) {
        printf("%s%d", s, nums[i]);
        s = ", ";
    }
    printf("]");
}

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

int *preorder_traversal(struct TreeNode *root, int *return_size)
{
    if (root == NULL) {
        *return_size = 0;
        return NULL;
    }

    int capacity = 10000, count = 0;
    int *results = malloc(capacity * sizeof(int));
    struct TreeNode **stack = malloc(capacity / 16 * sizeof(*stack));
    struct TreeNode **top = stack;
    struct TreeNode *node = root;

    while (node != NULL || top != stack) {
        if (node == NULL) {
            node = *--top;
        }

        results[count++] = node->val;

        if (node->right != NULL) {
            *top++ = node->right;
        }

        node = node->left;
    }

    free(stack);

    *return_size = count;
    return results;
}

int main(int argc, char **argv)
{
    int nums1[] = { 1, INT_MIN, 2, INT_MIN, INT_MIN, 3 }, len1 = sizeof(nums1) / sizeof(int);
    struct Object inputs[] = {
        { .nums = nums1, .len = len1 },
    };
    int i, len = sizeof(inputs) / sizeof(struct Object);
    int return_size;

    for (i = 0; i < len; i++) {
        int *nums = inputs[i].nums;
        int size = inputs[i].len;

        struct TreeNode *root = make_tree(nums, size);
        printf("\n Input: ");
        print_tree(root);

        int *path = preorder_traversal(root, &return_size);
        printf("\n Output:");
        print_nums(path, return_size);
        printf("\n");
        
        free(path);
        free_tree(root);
    }
    return EXIT_SUCCESS;
}
