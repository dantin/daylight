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
    int i;
    struct ListNode dummy;
    struct ListNode *prev = &dummy;
    dummy.next = NULL;

    for (i = 0; i < size; i++) {
        struct ListNode *node = malloc(sizeof(*node));
        node->val = nums[i];
        node->next = NULL;
        prev->next = node;
        prev = node;
    }

    return dummy.next;
}

void print_list(struct ListNode *head)
{
    char *s = "";
    while (head != NULL) {
        printf("%s%d", s, head->val);
        s = "->";
        head = head->next;
    }
}

void free_list(struct ListNode *head)
{
    struct ListNode *tmp;
    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

void traverse(struct ListNode *dummy, struct ListNode *end)
{
    if (dummy == NULL || dummy->next == end) {
        return;
    }

    struct ListNode *pivot = dummy->next;
    struct ListNode *prev = pivot;
    struct ListNode *p = pivot->next;
    struct ListNode *first = NULL;

    while (p != end) {
        if (p->val >= pivot->val) {
            if (first == NULL && p->val > pivot->val) {
                first = prev;
            }
            prev = p;
            p = p->next;
        } else {
            prev->next = p->next;
            p->next = dummy->next;
            dummy->next = p;
            p = prev->next;
        }
    }

    traverse(dummy, pivot);
    traverse(first, end);
}

struct ListNode *sort_list(struct ListNode *head)
{
    struct ListNode dummy;
    dummy.next = head;
    traverse(&dummy, NULL);
    return dummy.next;
}

int main(int argc, char **argv)
{
    int nums1[] = { 4, 2, 1, 3 }, len1 = sizeof(nums1) / sizeof(int);
    int nums2[] = { -1, 5, 3, 4, 0 }, len2 = sizeof(nums2) / sizeof(int);
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
        head = sort_list(head);
        printf("\n Output: ");
        print_list(head);
        printf("\n");

        free_list(head);
    }
    
    return EXIT_SUCCESS;
}
