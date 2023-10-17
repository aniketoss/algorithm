#include <algorithm>
#include <iostream>
#include <set>
#include <unordered_map>
#include <vector>
using namespace std;

#define _FR(...)  // freopen(__VA_ARGS__)

#define fi first
#define se second
#define pb push_back
#define ppb pop_back

#define MAXN (111111)

int N;
int cnt;
bool flag;
vector<bool> visit(MAXN);
vector<int> ord(MAXN);
unordered_map<int, set<int>> tree;
void init() {
  ::cnt = 0;
  visit.clear();
  flag = false;
  for (int i = 0; i < N - 1; i++) {
    int u, v;
    scanf("%d %d", &u, &v);
    tree[u].insert(v);
    tree[v].insert(u);
  }
  for (int i = 0; i < N; i++) {
    int num;
    scanf("%d", &num);
    ord[i] = num;
  }
}

void dfs(int x, int depth) {
  if (visit[x]) {
    return;
  }
  visit[x] = true;
  cnt++;
  for (int i = 0; i < tree[x].size(); i++) {
    if (!visit[ord[cnt]] && tree[x].find(ord[cnt]) != tree[x].end()) {
      dfs(ord[cnt], depth + 1);
    }
  }
}

int main(void) {
  _FR("sample_input.txt", "r", stdin);
  scanf("%d", &N);
  init();
  dfs(1, 0);
  cnt < N ? printf("%d\n", 0) : printf("%d\n", 1);
  return 0;
}