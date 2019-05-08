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

int node_index(struct ListNode *head, struct ListNode *node)
{
    int i = 0;
    while (head != node) {
        i++;
        head = head->next;
    }
    return i;
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

struct ListNode *detect_cycle(struct ListNode *head)
{
    if (head == NULL || head->next == NULL) {
        return NULL;
    }

    bool first = true;
    struct ListNode *p0, *p1;
    for (p0 = head, p1 = head; p1 != NULL && p1->next != NULL; p0 = p0->next, p1 = p1->next->next) {
        if (p0 == p1 && !first) {
            p0 = head;
            while (p0 != p1) {
                p0 = p0->next;
                p1 = p1->next;
            }
            return p0;
        }
        first = false;
    }

    return NULL;
}

int main(int argc, char **argv)
{
    int nums1[] = { 3, 2, 0, -4  }, len1 = sizeof(nums1) / sizeof(int);
    int pos1 = 1;
    int nums2[] = { 1, 2  }, len2 = sizeof(nums2) / sizeof(int);
    int pos2 = 0;
    int nums3[] = { 1  }, len3 = sizeof(nums3) / sizeof(int);
    int pos3 = -1;
    struct Object inputs[] = {
        { .nums = nums1, .len = len1, .pos = pos1  },
        { .nums = nums2, .len = len2, .pos = pos2  },
        { .nums = nums3, .len = len3, .pos = pos3  },
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
        struct ListNode *join_node = detect_cycle(head);
        printf("\n Output: ");
        if (join_node == NULL) {
            printf("no cycle");
        } else {
            printf("tail connects to node index %d", node_index(head, join_node));
        }
        printf("\n");
        free_list(head, tail);
    }

    return EXIT_SUCCESS;
}
