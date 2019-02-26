#include <stdio.h>
#include <stdlib.h>

struct Object {
    int *nums;
    int len;
    int x;
};

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode *make_list(int *nums, int size)
{
    struct ListNode dummy;
    struct ListNode *prev = &dummy;
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
    if (head == NULL) {
        return;
    }

    printf("%d", head->val);
    head = head->next;
    while (head != NULL) {
        printf(" -> %d", head->val);
        head = head->next;
    }
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

struct ListNode *partition(struct ListNode *head, int x)
{
    struct ListNode dummy;
    struct ListNode *p = NULL, *start = &dummy, *pivot;

    dummy.next = head;
    // start and pivot is next to the other, and step forward list,
    // it stop until the first one make `pivot->val >= x`.
    for (pivot = head; pivot != NULL; pivot = pivot->next) {
        if (pivot->val >= x) {
            break;
        }
        start = pivot;
    }

    // prev and p is next to the other; and step forward list,
    // adjust list when `p->val < x`.
    struct ListNode *prev;
    for (p = pivot; p != NULL; p = p->next) {
        if (p->val < x) {
            prev->next = p->next;
            p->next = start->next;
            start->next = p;
            start = p;
            p = prev;
        }
        prev = p;
    }
    return dummy.next;
}

int main(int argc, char **argv)
{
    int nums1[] = { 1, 4, 3, 2, 5, 2 }, len1 = sizeof(nums1) / sizeof(int), x1 = 3;
    struct Object inputs[] = {
        { .nums = nums1, .len = len1, .x = x1 },
    };
    int i, len = sizeof(inputs) / sizeof(struct Object);

    for (i = 0; i < len; i++) {
        int *nums = inputs[i].nums;
        int size = inputs[i].len;
        int x = inputs[i].x;

        struct ListNode *head = make_list(nums, size);
        printf("\n Input: head = ");
        print_list(head);
        printf(", x = %d\n", x);

        head = partition(head, x);
        printf(" Output: ");
        print_list(head);
        printf("\n");

        free_list(head, NULL);
    }

    return EXIT_SUCCESS;
}
