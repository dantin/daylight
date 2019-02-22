#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

struct Object {
    int *nums;
    int len;
};

struct ListNode *make_list(int *nums, int size)
{
    struct ListNode dummy, *prev = NULL;
    int i;

    dummy.next = NULL;
    prev = &dummy;

    for (i = 0; i < size; i++) {
        struct ListNode *node = malloc(sizeof(struct ListNode));
        node->next = NULL;
        node->val = nums[i];
        prev->next = node;
        prev = node;
    }

    return dummy.next;
}

void free_list(struct ListNode *head, struct ListNode *end)
{
    struct ListNode *prev = NULL, *p = head;

    while (p != end) {
        prev = p;
        p = p->next;
        free(prev);
        prev = NULL;
    }
}

void print_list(struct ListNode *list)
{
    struct ListNode *p = list;

    if (p == NULL) {
        return;
    }
    printf("%d", p->val);
    while (p->next != NULL) {
        p = p->next;
        printf(" -> %d", p->val);
    }
    printf("\n");
}

struct ListNode *delete_duplicates(struct ListNode *head)
{
    struct ListNode dummy;
    struct ListNode *p, *next, *prev;

    prev = &dummy;
    dummy.next = head;
    p = next = head;

    while (p != NULL) {
        while (next != NULL && next->val == p->val) {
            next = next->next;
        }
        if (p->next == next) {
            prev = p;
        } else {
            free_list(p, next);

            prev->next = next;
        }
        p = next;
    }

    return dummy.next;
}

int main(int argc, char **argv)
{
    int nums1[] = { 1, 2, 3, 3, 4, 4, 5 }, len1 = sizeof(nums1) / sizeof(int);
    int nums2[] = { 1, 1, 1, 2, 3 },       len2 = sizeof(nums2) / sizeof(int);
    struct Object inputs[] = {
        { .nums = nums1, .len = len1 },
        { .nums = nums2, .len = len2 },
    };
    int i, len = sizeof(inputs) / sizeof(struct Object);

    for (i = 0; i < len; i++) {
        int *nums = inputs[i].nums;
        int size = inputs[i].len;

        printf("\n Input: ");
        struct ListNode *list = make_list(nums, size);
        print_list(list);
        
        struct ListNode *processed = delete_duplicates(list);
        printf(" Output: ");
        print_list(processed);
        free_list(processed, NULL);
    }

    return EXIT_SUCCESS;
}
