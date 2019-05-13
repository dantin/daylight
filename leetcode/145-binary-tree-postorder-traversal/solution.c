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

struct node_backlog {
    struct TreeNode *parent;
    struct TreeNode *right;
};

int counting(struct TreeNode *node)
{
    if (node == NULL) {
        return 0;
    }
    return 1 + counting(node->left) + counting(node->right);
}

int *postorder_traversal(struct TreeNode *root, int *return_size)
{
    if (root == NULL) {
        *return_size = 0;
        return NULL;
    }

    *return_size = counting(root);
    
    int count = 0;
    int *results = malloc(*return_size * sizeof(int));
    struct node_backlog *stack = malloc(*return_size * sizeof(*stack));
    struct node_backlog *top = stack;
    struct TreeNode *node = root;

    while (node != NULL || top != stack) {
        if (node == NULL) {
            if ((top - 1)->right != NULL) {
                node = (top - 1)->right;
                (top - 1)->right = NULL;
            } else {
                node = (--top)->parent;
                results[count++] = node->val;
                node = NULL;
                continue;
            }
        }
        top->parent = node;
        top->right = node->right;
        top++;
        node = node->left;
    }
    free(stack);

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

        int *path = postorder_traversal(root, &return_size);
        printf("\n Output: ");
        print_nums(path, return_size);
        printf("\n");

        free(path);
        free_tree(root);
    }

    return EXIT_SUCCESS;
}
