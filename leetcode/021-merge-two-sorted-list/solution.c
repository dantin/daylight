#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

void print_list(struct ListNode *list)
{
    int head = 1;
    while (list != NULL) {
        if (head == 1) {
            head = 0;
            printf("%d", list->val);
        } else {
            printf(" -> %d", list->val);
        }
        list = list->next;
    }
    printf("\n");
}

struct ListNode *make_list(int *array, int len)
{
    struct ListNode *tail = NULL, *list = NULL;
    int i;
    
    for (i = 0; i < len; i++) {
        struct ListNode *node = malloc(sizeof(struct ListNode));
        node->val = array[i];
        node->next = NULL;
        if (list == NULL) {
            list = node;
            tail = node;
            continue;
        }
        tail->next = node;
        tail = node;
    }

    return list;
}

struct ListNode *merge_two_lists(struct ListNode *l1, struct ListNode *l2)
{
    struct ListNode dummy, *tail = &dummy;
    dummy.next = NULL;

    while (l1 != NULL || l2 != NULL) {
        struct ListNode *node = malloc(sizeof(struct ListNode));
        node->next = NULL;
        tail->next = node;
        tail = node;
        if (l1 != NULL) {
            if (l2 != NULL) {
                if (l1->val < l2->val) {
                    node->val = l1->val;
                    l1 = l1->next;
                } else {
                    node->val = l2->val;
                    l2 = l2->next;
                }
            } else {
                node->val = l1->val;
                l1 = l1->next;
            }
        } else {
            node->val = l2->val;
            l2 = l2->next;
        }
    }

    return dummy.next;
}

int main(int argc, char **argv)
{
    int arr1[] = {1, 2, 4};
    int arr2[] = {1, 3, 4};
    struct ListNode *l1 = make_list(arr1, sizeof(arr1)/sizeof(int));
    struct ListNode *l2 = make_list(arr2, sizeof(arr2)/sizeof(int));

    printf(" Input:\n  list1: "); print_list(l1);
    printf("  list2: "); print_list(l2);

    struct ListNode *merged = merge_two_lists(l1, l2);
    printf(" Output:\n "); print_list(merged);

    return EXIT_SUCCESS;
}
