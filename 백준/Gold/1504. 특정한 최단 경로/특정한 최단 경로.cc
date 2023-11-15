#include <algorithm>
#include <climits>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

#define MAXN (888)

#define fi first
#define se second
#define pb push_back

#define _FR(...) // freopen(__VA_ARGS__)
#define _PF(...) printf(__VA_ARGS__)

typedef long long ll;
int N, E;

vector<pair<int, ll>> graph[MAXN];

void init() {
  for (int i = 0; i < MAXN; i++) graph[i].clear();
}

void addVertex(int mV, int mU, int mC) {
  graph[mV].pb({mU, mC});
  graph[mU].pb({mV, mC});
}

ll dist[MAXN];

void dikstra(int start) {
  priority_queue<pair<int, ll>, vector<pair<int, ll>>, greater<pair<int, ll>>>
      que;
  for (int i = 0; i <= N; i++) dist[i] = INT_MAX;
  dist[start] = 0;
  que.push({start, 0});

  while (!que.empty()) {
    pair<int, ll> tv = que.top();
    int now = tv.fi;
    ll cost = tv.se;
    que.pop();
    if (dist[now] < cost) continue;

    for (auto& next : graph[now]) {
      if (dist[next.fi] > dist[now] + next.se) {
        dist[next.fi] = dist[now] + next.se;
        que.push({next.fi, dist[now] + next.se});
      }
    }
  }
}

ll findPath(int mV1, int mV2) {
  ll ret = -1;
  dikstra(mV1);
  ll sToV1 = dist[1];
  ll v1ToV2 = dist[mV2];
  ll v1ToN = dist[N];
  dikstra(mV2);
  ll sToV2 = dist[1];
  ll v2ToN = dist[N];

  ll pathA = sToV1 + v1ToV2 + v2ToN;
  ll pathB = sToV2 + v1ToV2 + v1ToN;

  if (pathA + pathB >= INT_MAX) return -1;
  return pathA < pathB ? pathA : pathB;
}

int main(void) {
  _FR("sample_input.txt", "r", stdin);
  scanf("%d %d", &N, &E);
  init();
  for (int i = 0; i < E; i++) {
    int v, u, c;
    scanf("%d %d %d", &v, &u, &c);
    addVertex(v, u, c);
  }
  int v1, v2;
  scanf("%d %d", &v1, &v2);
  printf("%lld\n", findPath(v1, v2));
  return 0;
}
