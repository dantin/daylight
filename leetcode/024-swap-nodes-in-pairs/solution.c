#include <stdio.h>
#include <stdlib.h>

struct object {
    int *array;
    int len;
};

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode *make_list(int *array, int size)
{
    struct ListNode dummy, *prev;
    int i;

    dummy.next = NULL;
    prev = &dummy;
    for (i = 0; i < size; i++) {
        struct ListNode *node = malloc(sizeof(struct ListNode));
        node->next = NULL;
        node->val = array[i];
        prev->next = node;
        prev = node;
    }
    return dummy.next;
}

void print_list(struct ListNode *list)
{
    if (list == NULL) {
        return;
    }

    printf("%d", list->val);
    while (list->next != NULL) {
        list = list->next;
        printf(" -> %d", list->val);
    }
    putchar('\n');
}

struct ListNode *swap_pairs(struct ListNode *head)
{
    if (head == NULL) {
        return NULL;
    }

    struct ListNode dummy;
    dummy.next = head;
    struct ListNode *prev = &dummy, *p = head, *next = p->next;
    while (p != NULL && next != NULL) {
        prev->next = next;
        p->next = next->next;
        next->next = p;
        prev = p;
        p = p->next;
        if (p != NULL) {
            next = p->next;
        }
    }
    return dummy.next;
}

int main(int argc, char **argv)
{
    int arr1[] = {1, 2, 3, 4};
    int len1 = sizeof(arr1) / sizeof(int);
    int arr2[] = {1, 2, 3, 4, 5};
    int len2 = sizeof(arr2) / sizeof(int);

    struct object inputs[] = {
        {.array = arr1, .len = len1},
        {.array = arr2, .len = len2},
    };
    int i, len = sizeof(inputs) / sizeof(struct object);

    for (i = 0; i < len; i++) {
        struct ListNode *list = make_list(inputs[i].array, inputs[i].len);
        printf("\n Input: "); print_list(list);
        struct ListNode *swapped = swap_pairs(list);
        printf(" Output: "); print_list(swapped);
    }

    return EXIT_SUCCESS;
}
