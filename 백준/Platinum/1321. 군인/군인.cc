#include <memory.h>

#include <iostream>
#include <set>
#include <vector>
#define _FR(...) freopen(__VA_ARGS__)

#define fi first
#define se second
#define pb push_back

#define ADD 1
#define FIND 2

#define MAXN 555555
#define MAXBS 500

using namespace std;

int N;

int gArr[MAXN];
int bucket[MAXN / MAXBS];

int getBucketidx(int index) { return (index / MAXBS); }
void init() {
  memset(bucket, 0, sizeof(bucket));
  memset(gArr, 0, sizeof(gArr));
  for (int i = 1; i <= N; i++) {
    int num;
    scanf("%d", &num);
    gArr[i] = num;
  }

  // build bucket
  for (int i = 1; i <= N; i++) {
    int idx = getBucketidx(i);
    bucket[idx] += gArr[i];
  }
}

void addSoldier(int index, int diff) {
  int bIdx = getBucketidx(index);
  gArr[index] += diff;
  bucket[bIdx] += diff;
}

void findDiv(int num) {
  int bIdx = getBucketidx(N);
  int sum = 0;
  int left = 0;
  for (int i = 0; i <= bIdx; i++) {
    if (sum + bucket[i] >= num) break;
    sum += bucket[i];
    left++;
  }

  int s = left * MAXBS;
  int e = s + MAXBS - 1;
  while (s <= e && sum < num) {
    sum += gArr[s];
    s++;
  }
  printf("%d\n", s - 1);
}

int main(void) {
  // _FR("sample_input.txt", "r", stdin);
  scanf("%d", &N);
  init();
  int query;
  scanf("%d", &query);
  for (int i = 0; i < query; i++) {
    int in[3];
    scanf("%d", &in[0]);
    switch (in[0]) {
      case ADD:
        scanf("%d %d", &in[1], &in[2]);
        addSoldier(in[1], in[2]);
        break;
      case FIND:
        scanf("%d", &in[1]);
        findDiv(in[1]);
        break;
    }
  }
  return 0;
}