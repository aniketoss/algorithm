#include <memory.h>

#include <algorithm>
#include <climits>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#define MAXN 5555
#define MAXM 5555

using namespace std;

#define _FR(...) // freopen(__VA_ARGS__)

int N, M;

int lenA;
int lenB;
int dp[MAXN + 1][MAXM + 1][2];
string strA, strB;

int dfs(int i, int j, int k = 0) {
  if (i < 0 || i >= N) return 0;
  if (j == M) return 0;
  int ret = dp[i][j][k];
  if (ret != -1) return ret;
  if (strA[i] == strB[j]) {
    return dp[i][j][k] = max(dfs(i - 1, j + 1, 0), dfs(i + 1, j + 1, 1)) + 1;
  } else {
    return dp[i][j][k] = max(dfs(i - 1, j + 1, 0), dfs(i + 1, j + 1, 1));
  }
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);

  _FR("sample_input.txt", "r", stdin);
  memset(dp, -1, sizeof(dp));
  cin >> N >> M >> strA >> strB;
  lenA = strA.size();
  lenB = strB.size();
  int ans = INT_MIN;
  for (int i = 0; i < lenA; i++) {
    int ret = dfs(i, 0);
    ans = max(ans, ret);
  }
  printf("%d\n", ans);
  return 0;
}