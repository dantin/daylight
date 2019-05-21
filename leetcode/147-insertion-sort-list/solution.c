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

struct ListNode *insertion_sort_list(struct ListNode *head)
{
    if (head == NULL) {
        return NULL;
    }

    if (head->next == NULL) {
        return head;
    }

    struct ListNode dummy;
    struct ListNode *p0, *p, *p1;
    dummy.next = head;

    for (p0 = head, p = head->next; p != NULL; p0 = p, p = p->next) {
        if (p->val < p0->val) {
            p0->next = p->next;
            for (p1 = &dummy; p1 != p0; p1 = p1->next) {
                if (p1->next->val >= p->val) {
                    p->next = p1->next;
                    p1->next = p;
                    break;
                }
            }
            p = p0;
        }
    }

    return dummy.next;
}

int main(int argc, char **argv)
{
    int nums1[] = { 4, 2, 1, 3 }, len1 = sizeof(nums1) / sizeof(int);
    struct Object inputs[] = {
        { .nums = nums1, .len = len1 },
    };
    int i, len = sizeof(inputs) / sizeof(struct Object);

    for (i = 0; i < len; i++) {
        int *nums = inputs[i].nums;
        int size = inputs[i].len;

        struct ListNode *head = make_list(nums, size);

        printf("\n Input: ");
        print_list(head);
        head = insertion_sort_list(head);
        printf("\n Output: ");
        print_list(head);
        printf("\n");

        free_list(head);
    }

    return EXIT_SUCCESS;
}
