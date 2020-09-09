#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Object {
    char *lhs;
    char *rhs;
};

struct ListNode {
    int val;
    struct ListNode *next;
};

void print_num(struct ListNode *node)
{
    if (node == NULL) {
        return;
    }
    printf("(%d", node->val);
    while ((node = node->next) != NULL) {
        printf(" -> %d", node->val);
    }
    printf(")");
}

struct ListNode *make_num(const char *digits)
{
    int len = strlen(digits);
    const char *c = digits + len - 1;
    struct ListNode dummy, *prev;

    dummy.next = NULL;
    prev = &dummy;
    while (len-- > 0) {
        struct ListNode *p = malloc(sizeof(*p));
        p->val = *c-- - '0';
        p->next = NULL;
        prev->next = p;
        prev = p;
    }

    return dummy.next;
}

void free_num(struct ListNode *node) {
    struct ListNode *n;
    while (node != NULL) {
        n = node;
        node = node->next;
        free(n);
    }
}

struct ListNode* add_two_numbers(struct ListNode* l1, struct ListNode* l2)
{
    int carry = 0;
    struct ListNode dummy, *prev;

    dummy.next = NULL;
    prev = &dummy;
    while (l1 != NULL || l2 != NULL || carry) {
        int sum = 0;

        if (l1 != NULL) {
            sum += l1->val;
            l1 = l1->next;
        }
        if (l2 != NULL) {
            sum += l2->val;
            l2 = l2->next;
        }
        sum += carry;

        struct ListNode *p = malloc(sizeof(*p));
        p->val = sum % 10;
        p->next = NULL;
        prev->next = p;
        prev = p;

        carry = sum / 10;
    }

    return dummy.next;
}

int main(int argc, char **argv)
{
    struct Object inputs[] = {
        { .lhs = "342", .rhs = "465" },
    };
    int i, len = sizeof(inputs) / sizeof(struct Object);

    for (i = 0; i < len; i++) {
        struct ListNode *lhs = make_num(inputs[i].lhs);
        struct ListNode *rhs = make_num(inputs[i].rhs);
        struct ListNode *sum = add_two_numbers(lhs, rhs);
        int n1 = atoi(inputs[i].lhs);
        int n2 = atoi(inputs[i].rhs);

        printf("\n Input: ");
        print_num(lhs);
        printf(" + ");
        print_num(rhs);
        printf("\n Output: ");
        print_num(sum);

        printf("\n Explanation: %d + %d = %d\n", n1, n2, n1 + n2);

        free_num(lhs);
        free_num(rhs);
        free_num(sum);
    }

    return EXIT_SUCCESS;
}
