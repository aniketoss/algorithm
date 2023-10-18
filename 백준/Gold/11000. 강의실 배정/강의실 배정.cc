/*

Correctness? // To Do

Trial and Error)

Activity selection 문제와 마찬가지로 처음 finish time 기준으로 정렬 후 강의실 배정.

하지만 이 문제는 Start time 기준으로 정렬 후. finish time기준으로 강의실을 할당해야함.

간단하게 finish time 기준으로 강의실을 배정하면 다음과 같은 케이스의 반례가 존재함.

(9, 11), (2,10), (3,9)

finish time 기준 : (3,9), (2,10), (9,11),

필요한 강의실 갯수 => 1강의실 {7,8} 2강의실 {3,9}, 3강의실 {2,10} 총 3개

하지만 이 경우 필요한 최소 강의실은 1강의실 {2,10} 2 강의실 {3,9} {9,11} 총 2개

즉 finish time은 최적해를 보장해주지 않는다.
*/

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
    int s, f;
    cin >> s >> f;
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
