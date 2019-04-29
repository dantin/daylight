#include <stdio.h>
#include <stdlib.h>

struct Object {
    int *nums;
    int len;
};

struct RandomListNode {
    int label;
    struct RandomListNode *next;
    struct RandomListNode *random;
};

void print_nums(int *nums, int size)
{
    int i;
    char *s = "";
    printf("[");
    for (i = 0; i < size; i++) {
        printf("%s%d", s, nums[i]);
        s = ", ";
    }
    printf("]");
}

struct RandomListNode *make_list(int *nums, int size)
{
    struct RandomListNode dummy;
    struct RandomListNode *prev;
    dummy.next = NULL;
    prev = &dummy;

    int i;
    for (i = 0; i < size; i++) {
        struct RandomListNode *node = malloc(sizeof(*node));
        node->label = nums[i];
        node->next = NULL;
        node->random = NULL;
        prev->next = node;
        prev->random = node;
        prev = node;
    }

    return dummy.next;
}

void print_list(struct RandomListNode *node)
{
    char *s = "";
    while (node != NULL) {
        printf("%s%d", s, node->label);
        s = " -> ";
        node = node->next;
    }
}

void free_list(struct RandomListNode *node)
{
    struct RandomListNode *tmp;

    while (node != NULL) {
        tmp = node;
        node = node->next;
        free(tmp);
    }
}

struct RandomListNode *copy_random_list(struct RandomListNode *head)
{
    if (head == NULL) {
        return NULL;
    }

    // copy each node, append it to the next.
    struct RandomListNode *p, *new;
    for (p = head; p != NULL; p = p->next->next) {
        new = malloc(sizeof(*new));
        new->label = p->label;
        new->next = p->next;
        p->next = new;
    }

    // make random ptr right.
    for (p = head; p != NULL; p = p->next->next) {
        new = p->next;
        new->random = p->random != NULL ? p->random->next : NULL;
    }

    // split double list.
    struct RandomListNode dummy;
    struct RandomListNode *prev = &dummy;
    for (p = head; p != NULL; p = p->next) {
        new = p->next;
        p->next = new->next;
        prev->next = new;
        prev = new;
        new->next = NULL;
    }

    return dummy.next;
}



int main(int argc, char **argv)
{
    int nums1[] = { 1, 2, 3 }, len1 = sizeof(nums1) / sizeof(int);
    struct Object inputs[] = {
        { .nums = nums1, .len = len1 },
    };
    int i, len = sizeof(inputs) / sizeof(struct Object);

    for (i = 0; i < len; i++) {
        int *nums = inputs[i].nums;
        int size = inputs[i].len;

        printf("\n Input: ");
        print_nums(nums, size);
        struct RandomListNode *list = make_list(nums, size);
        struct RandomListNode *list2 = copy_random_list(list);

        printf("\n Output: ");
        print_list(list2);
        printf("\n");
        free_list(list);
        free_list(list2);
    }
    return EXIT_SUCCESS;
}
