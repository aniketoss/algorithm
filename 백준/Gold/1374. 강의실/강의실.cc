#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
using namespace std;

#define pb push_back
#define fi first
#define se second

#define MAXN (111111)

#define _FR(...) freopen(__VA_ARGS__)

int N;
vector<pair<int, int>> lects;

struct cmp {
  bool operator()(const pair<int, int> &a, const pair<int, int> &b) const {
    return a.se < b.se;
  }
};

int main(void) {
  // _FR("sample_input.txt", "r", stdin);
  cin >> N;
  for (int i = 0; i < N; i++) {
    int num, s, f;
    cin >> num >> s >> f;
    lects.pb({s, f});
  }

  sort(lects.begin(), lects.end(),
       [](const pair<int, int> a, const pair<int, int> b) {
         return a.fi < b.fi;
       });

  multiset<pair<int, int>, cmp> st;
  st.insert(lects[0]);
  int cnt = 1;
  for (int i = 1; i < N; i++) {
    multiset<pair<int, int>, cmp>::iterator it = st.begin();
    int start = lects[i].fi;
    int end = it->se;
    if (start < end) {
      cnt++;
    } else {
      it = st.erase(it);
    }
    st.insert(lects[i]);
  }
  printf("%d\n", cnt);
  return 0;
}

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
