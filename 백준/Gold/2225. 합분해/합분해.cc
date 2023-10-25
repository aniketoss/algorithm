#include <cstdio>

using namespace std;

#define MAX (201)
#define mod (1000000000)
int N, K;
unsigned long long dp[MAX][MAX];
int main(int argc, char* argv[]) {
  scanf("%d %d", &N, &K);
  for (int k = 1; k <= K; k++) {
    dp[0][k] = 1;
  }
  for (int n = 1; n <= N; n++) {
    dp[n][1] = 1;
    for (int k = 2; k <= K; k++) {
      for (int i = 0; i <= n; i++) {
        dp[n][k] += dp[n - i][k - 1] % mod;
        dp[n][k] %= mod;
      }
    }
  }
  printf("%llu\n", dp[N][K] % mod);
  return 0;
}