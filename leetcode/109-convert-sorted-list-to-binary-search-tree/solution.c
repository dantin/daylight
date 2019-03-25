#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 100000

struct Object {
    int *nums;
    int len;
};

struct ListNode {
    int val;
    struct ListNode *next;
};

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct ListNode *make_list(int *nums, int size)
{
    int i;
    struct ListNode *prev, dummy;

    dummy.next = NULL;
    prev = &dummy;
    for (i = 0; i < size; i++) {
        struct ListNode *node = malloc(sizeof(*node));
        node->val = nums[i];
        node->next = NULL;
        prev->next = node;
        prev = node;
    }
    return dummy.next;
}

void print_list(struct ListNode *list)
{
    if (list == NULL) {
        printf("[]\n");
        return;
    }
    printf("[%d", list->val);
    list = list->next;
    while (list != NULL) {
        printf(", %d", list->val);
        list = list->next;
    }
    printf("]\n");
}

void free_list(struct ListNode *list)
{
    struct ListNode *p;

    while (list != NULL) {
        p = list;
        list = list->next;
        free(p);
    }
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

struct TreeNode *traverse(int *nums, int low, int high)
{
    int mid = low + (high - low) / 2;
    struct TreeNode *node = malloc(sizeof(*node));
    node->val = nums[mid];
    node->left = mid > low ? traverse(nums, low, mid - 1) : NULL;
    node->right = mid < high ? traverse(nums, mid + 1, high) : NULL;
    return node;
}

struct TreeNode *sorted_list_to_bst(struct ListNode *head)
{
    int i, nums[BUFFER_SIZE];
    for (i = 0; head != NULL; head = head->next, i++) {
        nums[i] = head->val;
    }

    if (i == 0) {
        return NULL;
    }
    return traverse(nums, 0, i - 1);
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

        struct ListNode *list = make_list(nums, size);
        printf("\n Input: ");
        print_list(list);
        struct TreeNode *root = sorted_list_to_bst(list);
        printf("\n Output: ");
        print_tree(root);
        printf("\n");

        free_tree(root);
        free_list(list);
    }

    return EXIT_SUCCESS;
}
