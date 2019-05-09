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
    dummy.next = NULL;
    prev = &dummy;

    int i;
    for (i = 0; i < size; i++) {
        struct ListNode *node = malloc(sizeof(*node));
        node->val = nums[i];
        node->next = NULL;
        prev->next = node;
        prev = node;
    }

    return dummy.next;
}

void print_list(struct ListNode *node)
{
    char *s = "";
    for (; node != NULL; node = node->next) {
        printf("%s%d", s, node->val);
        s = "->";
    }
}

void free_list(struct ListNode *node)
{
    struct ListNode *tmp;

    while (node != NULL) {
        tmp = node;
        node = node->next;
        free(tmp);
    }
}

void reverse(struct ListNode *dummy)
{
    struct ListNode *prev = dummy->next;
    if (prev != NULL) {
        struct ListNode *p = prev->next;
        while (p != NULL) {
            prev->next = p->next;
            p->next = dummy->next;
            dummy->next = p;
            p = prev->next;
        }
    }
}

void reorder_list(struct ListNode *head)
{
    if (head == NULL) {
        return;
    }

    int count = 0;
    struct ListNode *p = head;
    struct ListNode *q = p;

    // locate half length.
    for (; p != NULL; p = p->next) {
        if ((++count & 0x1) == 0) {
            q = q->next;
        }
    }

    // reverse latter half list.
    reverse(q);

    struct ListNode *r;
    for (p = head, r = q->next; r != NULL; p = r->next, r = q->next) {
        q->next = r->next;
        r->next = p->next;
        p->next = r;
    }
}

int main(int argc, char **argv)
{
    int nums1[] = { 1, 2, 3, 4 }, len1 = sizeof(nums1) / sizeof(int);
    int nums2[] = { 1, 2, 3, 4, 5 }, len2 = sizeof(nums2) / sizeof(int);
    struct Object inputs[] = {
        { .nums = nums1, .len = len1 },
        { .nums = nums2, .len = len2 },
    };
    int i, len = sizeof(inputs) / sizeof(struct Object);

    for (i = 0; i < len; i++) {
        int *nums = inputs[i].nums;
        int size = inputs[i].len;

        struct ListNode *head = make_list(nums, size);
        printf("\n Input: ");
        print_list(head);

        reorder_list(head);

        printf("\n Output: ");
        print_list(head);
        printf("\n");

        free_list(head);
    }

    return EXIT_SUCCESS;
}
