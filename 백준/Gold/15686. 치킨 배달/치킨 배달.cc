#include <memory.h>

#include <algorithm>
#include <climits>
#include <cstdio>
#include <queue>
#include <vector>
#define MAXN 55
#define MAXM 15

#define fi first
#define se second
#define pb push_back

#define _FR(...) //freopen(__VA_ARGS__)

using namespace std;

int N, M;

vector<pair<int, int>> stores;
int adj[MAXN][MAXN];
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, -1, 0, 1};

void init() {
  stores.clear();
  memset(adj, 0, sizeof(adj));
}

int bfs(queue<pair<pair<int, int>, int>>& que, int visit[][MAXN]) {
  int ret = 0;
  while (!que.empty()) {
    pair<pair<int, int>, int> cur = que.front();
    que.pop();
    int r = cur.fi.fi;
    int c = cur.fi.se;
    int dist = cur.se;

    for (int d = 0; d < 4; d++) {
      int rr = r + dx[d];
      int cc = c + dy[d];

      if (rr < 0 || cc < 0 || rr >= N || cc >= N) continue;
      if (visit[rr][cc]) continue;
      if (adj[rr][cc] == 1) {
        ret += (dist + 1);
      }
      visit[rr][cc] = 1;
      que.push({{rr, cc}, dist + 1});
    }
  }
  return ret;
}

int main(void) {
  _FR("sample_input.txt", "r", stdin);
  init();
  scanf("%d %d", &N, &M);

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      scanf("%d", &adj[i][j]);
      if (adj[i][j] == 2) stores.pb({i, j});
    }
  }
  int ans = INT_MAX;
  int sCnt = stores.size();

  for (int k = 1; k < (1 << sCnt); k++) {
    queue<pair<pair<int, int>, int>> que;
    int visit[MAXN][MAXN] = {
        0,
    };
    for (int j = 0; j < sCnt; j++) {
      if (!(k & (1 << j))) continue;
      que.push({stores[j], 0});
      visit[stores[j].fi][stores[j].se] = 1;
    }
    if (que.size() == M) {
      ans = min(ans, bfs(que, visit));
    }
  }
  printf("%d\n", ans);
  return 0;
}