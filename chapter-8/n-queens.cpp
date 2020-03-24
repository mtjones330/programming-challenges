#include <iostream>
#include <vector>
using namespace std;

int n = 8;
int solutionCount = 0;

bool isSolution(int k, int n) {
  return k == n;
}

void processSolution() {
  solutionCount++;
}

vector<int> getCandidates(int a[], int k, int n) {
  vector<int> candidates;

  for (int i = 1; i <= n; i++) {
    bool legalMove = true;

    for (int j = 1; j < k; j++) {
      if (abs(k - j) == abs(i - a[j]) || i == a[j]) {
        legalMove = false;;
      }
    }

    if (legalMove == true) {
      candidates.push_back(i);
    }
  }

  return candidates;
}

void backtrack(int a[], int k, int n) {
  if (isSolution(k, n)) {
    processSolution();
    return;
  }

  k++;

  vector<int> candidates = getCandidates(a, k, n);

  for (int i = 0; i < candidates.size(); i++) {
    a[k] = candidates.at(i);

    backtrack(a, k, n);
  }
}

int main() {
  int a[32] = { 0 };

  backtrack(a, 0, n);

  printf("n=%d solution_count=%d\n", n, solutionCount);
}