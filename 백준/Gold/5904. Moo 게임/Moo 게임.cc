#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

#define MAXN ()

#define _FR(...) // freopen(__VA_ARGS__)
#define _PF(...) printf(__VA_ARGS__)

int N;

bool flag = false;
void moo(int n, int k, int len) {
  if (k == 0) {
    if (n == 1)
      printf("m");
    else {
      printf("o");
    }
    flag = true;
    return;
  }
  int llen = (len - k - 3) / 2;
  if (n >= llen + k + 3 && flag == false) {
    moo(n - (llen + k + 3), k - 1, llen);
  } else if (n <= llen && flag == false) {
    moo(n, k - 1, llen);
  } else if (n > llen && n < llen + k + 3 && flag == false) {
    if (n - llen > 1) {
      printf("o");
    } else {
      printf("m");
    }
    flag = true;
  }
}

int main(void) {
  _FR("sample_input.txt", "r", stdin);
  int tc = 1;
  while (tc--) {
    flag = false;
    scanf("%d", &N);
    int k = 0;
    int len = 0;
    while (len < N) {
      len = len * 2 + k + 3;
      k++;
    }
    moo(N, k - 1, len);
  }
  return 0;
}
