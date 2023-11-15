#include <algorithm>
#include <iostream>
#include <queue>
#include <tuple>
#pragma warning(disable: 4996)
#define MAX_N 101
#define MAX_M 101
#define MAX_H 101
int INF = -9999999;
int t[MAX_N][MAX_M][MAX_H];
int visit[MAX_N][MAX_M][MAX_H];
int dist[MAX_N][MAX_M][MAX_H];

int find_answer(int h,int n, int m) {
    int answer = INF;
    for (int i = 1; i <= h; i++) {
        for (int j = 1; j <= n; j++) {
            for (int k = 1; k <= m; k++) {
                if (visit[i][j][k] == 0) {
                    answer = -1;
                    return answer;
                }
                answer = std::max(answer, dist[i][j][k]);
            }
        }
    }
    return answer;
}

int main() {
    int n, m, h;

    int dx[6] = { 1, -1, 0, 0, 0, 0 };
    int dy[6] = { 0, 0, 1, -1, 0, 0 };
    int dz[6] = { 0, 0, 0, 0, -1, 1 };
    //           r, l, f, b, d, u
    scanf("%d %d %d", &m, &n, &h);
    for (int i = 1; i <= h; i++) {
        for (int j = 1; j <= n; j++) {
            for (int k = 1; k <= m; k++) {
                scanf("%d", &t[i][j][k]);
                dist[i][j][k] = 0;
                visit[i][j][k] = 0;
            }
        }
    }

    std::queue<std::tuple<int, int, int>> que;

    for (int i = 1; i <= h; i++) {
        for (int j = 1; j <= n; j++) {
            for (int k = 1; k <= m; k++) {
                if (t[i][j][k] == 1) {
                    que.push(std::make_tuple(i, j, k));
                    visit[i][j][k] = 1;
                    dist[i][j][k] = 0;
                }
                if (t[i][j][k] == -1) {
                    visit[i][j][k] = -1;
                    dist[i][j][k] = -1;
                }
            }
        }
    }

    while (!que.empty()) {
        int now_h, now_n, now_m;
        std::tie(now_h, now_n, now_m) = que.front();
        que.pop();
        for (int i = 0; i < 6; i++) {
            int next_n = now_n + dx[i];
            int next_m = now_m + dy[i];
            int next_h = now_h + dz[i];

            if (next_h >= 1 && next_h <= h && next_n >= 1 && next_n <= n &&
                next_m >= 1 && next_m <= m) {
                if (visit[next_h][next_n][next_m] != 1 &&
                    t[next_h][next_n][next_m] == 0) {
                    t[next_h][next_n][next_m] = 1;
                    visit[next_h][next_n][next_m] = 1;
                    dist[next_h][next_n][next_m] = dist[now_h][now_n][now_m] + 1;
                    que.push(std::make_tuple(next_h, next_n, next_m));
                }
            }
        }
    }

    printf("%d\n", find_answer(h,n,m));
    return 0;
}