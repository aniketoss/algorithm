#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

#define MAX 1000

int n;
int iq[MAX + 1];
vector<int> adj[MAX + 1];

bool iq_cmp(int a, int b) { return iq[a] > iq[b]; }

int main(void) {
  scanf("%d", &n);

  for (int i = 1; i <= n; ++i) scanf("%d", &iq[i]);

  for (int i = 1; i < n; ++i) {
    int a, b;
    scanf("%d%d", &a, &b);
    adj[a].push_back(b);
  }

  for (int i = 1; i <= n; ++i) {
    sort(adj[i].begin(), adj[i].end(), iq_cmp);

    for (int j = 1; j < adj[i].size(); ++j)
      printf("%d %d\n", adj[i][j - 1], adj[i][j]);

    if (adj[i].size() > 0) printf("%d %d\n", i, adj[i][0]);
  }

  return 0;
}