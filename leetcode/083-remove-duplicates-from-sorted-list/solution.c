#include <stdio.h>
#include <stdlib.h>

struct Object {
    int *nums;
    int len;
};

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode *make_list(int *nums, int size)
{
    struct ListNode dummy, *prev;
    int i;

    prev = &dummy;
    dummy.next = NULL;
    for (i = 0; i < size; i++) {
        struct ListNode *node = malloc(sizeof(struct ListNode));
        node->val = nums[i];
        node->next = NULL;
        prev->next = node;
        prev = node;
    }

    return dummy.next;
}

void free_list(struct ListNode *head, struct ListNode *end)
{
    struct ListNode *tmp;

    while (head != end) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

void print_list(struct ListNode *head)
{
    if (head == NULL) {
        return;
    }
    printf("%d", head->val);
    head = head->next;

    while (head != NULL) {
        printf("->%d", head->val);
        head = head->next;
    }
    printf("\n");
}

struct ListNode *delete_dumplicates(struct ListNode *head)
{
    struct ListNode *p, *next;

    p = next = head;
    while (p != NULL) {
        while (next != NULL && next->val == p->val) {
            next = next->next;
        }
        if (p->next != next) {
            free_list(p->next, next);
        }
        p->next = next;
        p = next;
    }
    return head;
}

int main(int argc, char **argv)
{
    int nums1[] = { 1, 1, 2 },       len1 = sizeof(nums1) / sizeof(int);
    int nums2[] = { 1, 1, 2, 3, 3 }, len2 = sizeof(nums2) / sizeof(int);
    struct Object inputs[] = {
        { .nums = nums1, .len = len1 },
        { .nums = nums2, .len = len2 },
    };
    int i, len = sizeof(inputs) / sizeof(struct Object);

    for (i = 0; i < len; i++) {
        int *nums = inputs[i].nums;
        int size = inputs[i].len;
        struct ListNode *list = make_list(nums, size);
        printf("\n Input: ");
        print_list(list);

        struct ListNode *removed = delete_dumplicates(list);
        printf(" Output: ");
        print_list(removed);

        free_list(removed, NULL);
    }
    
    return EXIT_SUCCESS;
}
