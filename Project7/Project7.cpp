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
	map = new vector<vector<int>>(y*2 + 2, vector<int>(x*2 + 2, '-'));
	visit = new vector<vector<bool>>(y*2 + 2, vector<bool>(x*2 + 2, 0));
	vector<vector<int>> &map = *::map;
	vector<vector<bool>> &visit = *::visit;
	UnionSet us;
	int maxm = x*y;
	map[1][1] = 'S';
	for (int i = 0; i < x ;i++)
	for (int j = 0; j < y; j++)
	{
		map[i * 2 + 1][j * 2 + 1] = '*';
	}
	while (us.Find(1)!=us.Find(maxm))
	{
		int rx = (rand() % x);
		int ry = (rand() % y);
		int sx = rx+1;
		int sy = ry+1;
		rx = rx * 2 + 1;
		ry = ry * 2 + 1;
		//int count = 0;
		/*for (int i = 0; i < 4; i++)
		{
			if (map[ry + LocY[i]][rx + LocX[i]]) count++;
		}
		if (count >1)
				continue;*/
		int loc = rand() % 4;
		if ((ry + LocY[loc]<1 || ry + LocY[loc] > y*2+1) || (rx + LocX[loc]<1 || rx + LocX[loc] > x*2+1))
			continue;
		rx += LocX[loc];
		ry += LocY[loc];
		//map[ry][rx] = 1;
		//map[ry + LocY[loc]][rx + LocX[loc]] = 1;
		if (ry % 2 == 0)
		{
			if (us.Find(((sy - 1) + 1)*x + sx) == us.Find(((sy - 1) - 1)*x + sx))
				continue;
			map[ry][rx] = '0';
			us.Merge( (((sy - 1) + 1)*x + sx), ((sy - 1) - 1)*x + sx );
		}
		else
		{
			if ( us.Find( ((sy - 1)*x + sx + 1) ) == us.Find( ((sy - 1)*x + sx - 1) ) )
				continue;
			map[ry][rx] = '0';
			us.Merge(((sy - 1)*x + sx + 1), ((sy - 1)*x + sx - 1));
		}
		COORD pos = { 0, 0 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
		for (int j = 0; j <= y*2 + 1; ++j)
		{
			for (int i = 0; i <= x*2 + 1; ++i)
			{
				printf("%c", map[j][i]);
			}
			printf("\n");
		}
		printf("ÕýÔÚµã(%d,%d)\t\t\n", sx, sy);

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
	system("pause");
}

int main(void)
{
	srand((unsigned int)time(NULL));
	int i, j;
	scanf("%d%d", &i, &j);
	RamdomMap(i, j);
}