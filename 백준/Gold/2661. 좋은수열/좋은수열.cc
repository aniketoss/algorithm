#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

#define _FR(...) // freopen(__VA_ARGS__)
#define fi first
#define se second
#define pb push_back
#define ppb pop_back

int N;
string result;

bool check(int len) {
  string suffix;
  for (int i = len - 1; i >= 0; i--) {
    suffix.pb(result[i]);
    string str;
    for (int j = i - 1; j >= 0; j--) {
      str.pb(result[j]);
      if (suffix.compare(str) == 0) return false;
    }
  }
  return true;
}

bool flag;
void dfs(int len) {
  if (len == N) {
    printf("%s\n", result.c_str());
    flag = true;
    return;
  }
  for (int i = 1; i <= 3; i++) {
    result.pb((i + '0'));
    if (check(len + 1) && !flag) dfs(len + 1);

    result.ppb();
  }
}

int main(void) {
  _FR("sample_input.txt", "r", stdin);
  scanf("%d", &N);
  flag = false;
  dfs(0);
  return 0;
}