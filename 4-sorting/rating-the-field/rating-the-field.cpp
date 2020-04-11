#include <stdio.h>
#include <string.h>
#include <stdlib.h>
using namespace std;

#define NAMELEGNTH 30
#define NSUITORS 100

#define BESTHEIGTH 180
#define BESTWEIGHT 75

typedef struct {
  char first[NAMELEGNTH];
  char last[NAMELEGNTH];
  int height;
  int weight;
} suitor;

suitor suitors[NSUITORS];
int nsuitors;

void readSuitors() {
  char first[NAMELEGNTH], last[NAMELEGNTH];
  int height, weight;

  nsuitors = 0;

  while(scanf("%s %s %d %d\n",
    suitors[nsuitors].first,
    suitors[nsuitors].last,
    &height,
    &weight
  ) != EOF) {
    
    suitors[nsuitors].height = abs(height - BESTHEIGTH);

    if (weight > BESTWEIGHT) {
      suitors[nsuitors].weight = weight - BESTWEIGHT;
    }
    else {
      suitors[nsuitors].weight = - weight;
    }

    nsuitors++;
  }
}

int suitorCompare(const void *a, const void *b) {
  int result;

  const suitor *sa = (const suitor *)a;
  const suitor *sb = (const suitor *)b;

  if (sa -> height < sb -> height) return -1;
  if (sa -> height > sb -> height) return 1;
  
  if (sa -> weight < sb -> weight) return -1;
  if (sa -> weight > sb -> weight) return 1;
  
  if ((result = strcmp(sb -> last, sb -> last)) != 0) return result;

  return (strcmp(sa -> first, sb -> first));
}

int main() {
  readSuitors();

  qsort(suitors, nsuitors, sizeof(suitor), suitorCompare);

  for (int i = 0; i < nsuitors; i++) {
    printf("%s, %s\n", suitors[i].last, suitors[i].first);
  }
}