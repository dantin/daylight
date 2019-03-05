#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

char *itostr(char *str, int value)
{
    if (value == INT_MIN) {
        strcpy(str, "null");
    } else {
        sprintf(str, "%d", value);
    }
    return str;
}

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

void print_nums(int *nums, int size)
{
    char buf[255];

    if (size < 1) {
        printf("[]");
        return;
    }
    int i;
    printf("[%s", itostr(buf, nums[0]));
    for (i = 1; i < size; i++) {
        printf(", %s", itostr(buf, nums[i]));
    }
    printf("]");
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

void traverse(struct TreeNode *node, int *result, int *count)
{
    if (node->left != NULL) {
        traverse(node->left, result, count);
    }

    result[*count] = node->val;
    (*count)++;

    if (node->right != NULL) {
        traverse(node->right, result, count);
    }
}

int *inorder_traversal(struct TreeNode *root, int *return_size)
{
    if (root == NULL) {
        *return_size = 0;
        return NULL;
    }
    int count = 0, capacity = 5000;
    int *result = malloc(capacity * sizeof(int));
    traverse(root, result, &count);
    *return_size = count;
    return result;
}

int main(int argc, char **argv)
{
    int nums1[] = { 1, INT_MIN, 2, INT_MIN, INT_MIN, 3 }, len1 = sizeof(nums1) / sizeof(int);
    int nums2[] = { 1, 2 }, len2 = sizeof(nums2) / sizeof(int);
    struct Object inputs[] = {
        { .nums = nums1, .len = len1 },
        { .nums = nums2, .len = len2 },
    };
    int i, len = sizeof(inputs) / sizeof(struct Object);
    int return_size;

    for (i = 0; i < len; i++) {
        int *nums = inputs[i].nums;
        int size = inputs[i].len;

        printf("\n Input: ");
        print_nums(nums, size);
        printf("\n");
        struct TreeNode *root = make_tree(nums, 0, size);
        int *path = inorder_traversal(root, &return_size);
        printf(" Output: ");
        print_nums(path, return_size);
        printf("\n");

        free(path);
        free_tree(root);
    }

    return EXIT_SUCCESS;
}
