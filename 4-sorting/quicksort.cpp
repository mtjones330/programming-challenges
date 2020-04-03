#include <iostream>
#include <algorithm>
using namespace std;

int partition(int s[], int l, int h) {
  int p = h;
  int firstHigh = l;

  for (int i = l; i < h; i++) {
    if (s[i] < s[p]) {
      swap(s[i], s[firstHigh]);
      firstHigh++;
    }
    
  }

  swap(s[p], s[firstHigh]);

  return firstHigh;
}

void quicksort(int s[], int l, int h) {
  if ((h - l) > 0) {
    int p = partition(s, l, h);
    quicksort(s, l, p - 1);
    quicksort(s, p + 1, h);
  }
}

int main() {
  int s[] = { 5, 3, 4, 2, 1 };
  int size = sizeof(s) / sizeof(*s);

  quicksort(s, 0, size - 1);

  for (int i = 0; i < size; i++) {
    printf("%d ", s[i]);
  }

  printf("\n");
}
