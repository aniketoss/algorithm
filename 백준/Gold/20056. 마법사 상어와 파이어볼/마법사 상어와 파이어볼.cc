/*
tiral and error:

문제의 조건 "모두 짝수/모두 홀수 방향 파이어 볼이 합쳐지면.." => 홀수+홀수 =짝수, 짝수+짝수= 짝수, 홀수+짝수 = 짝수 임을 이용하여 홀수+홀수+홀수+홀수 = 짝수,

짝수+짝수+짝수+짝수 = 짝수이므로 방향값을 다더하고 %2 하면 쉽게 처리가능해 보였지만.

홀+짝+홀+짝 = 짝수 라는 반례 존재.

void div() {
  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= N; j++) {
        ......
        int dir = 0;
        for (auto idx : grid[i][j]) {
          mass += fbNodes[idx].mMas;
          vt += fbNodes[idx].mVt;
          dir += fbNodes[idx].mDir;
          fbNodes[idx].del = true; // deleted
        }
        // div to 4
        ......
}
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

#define pb push_back
#define fi first
#define se second

#define MAXN (55)
#define MAXM (444444)

#define _FR(...) // freopen(__VA_ARGS__)
#define _PF(...) printf(__VA_ARGS__)
int N, M, K;

struct Node {
  int mRow;
  int mCol;
  int mMas;
  int mVt;
  int mDir;
  bool del;
} fbNodes[MAXM];
int bCnt;

int dx[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dy[8] = {0, 1, 1, 1, 0, -1, -1, -1};

vector<int> grid[MAXN][MAXN];

void addFireBall(int mRow, int mCol, int mMas, int mVt, int mDir) {
  Node fb = fbNodes[++bCnt];
  fb = {mRow, mCol, mMas, mVt, mDir, false};
  fbNodes[bCnt] = fb;
}

void mapClear() {
  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= N; j++) {
      grid[i][j].clear();
    }
  }
}

void init() {
  ::bCnt = 0;
  mapClear();
  for (int i = 0; i < M; i++) {
    int r, c, m, s, d;
    scanf("%d %d %d %d %d", &r, &c, &m, &s, &d);
    addFireBall(r, c, m, s, d);
  }
}

void div() {
  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= N; j++) {
      int fbCnt = grid[i][j].size();
      if (fbCnt && fbCnt > 1) {
        // merge
        int mass = 0;
        int vt = 0;
        bool odd = false;
        bool even = false;
        for (auto idx : grid[i][j]) {
          mass += fbNodes[idx].mMas;
          vt += fbNodes[idx].mVt;
          if ((fbNodes[idx].mDir % 2) != 0) {
            odd = true;
          } else {
            even = true;
          }
          fbNodes[idx].del = true;  // deleted
        }
        // div to 4
        int mMass = mass / 5;
        int vVt = vt / fbCnt;
        // new Dir?
        int case1[4] = {0, 2, 4, 6};
        int case2[4] = {1, 3, 5, 7};
        if (mMass == 0) continue;
        for (int k = 0; k < 4; k++) {
          if (odd && even) {
            addFireBall(i, j, mMass, vVt, case2[k]);
          } else {
            addFireBall(i, j, mMass, vVt, case1[k]);
          }
        }
      }
    }
  }
}

void merge() {
  mapClear();
  for (int i = 1; i <= bCnt; i++) {
    Node fb = fbNodes[i];
    if (fb.del) continue;
    int r = fb.mRow;
    int c = fb.mCol;

    grid[r][c].pb(i);
  }
}

void process() {
  // fireballs
  for (int i = 1; i <= bCnt; i++) {
    Node fb = fbNodes[i];
    if (fb.del) continue;

    int r = fb.mRow;
    int c = fb.mCol;

    int vt = fb.mVt;
    int dir = fb.mDir;

    int rr = r;
    int cc = c;
    for (int k = 0; k < vt; k++) {
      rr = rr + dx[dir];
      cc = cc + dy[dir];
      if (rr < 1 && cc <= N && cc >= 1) {
        rr = N;
      } else if (rr > N && cc <= N && cc >= 1) {
        rr = 1;
      } else if (rr >= 1 && rr <= N && cc > N) {
        cc = 1;
      } else if (rr >= 1 && rr <= N && cc < 1) {
        cc = N;
      } else if (rr < 1 && cc < 1) {
        rr = cc = N;
      } else if (rr > N && cc > N) {
        rr = cc = 1;
      } else if (rr < 1 && cc > N) {
        rr = N;
        cc = 1;
      } else if (rr > N && cc < 1) {
        rr = 1;
        cc = N;
      }

      fbNodes[i].mRow = rr;
      fbNodes[i].mCol = cc;
    }
  }
}

void move() {
  for (int i = 0; i < K; i++) {
    process();
    merge();
    div();
  }
}

int main(void) {
  _FR("sample_input.txt", "r", stdin);
  scanf("%d %d %d", &N, &M, &K);
  init();
  int ans = 0;
  if (M != 0) {
    move();
    // survived fireballs
    for (int i = 1; i <= bCnt; i++) {
      Node fb = fbNodes[i];
      if (fb.del) continue;

      ans += fb.mMas;
    }
  }
  printf("%d\n", ans);
  return 0;
}
