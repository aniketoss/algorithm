#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <unordered_map>

using namespace std;

#define _FR(...) // freopen(__VA_ARGS__)

#define RECOMMAND 1
#define ADD 2
#define SOLVED 3

#define MAX_SIZE 100
#define MAXPRO 111111

struct Problem {
  int mId;
  int mLevel;
} nodes[MAXPRO];
int nodeCnt;

struct cmp4pb {
  bool operator()(const Problem* a, const Problem* b) const {
    return a->mLevel != b->mLevel ? a->mLevel > b->mLevel : a->mId > b->mId;
  }
};

set<Problem*, cmp4pb> pbList;
unordered_map<int, Problem*> pbHash;

int N, M;

void init() {
  pbHash.clear();
  pbList.clear();
  nodeCnt = 0;
}

Problem* getNodes() {
  Problem* node = &nodes[++nodeCnt];
  node->mId = 0;
  node->mLevel = 0;
  return node;
}

void addProblem(int mId, int mLevel) {
  Problem* node = pbHash[mId];
  if (node) {
    pbList.erase(node);

    node->mId = mId;
    node->mLevel = mLevel;
    pbList.insert(node);
  } else {
    node = getNodes();
    node->mId = mId;
    node->mLevel = mLevel;

    pbList.insert(node);
    pbHash[mId] = node;
  }
}

void sovleProblem(int mId) {
  Problem* node = pbHash[mId];
  pbList.erase(node);
  pbHash.erase(mId);
}

int mystrcmp(char a[], char b[]) {
  while (*a && *a == *b) {
    *a++;
    *b++;
  }
  return *a - *b;
}

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(0);
  _FR("sample_input.txt", "r", stdin);
  cin >> N;
  int a[2];

  for (int i = 0; i < N; i++) {
    cin >> a[0] >> a[1];
    addProblem(a[0], a[1]);
  }

  cin >> M;

  string type;
  string cmd[3] = {"add", "solved", "recommend"};
  for (int i = 0; i < M; i++) {
    cin >> type;
    if (type.compare(cmd[0]) == 0) {
      cin >> a[0] >> a[1];
      addProblem(a[0], a[1]);
    } else if (type.compare(cmd[1]) == 0) {
      cin >> a[0];
      sovleProblem(a[0]);
    } else {
      cin >> a[0];
      if (a[0] == 1) {
        cout << (*pbList.begin())->mId << "\n";
      } else {
        cout << (*prev(pbList.end()))->mId << "\n";
      }
    }
  }
  return 0;
}
