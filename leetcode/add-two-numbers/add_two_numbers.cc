#include <iostream>

using namespace std;

/**
 * Definition for singly-linked list.
 */
struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
  ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
  {
    ListNode *result = new ListNode(-1);
    ListNode *pre = result;
    ListNode *pa = l1, *pb = l2;
    int carry = 0;

    while (pa != NULL || pb != NULL) {
      int av = (pa == NULL) ? 0 : pa->val;
      int bv = (pb == NULL) ? 0 : pb->val;
      ListNode *node = new ListNode((av + bv + carry) % 10);
      carry = (av + bv + carry) / 10;
      pre->next = node;
      pre = pre->next;
      pa = (pa == NULL) ? NULL : pa->next;
      pb = (pb == NULL) ? NULL : pb->next;
    }
    if (carry > 0) {
      pre->next = new ListNode(1);
    }
    pre = result->next;
    delete result;
    return pre;
  }
};

ListNode *int2list(int num)
{
  ListNode *head = new ListNode(-1);
  ListNode *tail = head;

  while (num != 0) {
    ListNode *node = new ListNode(num%10);
    tail->next = node;
    tail = node;
    num /= 10;
  }

  ListNode *list = head->next;
  delete head;
  return list;
}

void display(ListNode *node)
{
  int i = 0;
  while (node != NULL) {
    if (i > 0) cout << " -> ";
    cout << node->val;
    i++;
    node = node->next;
  }
  cout << endl;
}

int main()
{
  int ia, ib;

  cin >> ia;
  cin >> ib;

  ListNode *pa = int2list(ia);
  display(pa);
  ListNode *pb = int2list(ib);
  display(pb);

  Solution s;
  ListNode *l = s.addTwoNumbers(pa, pb);
  display(l);

  return 0;
}
