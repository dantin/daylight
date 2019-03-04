#include <stdio.h>
#include <stdlib.h>

struct Object {
    int *nums;
    int len;
    int m;
    int n;
};

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode *make_list(int *nums, int size)
{
    if (size < 1) {
        return NULL;
    }

    struct ListNode dummy, *prev = &dummy;
    int i;

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

void print_list(struct ListNode *head)
{
    if (head != NULL) {
        printf("%d", head->val);
        head = head->next;
    }
    while (head != NULL) {
        printf("->%d", head->val);
        head = head->next;
    }
    printf("->NULL");
}

void free_list(struct ListNode *head)
{
    struct ListNode *tmp;

    while(head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

struct ListNode *reverse_between(struct ListNode *head, int m, int n)
{
    int len = n - m + 1;
    if (len == 1) {
        return head;
    }

    struct ListNode dummy;
    struct ListNode *p = head;
    struct ListNode *prev = &dummy;
    prev->next = p;
    while (--m > 0) {
        prev = p;
        p = p->next;
    }

    struct ListNode *q = p->next;
    while (--len > 0) {
        p->next = q->next;
        q->next = prev->next;
        prev->next = q;
        q = p->next;
    }

    return dummy.next;
}

int main(int argc, char **argv)
{
    int nums1[] = { 1, 2, 3, 4, 5 }, len1 = sizeof(nums1) / sizeof(int), m1 = 2, n1 = 4;
    struct Object inputs[] = {
        { .nums = nums1, .len = len1, .m = m1, .n = n1 },
    };
    int i, len = sizeof(inputs) / sizeof(struct Object);

    for (i = 0; i < len; i++) {
        int *nums = inputs[i].nums;
        int size = inputs[i].len;
        int m = inputs[i].m;
        int n = inputs[i].n;

        struct ListNode *head = make_list(nums, size);
        printf("\n Input: ");
        print_list(head);
        printf(", m = %d, n = %d\n", m, n);

        head = reverse_between(head, m, n);
        printf(" Output: ");
        print_list(head);
        printf("\n");

        free_list(head);
    }

    return EXIT_SUCCESS;
}
