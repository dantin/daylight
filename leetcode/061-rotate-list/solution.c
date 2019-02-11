#include <stdio.h>
#include <stdlib.h>

struct Object {
    int *nums;
    int len;
    int k;
};

struct ListNode {
    int val;
    struct ListNode *next;
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

void print_list(struct ListNode *list)
{
    struct ListNode *p = list;

    while (p != NULL) {
        if (p == list) {
            printf("%d", p->val);
        } else {
            printf(" -> %d", p->val);
        }
        p = p->next;
    }
}

struct ListNode *rotate_right(struct ListNode *head, int k)
{
    if (head == NULL || k <= 0) {
        return head;
    }

    struct ListNode dummy;
    struct ListNode *prev = &dummy, *last = &dummy, *p = head;
    dummy.next = head;
    int count = k;
    while (k > 0) {
        if (p == NULL) {
            int length = count - k;
            prev = &dummy;
            p = head;
            k = count % length;
            if (k == 0) break;
        }
        prev = p;
        p = p->next;
        k--;
    }

    while (p != NULL) {
        last = last->next;
        prev = p;
        p = p->next;
    }

    if (last != &dummy) {
        prev->next = head;
        dummy.next = last->next;
        last->next = NULL;
    }

    return dummy.next;
}

int main(int argc, char **argv)
{
    int nums1[] = {1, 2, 3, 4, 5}, len1 = sizeof(nums1) / sizeof(int);
    int nums2[] = {0, 1, 2},       len2 = sizeof(nums2) / sizeof(int);
    struct Object inputs[] = {
        {.nums = nums1, .len = len1, .k = 2},
        {.nums = nums2, .len = len2, .k = 4},
    };
    int i, len = sizeof(inputs) / sizeof(struct Object);

    for (i = 0; i < len; i++) {
        int *nums = inputs[i].nums;
        int size = inputs[i].len;
        int k = inputs[i].k;
        struct ListNode *list = make_list(nums, size);
        printf("\n Input: ");
        print_list(list);
        printf(", k = %d\n", k);
        list = rotate_right(list, k);
        printf(" Output: ");
        print_list(list);
        putchar('\n');
    }

    return EXIT_SUCCESS;
}
