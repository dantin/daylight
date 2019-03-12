#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

struct Object {
    int *nums_lhs;
    int len_lhs;
    int *nums_rhs;
    int len_rhs;
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

bool is_same_tree(struct TreeNode *p, struct TreeNode *q)
{
    if (p != NULL && q != NULL) {
        if (p->val != q->val) {
            return false;
        }
        if (!is_same_tree(p->left, q->left)) {
            return false;
        }
        if (!is_same_tree(p->right, q->right)) {
            return false;
        }
    } else {
        return p == q;
    }

    return true;
}

int main(int argc, char **argv)
{
    int nums1[] = { 1, 2, 3 }, len1 = sizeof(nums1) / sizeof(int);
    int nums2[] = { 1, 2, INT_MIN }, len2 = sizeof(nums2) / sizeof(int);
    int nums3[] = { 1, INT_MIN, 2 }, len3 = sizeof(nums3) / sizeof(int);
    int nums4[] = { 1, 2, 1 }, len4 = sizeof(nums4) / sizeof(int);
    int nums5[] = { 1, 1, 2 }, len5 = sizeof(nums5) / sizeof(int);
    struct Object inputs[] = {
        { .nums_lhs = nums1, .len_lhs = len1, .nums_rhs = nums1, .len_rhs = len1 },
        { .nums_lhs = nums2, .len_lhs = len2, .nums_rhs = nums3, .len_rhs = len3 },
        { .nums_lhs = nums4, .len_lhs = len4, .nums_rhs = nums5, .len_rhs = len5 },
    };
    int i, len = sizeof(inputs) / sizeof(struct Object);

    for (i = 0; i < len; i++) {
        int *nums_lhs = inputs[i].nums_lhs;
        int len_lhs = inputs[i].len_lhs;
        int *nums_rhs = inputs[i].nums_rhs;
        int len_rhs = inputs[i].len_rhs;

        struct TreeNode *lhs = make_tree(nums_lhs, 0, len_lhs);
        struct TreeNode *rhs = make_tree(nums_rhs, 0, len_rhs);
        printf("\n Input: ");
        print_tree(lhs);
        printf("\n        ");
        print_tree(rhs);

        bool same = is_same_tree(lhs, rhs);
        printf("\n Output: %s\n", same ? "true" : "false");

        free_tree(lhs);
        free_tree(rhs);
    }

    return EXIT_SUCCESS;
}
