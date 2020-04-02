#include <iostream>
#include <algorithm>
using namespace std;

void selectionSort(int s[], int n) {
  for (int i = 0; i < n; i++) {
    int min = i;

    for (int j = i + 1; j < n; j++) {
      if (s[j] < s[min]) {
        min = j;
      }
    }

    swap(s[i], s[min]);
  }
}

int main() {
  int s[] = { 5, 3, 4, 2, 1 };
  int size = sizeof(s) / sizeof(*s);

  selectionSort(s, size);

  for (int i = 0; i < size; i++) {
    printf("%d ", s[i]);
  }

  printf("\n");
}