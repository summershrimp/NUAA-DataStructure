#define _CRT_SECURE_NO_WARNINGS
#include "Graph.h"
#include <cstdio>
#include <cstdlib>

using namespace std;

Graph g;

int main(void)
{
	FILE *fp = fopen("map.txt", "r");
	node t;
	fscanf(fp,"%d%d%d", &t.u, &t.v, &t.weight);
	while (!feof(fp))
	{
		g.AddNode(t.u, t.v, t.weight);
		fscanf(fp, "%d%d%d", &t.u, &t.v, &t.weight);
	}
	scanf("%d%d", &t.u, &t.v);
	printf("%d",g.FindMaxPath(t.u, t.v));
	system("pause");

}
