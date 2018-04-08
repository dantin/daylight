#include <iostream>

using namespace std;

static const int MAX_LEN = 200;

struct Card {
  char suit;
  char value;
};

void buble_sort(struct Card cards[], const int size)
{
  for (int i = 0; i < size; ++i) {
    for (int j = size-1; j >= i+1; --j) {
      if (cards[j].value < cards[j-1].value) {
        Card tmp = cards[j];
        cards[j] = cards[j-1];
        cards[j-1] = tmp;
      }
    }
  }
}

void selection_sort(struct Card cards[], const int size)
{
  for (int i = 0; i < size; ++i) {
    int minj = i;
    for (int j = i; j < size; ++j) {
      if (cards[j].value < cards[minj].value) minj = j;
    }
    Card tmp = cards[i];
    cards[i] = cards[minj];
    cards[minj] = tmp;
  }
}

void display(struct Card cards[], const int size)
{
  for (int i = 0; i < size; ++i) {
    if (i > 0) cout << " ";
    cout << cards[i].suit << cards[i].value;
  }
  cout << endl;
}

bool isStable(struct Card c1[], struct Card c2[], const int size)
{
  for (int i = 0; i < size; ++i)
    if (c1[i].suit != c2[i].suit) return false;
  return true;
}

int main()
{
  Card cards1[MAX_LEN], cards2[MAX_LEN];
  int n;
  char ch;

  cin >> n;
  for (int i = 0; i < n; ++i) cin >> cards1[i].suit >> cards1[i].value;
  for (int i = 0; i < n; ++i) cards2[i] = cards1[i];

  buble_sort(cards1, n);
  selection_sort(cards2, n);

  display(cards1, n);
  cout << "Stable" << endl;
  display(cards2, n);
  if (isStable(cards1, cards2, n)) {
    cout << "Stable" << endl;
  } else {
    cout << "Not Stable" << endl;
  }

  return 0;
}
