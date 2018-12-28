#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

void print_list(struct ListNode *list) {
    struct ListNode *p;

    if (list != NULL) {
        for (p = list; p != NULL; p = p->next) {
            if (p != list) {
                printf(" -> ");
            }
            printf("%d", p->val);
        }
        printf("\n");
    }
}

struct ListNode *remove_nth_from_end(struct ListNode *head, int n)
{
    if (n < 1) return NULL;

    struct ListNode *p, *prev, dummy;
    dummy.next = head;
    p = prev = &dummy;

    // move `p` n-1 time from head.
    while (n-- > 0) {
        p = p->next;
    }

    // `prev` is the previous node of  nth node from end.
    while (p->next != NULL) {
        p = p->next;
        prev = prev->next;
    }

    // `tmp` is the nth node from end.
    struct ListNode *tmp = prev->next;
    prev->next = tmp->next;
    if (tmp == head) {
        head = tmp->next;
    }
    free(tmp);

    return head;
}

int main(int argc, char **argv)
{
    int nums[] = {1, 2, 3, 4, 5};
    int n = 2;
    int i, len = sizeof(nums) / sizeof(int);
    struct ListNode *list, *p, *prev = NULL;

    // prepare data
    for (i = 0; i < len; i++) {
        p = malloc(sizeof(*p));
        p->val = nums[i];
        p->next = NULL;

        if (i == 0) {
            list = p;
        }

        if (prev != NULL) {
            prev->next = p;
        }
        prev = p;
    }

    printf(" Given linked list:  "); print_list(list);
    printf(" n = %d\n", n);

    list = remove_nth_from_end(list, n);
    printf(" Result linked list: "); print_list(list);

    return 0;
}
