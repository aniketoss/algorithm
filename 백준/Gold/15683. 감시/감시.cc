#include <memory.h>

#include <algorithm>
#include <climits>
#include <iostream>
#include <unordered_map>
#include <vector>

#define fi first
#define se second
#define pb push_back

#define MAXN (9)

#define _FR(...) // freopen(__VA_ARGS__)
#define _PF(...) printf(__VA_ARGS__)

using namespace std;

int N, M;
int grid[MAXN][MAXN];

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, -1, 0, 1};

vector<vector<vector<int>>> cctvDir = {
    {},
    {{3}, {2}, {1}, {0}},
    {{1, 3}, {0, 2}},
    {{0, 3}, {3, 2}, {1, 2}, {0, 1}},
    {{1, 0, 3}, {0, 3, 2}, {3, 2, 1}, {0, 1, 2}},
    {{0, 1, 2, 3}}};

vector<pair<int, int>> cctvList;
int cctvCnt;
int answer = INT_MAX;

void init() {
  memset(grid, 0, sizeof(grid));
  cctvList.clear();
  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= M; j++) {
      scanf("%d", &grid[i][j]);
      if (grid[i][j] > 0 && grid[i][j] != 6) {
        cctvList.pb({i, j});
      }
    }
  };
  cctvCnt = cctvList.size();
}

void save(int mGrid[][MAXN]) {
  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= M; j++) {
      mGrid[i][j] = grid[i][j];
    }
  }
}

void restore(int mGrid[][MAXN]) {
  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= M; j++) {
      grid[i][j] = mGrid[i][j];
    }
  }
}

void scan(int row, int col, int dir) {
  int nextRow = row;
  int nextCol = col;
  for (;;) {
    nextRow = nextRow + dx[dir];
    nextCol = nextCol + dy[dir];

    if (nextRow > N || nextRow < 1 || nextCol > M || nextCol < 1) break;
    if (grid[nextRow][nextCol] == 0) {
      grid[nextRow][nextCol] = -1;
    } else if (grid[nextRow][nextCol] == 6) {
      break;
    }
  }
}

int getScore() {
  int ret = 0;
  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= M; j++) {
      if (grid[i][j] == 0) {
        ret++;
      }
    }
  }
  return ret;
}

void dfs(int depth) {
  if (depth >= cctvCnt) {
    answer = min(answer, getScore());
    return;
  }

  int row = cctvList[depth].fi;
  int col = cctvList[depth].se;
  int tGrid[MAXN][MAXN];
  int type = grid[row][col];
  save(tGrid);
  for (auto& rotation : cctvDir[type]) {
    for (auto& dir : rotation) {
      scan(row, col, dir);
    }
    dfs(depth + 1);
    restore(tGrid);
  }
}

int main(void) {
  _FR("sample_input.txt", "r", stdin);
  scanf("%d %d", &N, &M);
  init();
  dfs(0);
  printf("%d\n", answer);
  return 0;
}