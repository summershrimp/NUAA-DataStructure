#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <stack>
#include <windows.h>
#include "UnionSet.h"
using namespace std;

vector<vector<int>> *map;
vector<vector<bool>> *visit;
const int LocX[4] = { 0, 1, 0, -1 };
const int LocY[4] = { 1, 0, -1, 0 };
enum Direction	{ UP, RIGHT, DOWN, LEFT };
struct Point
{
	int x, y;
};
void RamdomMap(int x, int y)
{
	system("cls");
	if (map != nullptr)
		delete map;
	map = new vector<vector<int>>(y + 2, vector<int>(x + 2, 0));
	visit = new vector<vector<bool>>(y + 2, vector<bool>(x + 2, 0));
	vector<vector<int>> &map = *::map;
	vector<vector<bool>> &map = *::map;
	UnionSet us;
	for (int j = 0; j <= y + 1; ++j)
	{
		for (int i = 0; i <= x + 1; ++i)
		{
			map[j][i] = rand() % 2;
			if (map[j][i]) us.Merge(j, i);
		}
	}

	while (!st.empty())
	{
		COORD pos = { 0, 0 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
		for (int j = 0; j <= y + 1; ++j)
		{
			for (int i = 0; i <= x + 1; ++i)
			{
				printf( "%d", map[j][i]);
			}
			printf("\n");
		}
		Point pt = st.top();
		printf("正在点(%d,%d)\n", pt.x, pt.y);
		
		if (pt.y == y && pt.x == x)
			break;
		int i = rand() % 4;
		switch (i)
		{
		case UP:printf("测试向↑走"); break;
		case DOWN:printf("测试向↓走"); break;
		case LEFT:printf("测试向←走"); break;
		case RIGHT:printf("测试向→走"); break;

		}
		Point ppush;
		ppush.x = pt.x + LocX[i];
		ppush.y = pt.y + LocY[i];
		if (!map[ppush.y][ppush.x] && ppush.x > 0 && ppush.x <= x && ppush.y > 0 && ppush.y <= y)
		{
			st.push(ppush);
			map[ppush.y][ppush.x] = 1;
			bool flag = false;
			
			if (flag)
			{
				map[ppush.y][ppush.x] = 0;
				st.pop();
				continue;
			}
		}
		Sleep(500);
	}
	
	FILE *fp = fopen("maze.map", "w");
	for (int j = 0; j <= y+1; ++j)
	{
		for (int i = 0; i <= x+1; ++i)
		{
			fprintf(fp,"%d", map[j][i]);
		}
		fprintf(fp, "\n");
	}
	fclose(fp);
}

int main(void)
{
	srand((unsigned int)time(NULL));
	int i, j;
	scanf("%d%d", &i, &j);
	RamdomMap(i, j);
}