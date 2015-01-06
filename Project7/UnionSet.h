#ifndef _UNIONSET_H_
#define _UNIONSET_H_
#include <vector>
class UnionSet
{
private:
	std::vector<int> Fa;
public:
	UnionSet(){}
	void Init(int n)
	{
		for (int i = Fa.size(); i <= n; ++i)
			Fa.push_back(i);
	}
	int Find(int u)
	{
		if (Fa.size() <= u)
			Init(u);
		while (u != Fa[u])
			return Fa[u] = Find(Fa[u]);
		return u;
	}
	bool Same(int x, int y)
	{
		return (Find(x) == Find(y));
	}
	int Merge(int x, int y)
	{
		x = Find(x);
		y = Find(y);
		Fa[y] = x;
		return x;
	}
	int MakeEmpty()
	{
		for (int i = 0; i < Fa.size(); ++i)
			Fa[i] = i;
	}
};

#endif