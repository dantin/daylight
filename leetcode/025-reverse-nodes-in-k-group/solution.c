#include <stdio.h>
#include <stdlib.h>

struct object {
    int *array;
    int len;
    int k;
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
        node->val = array[i];
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
    while (head->next != NULL) {
        head = head->next;
        printf(" -> %d", head->val);
    }
    putchar('\n');
}

struct ListNode *reverse_k_group(struct ListNode *head, int k)
{
    struct ListNode dummy;
    struct ListNode *p = head, *prev = &dummy;
    int i, len = 0;

    dummy.next = head;
    for (p = head; p != NULL; p = p->next) {
        if (++len % k == 0) {
            struct ListNode *begin = prev->next;
            for (i = 1; i < k; i++) {
                struct ListNode *next = begin->next;
                begin->next = next->next;
                next->next = prev->next;
                prev->next = next;
            }
            p = begin;
            prev = p;
        }
    }
    return dummy.next;
}

int main(int argc, char **argv)
{
    int arr1[] = {1, 2, 3, 4, 5}, len1 = sizeof(arr1) / sizeof(int);
    int arr2[] = {1, 2, 3, 4, 5}, len2 = sizeof(arr2) / sizeof(int);

    struct object inputs[] = {
        {.array = arr1, .len = len1, .k = 2},
        {.array = arr2, .len = len2, .k = 3},
    };
    int i, len = sizeof(inputs) / sizeof(struct object);

    for (i = 0; i < len; i++) {
        struct ListNode *list = make_list(inputs[i].array, inputs[i].len);
        printf("\n Input: "); print_list(list);
        printf("     k: %d\n", inputs[i].k);
        struct ListNode *reversed = reverse_k_group(list, inputs[i].k);
        printf(" Output: "); print_list(reversed);
    }

    return EXIT_SUCCESS;
}
