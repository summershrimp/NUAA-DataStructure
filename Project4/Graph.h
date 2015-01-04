#ifndef _GRAPH_H_
#define _GRAPH_H_
#include <vector>
#include <queue>

struct node {
	int u;
	int weight;
	int v;
	int next;
};

#define MaxPoints 30
class Graph
{
private:
	std::vector<int> Map;
	std::vector<node> Nodes;
	std::vector<int> dist;
	std::vector<int> path;
	int capaticy;
public:
	Graph() :Map(MaxPoints, -1), path(MaxPoints, 0), dist(MaxPoints, -1), capaticy(MaxPoints){};
	Graph(int n) :Map(n, -1),path(n, 0), dist(n, -1),capaticy(n){};
	void AddNode(int u, int v, int w)
	{
		node t;
		t.weight = w;
		t.v = v;
		t.next = Map[u];
		Nodes.push_back(t);
		Map[u] = (int )Nodes.size() - 1;
	}
	int FindMaxPath(int u, int v)
	{
		
		if (dist[u] == 0)
			return dist[v];
		dist[u] = 0;
		std::queue<int> q;
		q.push(u);
		while (!q.empty())
		{
			int ut = q.front();
			q.pop();
			int tnext = Map[ut];
			while (tnext != -1)
			{
				int v = Nodes[tnext].v;
				if (dist[v] < (dist[ut] + Nodes[tnext].weight))
				{
					dist[v] = (dist[ut] + Nodes[tnext].weight);
					path[v] = ut;
				}
				q.push(v);
				tnext = Nodes[tnext].next;
			}
		}
		int tp = v;
		while (tp != u)
		{
			printf("%d <-- %d\n", tp, path[tp]);
			tp = path[tp];
		}
		return dist[v];
	}
};

#endif
