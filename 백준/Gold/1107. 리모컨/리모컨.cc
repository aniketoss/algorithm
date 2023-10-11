#include <memory.h>

#include <algorithm>
#include <climits>
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

#define _FR(...) //freopen(__VA_ARGS__)

#define pb push_back

#define MAXN (999999)
int N, M;

int arr[MAXN];
vector<bool> buttons(12);

int check(int chan) {
  int push = 0;
  if (chan == 0) {
    return buttons[chan] ? 0 : 1;
  }
  while (chan > 0) {
    if (buttons[chan % 10]) return 0;
    chan /= 10;
    push++;
  }
  return push;
}

int main(void) {
  _FR("sample_input.txt", "r", stdin);
  scanf("%d", &N);
  scanf("%d", &M);
  for (int i = 0; i < M; i++) {
    int num;
    scanf("%d", &num);
    buttons[num] = true;
  }
  for (int i = 0; i <= 999999; i++) {
    arr[i] = abs(100 - i);
  }
  int minValue = INT_MAX;
  for (int i = 0; i <= 999999; i++) {
    int result = check(i);
    if (result) {
      result += abs(N - i);
    } else {
      continue;
    }
    minValue = min(minValue, result);
  }
  printf("%d\n", min(arr[N], minValue));
  return 0;
}