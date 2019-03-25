#include <stdio.h>
#include <stdlib.h>

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
    if (size < 1) {
        printf("[]\n");
        return;
    }
    int i;
    printf("[%d", nums[0]);
    for (i = 1; i < size; i++) {
        printf(", %d", nums[i]);
    }
    printf("]\n");
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

struct TreeNode *partition(int *nums, int low, int high)
{
    int mid = low + (high - low) / 2;
    struct TreeNode *node = malloc(sizeof(*node));
    node->val = nums[mid];
    node->left = mid > low ? partition(nums, low, mid - 1) : NULL;
    node->right = mid < high ? partition(nums, mid + 1, high) : NULL;
    return node;
}

struct TreeNode *sorted_array_to_bst(int *nums, int nums_size)
{
    if (nums_size == 0) {
        return NULL;
    }
    return partition(nums, 0, nums_size - 1);
}

int main(int argc, char **argv)
{
    int nums1[] = {-10, -3, 0, 5, 9}, len1 = sizeof(nums1) / sizeof(int);
    struct Object inputs[] = {
        { .nums = nums1, .len = len1 },
    };
    int i, len = sizeof(inputs) / sizeof(struct Object);

    for (i = 0; i < len; i++) {
        int *nums = inputs[i].nums;
        int size = inputs[i].len;
        printf("\n Input: ");
        print_nums(nums, size);
        struct TreeNode *root = sorted_array_to_bst(nums, size);
        printf("\n Output: ");
        print_tree(root);
        printf("\n");
        free_tree(root);
    }

    return EXIT_SUCCESS;
}
