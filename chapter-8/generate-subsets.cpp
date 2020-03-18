#include<iostream>
#include<vector>
using namespace std;

const int NMAX = 21;

bool isSolution(int k, int n) {
  k == n;
}

void processSolution(int a[], int n) {
  printf("{");

  for (int i = 1; i <= n; i++) {
    if (a[i] == true) {
      printf(" %d", i);
    }
  }

  printf(" }\n");
}

vector<bool> getCandidates() {
  return vector<bool> { true, false };
}

void backtrack(int a[], int k, int n) {
  if (isSolution(k, n)) {
    processSolution(a, n);
    return;
  }

  k++;

  vector<bool> c = getCandidates();

  for (int i = 0; i < c.size(); i++) {
    a[k] = c.at(i);
    backtrack(a, k, n);
  }
}

int main() {
  int a[NMAX] = { false };
  int n = 20;

  backtrack(a, 0, n);
}