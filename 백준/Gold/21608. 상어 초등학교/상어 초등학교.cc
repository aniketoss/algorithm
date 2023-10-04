#include <memory.h>

#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

#define MAXN (22)
#define MAXSTUDENTS (22 * 22)

#define fi first
#define se second
#define pb push_back

#define _FR(...) // freopen(__VA_ARGS__)
#define _PF(...) printf(__VA_ARGS__)

using namespace std;

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, -1, 0, 1};

int gSlot[MAXN][MAXN];
vector<int> students[MAXSTUDENTS];
pair<int, int> pos[MAXSTUDENTS];

int N;
void init(int N) {
  ::N = N;
  memset(gSlot, 0, sizeof(gSlot));
  for (int i = 0; i < MAXSTUDENTS; i++) {
    students[i].clear();
    pos[i] = {0, 0};
  }
}

struct cmp4map {
  bool operator()(const pair<pair<int, int>, int> a,
                  const pair<pair<int, int>, int> b) {
    if (a.fi.fi != b.fi.fi) {
      return a.fi.fi < b.fi.fi;
    } else {
      if (a.fi.se != b.fi.se) {
        return a.fi.se < b.fi.se;
      } else {
        return a.se > b.se;
      }
    }
  }
};

pair<int, int> deploy(int mId) {
  priority_queue<pair<pair<int, int>, int>, vector<pair<pair<int, int>, int>>,
                 cmp4map>
      pq;

  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= N; j++) {
      int blank = 0;
      int adjFriends = 0;
      if (gSlot[i][j]) continue;
      for (int d = 0; d < 4; d++) {
        int ii = i + dx[d];
        int jj = j + dy[d];
        if (ii > N || jj > N || ii < 1 || jj < 1) continue;
        if (gSlot[ii][jj] == 0) {
          blank++;
        } else {
          for (auto& student : students[mId]) {
            if (gSlot[ii][jj] == student) {
              adjFriends++;
              break;
            }
          }
        }
      }
      pq.push({{adjFriends, blank}, (i << 8 | j)});
    }
  }

  int result = pq.top().se;
  int row = result >> 8 & 0xff;
  int col = result & 0xff;
  return {row, col};
}

void addStudent(int mId, int mList[4]) {
  for (int i = 0; i < 4; i++) {
    students[mId].pb(mList[i]);
  }
}

int calcPow(int power) {
  int ret = 1;
  for (int i = 0; i < power; i++) {
    ret *= 10;
  }
  return ret;
}

int getScore() {
  int ret = 0;
  for (int i = 1; i <= N * N; i++) {
    int row = pos[i].fi;
    int col = pos[i].se;
    int num = 0;
    for (int d = 0; d < 4; d++) {
      int rrow = row + dx[d];
      int ccol = col + dy[d];
      if (rrow > N || ccol > N || rrow < 1 || ccol < 1) continue;
      for (auto& student : students[i]) {
        if (gSlot[rrow][ccol] == student) {
          num++;
          break;
        }
      }
    }
    if (num != 0) ret += calcPow(num);
  }
  return ret;
}

int main(void) {
  _FR("sample_input.txt", "r", stdin);
  int N;
  scanf("%d", &N);
  init(N);
  for (int i = 1; i <= N * N; i++) {
    int id;
    int list[4];
    scanf("%d", &id);
    for (int j = 0; j < 4; j++) {
      scanf("%d", &list[j]);
    }
    addStudent(id, list);
    pair<int, int> seat = deploy(id);
    gSlot[seat.fi][seat.se] = id;
    pos[id] = {seat.fi, seat.se};
  }
  printf("%d\n", getScore() / 10);
  return 0;
}
