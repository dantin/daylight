#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode *make_list(const char *digits)
{
    struct ListNode dummy, *prev;
    int len = strlen(digits);
    const char *c = digits + len - 1;

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

void display(struct ListNode *list)
{
    int sum = 0, factor = 1;

    while (list != NULL) {
        sum += list->val * factor;
        factor *= 10;
        list = list->next;
    }

    printf("%d\n", sum);
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

int main(int argc, const char *argv[])
{
    char *nums[] = {"342", "465"};

    struct ListNode *l1 = make_list(nums[0]);
    struct ListNode *l2 = make_list(nums[1]);
    struct ListNode *res = add_two_numbers(l1, l2);

    display(l1);
    display(l2);
    display(res);

    return 0;
}
