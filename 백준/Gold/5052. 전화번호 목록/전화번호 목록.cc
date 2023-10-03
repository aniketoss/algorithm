#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

#define fi first
#define se second

#define _FR(...)  // freopen(__VA_ARGS__)
#define _PF(...) printf(__VA_ARGS__)

using namespace std;

typedef unsigned long long ull;

unordered_set<ull> wordList;

void init() { wordList.clear(); }

pair<ull, bool> getHashKey(string w, int mLen) {
  ull key = 0;
  for (int k = 0; k < mLen; k++) {
    key <<= 5;
    key |= (w[k] - '0' + 1);
    if (wordList.find(key) != wordList.end()) {
      return {key, false};
    }
  }
  return {key, true};
}

bool cmp4str(const string a, const string b) { return a < b; }

int main(void) {
  _FR("sample_input.txt", "r", stdin);
  int TC;
  scanf("%d", &TC);

  for (int i = 1; i <= TC; i++) {
    int n;
    scanf("%d", &n);
    init();
    vector<string> words;
    for (int j = 1; j <= n; j++) {
      char w[11];
      scanf("%s", &w);
      words.push_back(string(w));
    }
    sort(words.begin(), words.end(), cmp4str);

    bool flag = true;
    for (auto& word : words) {
      pair<ull, bool> key = getHashKey(word, word.size());
      if (!key.se) {
        flag = false;
        break;
      }
      wordList.insert(key.fi);
    }
    if (!flag) {
      printf("NO\n");
    } else {
      printf("YES\n");
    }
  }
  return 0;
}
