#include <iostream>
#include <cstdio>
#include <algorithm>
#include <stdlib.h>
using namespace std;
typedef struct robot {
	int x;
	int y;
	int dir;
	int idx;
}robot; robot bot[111];
int R, C, N, M; int grid[111][111];
int dx[] = {0,-1,0,1}; // W, N, E, S;
int dy[] = {-1,0,1,0};
int change_dir(char type, int cur_dir)
{
	int next_dir = 0;
	if (type == 'R')
	{
		next_dir = (cur_dir + 4 + 1) % 4;
	}
	else if (type == 'L')
	{
		next_dir = (cur_dir + 4 - 1) % 4;
	}
	else
	{
		next_dir = cur_dir;
	}
	return next_dir;
}
void simulate_forward(robot &bot)
{
	int xx = bot.x + dx[bot.dir];
	int yy = bot.y + dy[bot.dir];
	if (xx <= R && xx >= 1 && yy <= C && yy >= 1)
	{
		if (grid[xx][yy] != bot.idx && grid[xx][yy] !=  0)
		{
			printf("Robot %d crashes into robot %d\n", bot.idx, grid[xx][yy]);
			exit(0);
		}
		else
		{
			grid[bot.x][bot.y] = 0;
			bot.x = xx;
			bot.y = yy;
			grid[xx][yy] = bot.idx;
		}
	}
	else
	{
		printf("Robot %d crashes into the wall\n", bot.idx);
		exit(0);
	}
}
void simulate_rotate(robot &bot, char type)
{
	bot.dir = change_dir(type, bot.dir);
}
int main(void) {
	//freopen("input.txt", "r", stdin);
	scanf("%d %d", &C, &R);
	scanf("%d %d", &N, &M);
	for (int i = 1; i <= N; i++)
	{
		char dir;
		scanf("%d %d %c", &bot[i].y, &bot[i].x, &dir);
		bot[i].x = R - bot[i].x + 1;
		bot[i].y = bot[i].y;
		grid[bot[i].x][bot[i].y] = i;
		bot[i].idx = i;
		if (dir == 'E') // 0: W, 1: N, 2: E, 3: S 
		{
			bot[i].dir = 2;
		}
		if (dir == 'W')
		{
			bot[i].dir = 0;
		}
		if (dir == 'N')
		{
			bot[i].dir = 1;
		}
		if (dir == 'S')
		{
			bot[i].dir = 3;
		}
	}
	for (int m = 1; m <= M; m++)
	{
		int bot_idx; char order; int iter;
		bool ret;
		scanf("%d %c %d", &bot_idx, &order, &iter);
		if (order == 'F') //앞으로 전진
		{
			for (int i = 1; i <= iter; i++)
			{
				simulate_forward(bot[bot_idx]);
			}
		}
		else // 좌측 혹은 우측으로 방향전환
		{
			for (int i = 1; i <= iter; i++)
			{
				simulate_rotate(bot[bot_idx], order);
			}
		}
	}
	printf("OK\n");
	return 0;
}