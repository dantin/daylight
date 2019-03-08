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

void traverse(
    struct TreeNode *node,
    struct TreeNode **prev,
    struct TreeNode **p1,
    struct TreeNode **p2,
    int *wrong)
{
    if (node->left != NULL) {
        traverse(node->left, prev, p1, p2, wrong);
    }

    if (*prev != NULL && node->val < (*prev)->val) {
        (*wrong)++;
        if (*wrong == 1) {
            *p1 = *prev;
            *p2 = node;
        } else if (*wrong == 2) {
            *p2 = node;
            return;
        }
    }
    *prev = node;

    if (node->right != NULL) {
        traverse(node->right, prev, p1, p2, wrong);
    }
}

void recover_tree(struct TreeNode *root)
{
    if (root == NULL) {
        return;
    }

    struct TreeNode *prev = NULL;
    struct TreeNode *p1 = NULL;
    struct TreeNode *p2 = NULL;
    int wrong = 0;
    traverse(root, &prev, &p1, &p2, &wrong);
    int tmp = p1->val;
    p1->val = p2->val;
    p2->val = tmp;
}

int main(int argc, char **argv)
{
    int nums1[] = { 1, 3, INT_MIN, INT_MIN, 2 },             len1 = sizeof(nums1) / sizeof(int);
    int nums2[] = { 3, 1, 4, INT_MIN, INT_MIN, 2, INT_MIN }, len2 = sizeof(nums2) / sizeof(int);
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
        printf("\n");
        recover_tree(root);
        printf(" Output: ");
        print_tree(root);
        printf("\n");
        free_tree(root);
    }

    return EXIT_SUCCESS;
}
