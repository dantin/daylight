#include <iostream>

using namespace std;

struct RandomListNode {
  int label;
  RandomListNode *next, *random;
  RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
};

class Solution {
public:
  RandomListNode *copyRandomList(RandomListNode *head)
  {
    // insert nodes
    RandomListNode *cur = head;
    while (cur != NULL) {
      RandomListNode *tmp = new RandomListNode(cur->label);
      tmp->next = cur->next;
      cur->next = tmp;
      cur = tmp->next;
    }
    // copy random pointer
    cur = head;
    while (cur != NULL) {
      RandomListNode *tmp = cur->next;
      if (cur->random != NULL) {
        tmp->random = cur->random->next;
      }
      cur = tmp->next;
    }
    // decouple two links
    cur = head;
    RandomListNode *dup = head == NULL ? NULL : head->next;
    while (cur != NULL) {
      RandomListNode *tmp = cur->next;
      cur->next = tmp->next;
      if (tmp->next != NULL) {
        tmp->next = tmp->next->next;
      }
      cur = cur->next;
    }
    return dup;
  }
};

int main()
{
  RandomListNode *origin = new RandomListNode(1);
  RandomListNode *n2 = new RandomListNode(2);
  RandomListNode *n3 = new RandomListNode(3);

  origin->next = n2;
  n2->next = n3;
  n3->random = n2;
  origin->random = n3;

  Solution s;
  RandomListNode *dup = s.copyRandomList(origin);

  return 0;
}
