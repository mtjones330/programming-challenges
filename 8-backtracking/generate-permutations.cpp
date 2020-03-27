#include <iostream>
#include <vector>
using namespace std;

const int NMAX = 16;

bool isSolution(int k, int n) {
  return k == n;
}

void processSolution(int a[], int n) {
  printf("{");

  for (int i = 1; i <= n; i++) {
    printf(" %d", a[i]);
  }

  printf(" }\n");
}

vector<int> getCandidates(int a[], int k, int n) {
  vector<int> candidates;

  int inPerm[NMAX] = { false };

  for (int i = 1; i < k; i++) {
    inPerm[a[i]] = true;
  }

  for (int i = 1; i <= n; i++) {
    if (inPerm[i] == false) {
      candidates.push_back(i);
    }
  }

  return candidates;
}

void backtrack(int a[], int k, int n) {
  if (isSolution(k, n)) {
    processSolution(a, n);
    return;
  }

  k++;

  vector<int> candidates = getCandidates(a, k, n);

  for (int i = 0; i < candidates.size(); i++) {
    a[k] = candidates.at(i);
    backtrack(a, k, n);
  }
}

int main(){
  int a[NMAX] = { 0 };
  int n = 3;

  backtrack(a, 0, n);
}