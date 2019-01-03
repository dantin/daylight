#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode *make_list(int *array, int len)
{
    struct ListNode dummy, *prev = NULL;
    int i;

    dummy.next = NULL;
    prev = &dummy;
    for (i = 0; i < len; i++) {
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
    struct ListNode *p = list;

    while (p != NULL) {
        if (p == list) {
            printf("%d", p->val);
        } else {
            printf(" -> %d", p->val);
        }
        p = p->next;
    }

    putchar('\n');
}

struct ListNode *merge_k_lists(struct ListNode **lists, int lists_size)
{
    if (lists_size == 0) {
        return NULL;
    }
    if (lists_size == 1) {
        return lists[0];
    }

    int i, idx;
    struct ListNode dummy, *p, *prev;

    dummy.next = NULL;
    prev = &dummy;
    idx = 0;
    while (idx != -1) {
        int min = INT_MAX;
        idx = -1;
        for (i = 0; i < lists_size; i++) {
            if (lists[i] != NULL && lists[i]->val < min) {
                min = lists[i]->val;
                idx = i;
            }
        }

        if (idx != -1) {
            p = malloc(sizeof(*p));
            p->val = min;
            p->next = NULL;
            prev->next = p;
            prev = p;
            lists[idx] = lists[idx]->next;
        }
    }

    return dummy.next;
}

int main(int argc, char **argv)
{
    int i, size = 3;
    int arr1[] = {1, 4, 5};
    int arr2[] = {1, 3, 4};
    int arr3[] = {2, 6};

    struct ListNode **lists = malloc(size * sizeof(struct ListNode *));
    lists[0] = make_list(arr1, sizeof(arr1)/sizeof(int));
    lists[1] = make_list(arr2, sizeof(arr2)/sizeof(int));
    lists[2] = make_list(arr3, sizeof(arr3)/sizeof(int));

    printf(" Input:\n [\n");
    for (i = 0; i < size; i++) {
        printf("  ");
        print_list(lists[i]);
    }
    printf(" ]\n");

    struct ListNode *sorted = merge_k_lists(lists, size);
    printf(" Output: \n ");
    print_list(sorted);

    return EXIT_SUCCESS;
}
