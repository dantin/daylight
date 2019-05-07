#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Object {
    int *nums;
    int len;
    int pos;
};

struct ListNode {
    int val;
    struct ListNode *next;
};

void print_nums(int *nums, int size)
{
    char *s = "";
    int i;
    printf("[");
    for (i = 0; i < size; i++) {
        printf("%s%d", s, nums[i]);
        s = ", ";
    }
    printf("]");
}

struct ListNode *make_list(int *nums, int size, int pos, struct ListNode **tail)
{
    struct ListNode *prev;
    struct ListNode dummy;
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

    if (pos >= 0) {
        struct ListNode *head = dummy.next;
        for (i = 0; i < pos; i++) {
            head = head->next;
        }
        prev->next = head;
    }

    *tail = prev;
    return dummy.next;
}

void free_list(struct ListNode *head, struct ListNode *tail)
{
    struct ListNode *tmp;

    while (head != tail) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
    free(tail);
}

bool has_cycle(struct ListNode *head)
{
    if (head == NULL || head->next == NULL) {
        return false;
    }

    bool first = true;
    struct ListNode *fast, *slow;
    for (fast = head, slow = head; fast != NULL && fast->next != NULL; slow = slow->next, fast = fast->next->next) {
        if (slow == fast && !first) {
            return true;
        }
        first = false;
    }

    return false;
}

int main(int argc, char **argv)
{
    int nums1[] = { 3, 2, 0, -4 }, len1 = sizeof(nums1) / sizeof(int);
    int pos1 = 1;
    int nums2[] = { 1, 2 }, len2 = sizeof(nums2) / sizeof(int);
    int pos2 = 0;
    int nums3[] = { 1 }, len3 = sizeof(nums3) / sizeof(int);
    int pos3 = -1;
    struct Object inputs[] = {
        { .nums = nums1, .len = len1, .pos = pos1 },
        { .nums = nums2, .len = len2, .pos = pos2 },
        { .nums = nums3, .len = len3, .pos = pos3 },
    };
    int i, len = sizeof(inputs) / sizeof(struct Object);
    struct ListNode *tail = NULL;

    for (i = 0; i < len; i++) {
        int *nums = inputs[i].nums;
        int size = inputs[i].len;
        int pos = inputs[i].pos;
        printf("\n Input: head = ");
        print_nums(nums, size);
        printf(", pos = %d", pos);

        struct ListNode *head = make_list(nums, size, pos, &tail);
        bool cycled = has_cycle(head);
        printf("\n Output: %s\n", cycled ? "true": "false");
        free_list(head, tail);
    }

    return EXIT_SUCCESS;
}
