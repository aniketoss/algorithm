#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

#define MAXN (1111)

#define pb push_back
#define _FR(...) freopen(__VA_ARGS__)

int n;
int iq[MAXN];
vector<int> adj[MAXN];

bool cmp4iq(const int& a, const int& b) {
    return iq[a] > iq[b];
}

int main(void) {
  scanf("%d", &n);

  for (int i = 1; i <= n; ++i) scanf("%d", &iq[i]);

  for (int i = 1; i < n; ++i) {
    int a, b;
    scanf("%d %d", &a, &b);
    adj[a].pb(b);
  }

  for (int i = 1; i <= n; ++i) {
    sort(adj[i].begin(), adj[i].end(), cmp4iq);

    for (int j = 1; j < adj[i].size(); ++j)
      printf("%d %d\n", adj[i][j - 1], adj[i][j]);

    if (adj[i].size() > 0) printf("%d %d\n", i, adj[i][0]);
  }

  return 0;
}
