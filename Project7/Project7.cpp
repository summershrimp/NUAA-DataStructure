#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <cstring>
#include <stack>
#include <windows.h>
#include "UnionSet.h"
using namespace std;

vector<vector<int>> *map = nullptr;
vector<vector<bool>> *visit = nullptr;
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
	map = new vector<vector<int>>(y*2 + 2, vector<int>(x*2 + 2, '0'));
	vector<vector<int>> &map = *::map;
	UnionSet us;
	int maxm = x*y;
	while (us.Find(1)!=us.Find(maxm))
	{
		int rx = (rand() % x)+1;
		int ry = (rand() % y)+1;
		rx = rx * 2 - 1;
		ry = ry * 2 - 1;
		int loc = rand() % 4;
		if ((ry + LocY[loc]<1 || ry + LocY[loc] > y*2-1) || (rx + LocX[loc]<1 || rx + LocX[loc] > x*2-1))
			continue;
		rx += LocX[loc];
		ry += LocY[loc];
		if (ry % 2 == 0)
		{
			int tx1 = rx / 2 + 1, tx2 = tx1;
			int ty1 = ry / 2, ty2 = ry / 2 + 1;
			if (us.Find((ty1 - 1)*x + tx1) == us.Find((ty2 - 1)*x + tx2))
				continue;
			map[ry][rx] = '1';
			map[ry - 1][rx] = '1';
			map[ry + 1][rx] = '1';

			us.Merge((ty1 - 1)*x + tx1, (ty2 - 1)*x + tx2);
		}
		else
		{
			int ty1 = (ry + 1) / 2, ty2 = ty1;
			int tx1 = rx / 2, tx2 = rx / 2 + 1;
			if (us.Find((ty1 - 1)*x + tx1) == us.Find((ty2 - 1)*x + tx2))
				continue;
			map[ry][rx] = '1';
			map[ry][rx - 1] = '1';
			map[ry][rx + 1] = '1';

			us.Merge((ty1 - 1)*x + tx1, (ty2 - 1)*x + tx2);
		}
		COORD pos = { 0, 0 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
		for (int j = 1; j < y*2 ; ++j)
		{
			for (int i = 1; i < x*2; ++i)
			{
				printf("%c", map[j][i]);
			}
			printf("\n");
		}
		//printf("正在点(%d,%d)\t\t\n", rx, ry);

	}
	
	FILE *fp = fopen("maze.map", "w");
	fprintf(fp,"%d %d\n", x * 2 - 1, y * 2 - 1);
	for (int j = 1; j < y*2; ++j)
	{
		for (int i = 1; i < x*2; ++i)
		{
			fprintf(fp,"%c ", map[j][i]);
		}
		fprintf(fp, "\n");
	}
	fclose(fp);
	delete ::map;
	::map = nullptr;
}

struct pos
{
	int x, y, step;
};
stack<pos> st;


void Solve(vector<vector<int>> &map)
{
	int y = map.size();
	int x = map[0].size();
	visit = new vector<vector<bool>>(y, vector<bool>(x, false));
	vector<vector<bool>> visit = *::visit;

	pos po;
	po.x = 0;
	po.y = 0;
	po.step = 1;
	st.push(po);
	while (!st.empty())
	{
		po = st.top();
		st.pop();
		map[po.y][po.x] = po.step;
		visit[po.y][po.x] = true;
		COORD poos = { 0, 0 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), poos);
		for (int j = 0; j < y ; ++j)
		{
			for (int i = 0; i < x; ++i)
			{
				printf("%2d ", map[j][i]);
			}
			printf("\n");
		}
		Sleep(10);
		printf("尝试点：%d,%d\n", po.x, po.y);
		if (po.y == y-1 && po.x == x-1)
			break;
		pos tp;
		if ((po.x - 1) >= 0 && map[po.y][po.x - 1] && !visit[po.y][po.x - 1])
		{
			tp.x = po.x - 1;
			tp.y = po.y;
			tp.step = po.step + 1;
			st.push(tp);
		}
		if ((po.y - 1) >= 0 && map[po.y - 1][po.x] && !visit[po.y - 1][po.x])
		{
			tp.y = po.y - 1;
			tp.x = po.x;
			tp.step = po.step + 1;
			st.push(tp);
		}
		if ((po.x + 1) < x  && map[po.y][po.x + 1] && !visit[po.y][po.x + 1])
		{
			tp.x = po.x + 1;
			tp.y = po.y;
			tp.step = po.step + 1;
			st.push(tp);
		}
		if ((po.y + 1) < y  && map[po.y + 1][po.x] && !visit[po.y + 1][po.x])
		{
			tp.x = po.x;
			tp.y = po.y + 1;
			tp.step = po.step + 1;
			st.push(tp);
		}
	}
	if (st.empty())
		printf("无路可走啊亲T_T\n");
	else
	{
		for (int i = 0; i < y; i++)
		{
			for (int j = 0; j < x; j++)
				visit[i][j] = false;
		}
		int curnum = map[x - 1][y - 1];
		po.x = x-1;
		po.y = y-1;
		while (curnum != 1)
		{
			visit[po.y][po.x] = true;
			COORD poos = { 0, y };
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), poos);
			printf("尝试点：%d,%d, 数字是:%d\n", po.x, po.y,map[po.y][po.x]);
			if ((po.x - 1) >= 0 && map[po.y][po.x - 1]==curnum-1 )
			{
				curnum--;
				po.x = po.x - 1;
			}
			else if ((po.y - 1) >= 0 && map[po.y - 1][po.x] == curnum - 1)
			{
				curnum--;
				po.y = po.y - 1;
			}
			else if ((po.x + 1) < x  && map[po.y][po.x + 1] == curnum - 1)
			{
				curnum--;
				po.x = po.x + 1;
			}
			else if ((po.y + 1) < y  && map[po.y + 1][po.x] == curnum - 1)
			{
				curnum--;
				po.y = po.y + 1;
			}
		}
		for (int i = 0; i < y; i++)
		{
			for (int j = 0; j < x; j++)
				if(map[i][j]&& !visit[i][j])
					map[i][j] = 1;
		}
		COORD poos = { 0, 0 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), poos);
		for (int j = 0; j < y; ++j)
		{
			for (int i = 0; i < x; ++i)
			{
				printf("%2d ", map[j][i]);
			}
			printf("\n");
		}
		printf("\t\t\t\t\t\n");
	}
}


int buf[100000];

int main(void)
{
	srand((unsigned int)time(NULL));
	int i, j;
	char c;
	printf("是否生成地图(y/N)：");
	scanf("%c", &c);
	getchar();
	if ('Y' == toupper(c))
	{
		printf("请输入两个大于5的奇数：");
		scanf("%d%d", &i, &j);
		while (i % 2 == 0 || j % 2 == 0)
		{
			printf("请输入两个大于5的奇数：");
			scanf("%d%d", &i, &j);
		}
		RamdomMap((i + 1) / 2, (j + 1) / 2);
	}
	FILE *fp = fopen("maze.map", "r");
	int x, y;
	fscanf(fp,"%d %d", &x, &y);
	if (map)
		delete map;
	map = new vector<vector<int>>(y, vector<int>(x, 0));
	vector<vector<int>> &map = *::map;
	for (int i = 0; i < y; i++)
	{
		for (int j = 0; j < x; j++)
		{
			fscanf(fp,"%d", &map[i][j]);
		}
	}

	Solve(map);

	system("pause");
}