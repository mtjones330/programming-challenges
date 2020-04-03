#include <iostream>
#include <algorithm>
using namespace std;

int insertionSort(int s[], int n) {
  for (int i = 1; i < n; i++) {
    int j = i;

    while(j > 0 && s[j] < s[j - 1]) {
      swap(s[j], s[j - 1]);
      j--;
    }
  }
}

int main() {
  int s[] = { 5, 3, 4, 1, 2 };
  int n = sizeof(s) / sizeof(*s);

  insertionSort(s, n);

  for (int i = 0; i < n; i++) {
    printf("%d ", s[i]);
  }

  printf("\n");
}