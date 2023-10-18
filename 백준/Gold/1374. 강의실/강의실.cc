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