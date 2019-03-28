#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

void print_nums(int *nums, int size)
{
    if (size < 1) {
        printf("[]");
        return;
    }
    int i;
    printf("[%d", nums[0]);
    for (i = 1; i < size; i++) {
        printf(", %d", nums[i]);
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

void dfs(struct TreeNode *node, int sum, int *stack, int len, int **results, int *sizes, int *count)
{
    if (node == NULL) {
        return;
    }

    sum -= node->val;
    if (node->left == NULL && node->right == NULL && sum == 0) {
        results[*count] = malloc((len + 1) * sizeof(int));
        memcpy(results[*count], stack, len * sizeof(int));
        results[*count][len] = node->val;
        sizes[*count] = len + 1;
        (*count)++;
        return;
    }

    stack[len] = node->val;
    dfs(node->left, sum, stack, len + 1, results, sizes, count);
    dfs(node->right, sum, stack, len + 1, results, sizes, count);
}

int **path_sum(struct TreeNode *root, int sum, int **column_sizes, int *return_size)
{
    if (root == NULL) {
        *return_size = 0;
        return NULL;
    }

    int level = 5000, capacity = 1000;
    int *stack = malloc(level * sizeof(int));
    int **results = malloc(capacity * sizeof(int *));
    *column_sizes = malloc(capacity * sizeof(int));

    dfs(root, sum, stack, 0, results, *column_sizes, return_size);

    free(stack);

    return results;
}

int main(int argc, char **argv)
{
	int nums1[] = { 5, 4, 8, 11, INT_MIN, 13, 4, 7, 2, INT_MIN, INT_MIN, INT_MIN, INT_MIN, 5, 1 }, len1 = sizeof(nums1) / sizeof(int), target1 = 22;
    struct Object inputs[] = {
        { .nums = nums1, .len = len1, .target = target1 },
    };
    int i, len = sizeof(inputs) / sizeof(struct Object);
    int indent = 2, j = 0, return_size, *column_sizes;

    for (i = 0; i < len; i++) {
        int *nums = inputs[i].nums;
        int size = inputs[i].len;
        int target = inputs[i].target;

        struct TreeNode *root = make_tree(nums, size);
        printf("\n Input: ");
        print_tree(root);
        printf(", target = %d\n", target);

        int **paths = path_sum(root, target, &column_sizes, &return_size);

        printf(" Output:\n");
        j = 0;
        if (return_size < 1) {
            printf("[]\n");
            continue;
        }
        printf("[\n");
        printf("%*s", indent, "");
        print_nums(paths[j], column_sizes[j]);
        for (j = 1; j < return_size; j++) {
            printf(",\n%*s", indent, "");
            print_nums(paths[j], column_sizes[j]);
        }
        printf("\n]\n");

        for (j = 0; j < return_size; j++) {
            free(paths[j]);
        }
        free(paths);
        free(column_sizes);
        free_tree(root);
    }

    return EXIT_SUCCESS;
}
