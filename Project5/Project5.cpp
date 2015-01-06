#include <cstdio>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <string>
#include "LineHash.h"
#include "LinkHash.h"
using namespace std;

struct name_card
{
	string ID, name, address;
	friend ifstream &operator>>(ifstream &  rhs,name_card &n)
	{
		rhs >> n.ID >> n.name >> n.address;
		return rhs;
	}
	friend ostream &operator<<(ostream &  rhs, name_card &n)
	{
		rhs << n.ID << ' ' << n.name << ' ' << n.address;
		return rhs;
	}
	bool operator == (name_card rhs)
	{
		return (ID == rhs.ID);
	}
};

LineHash<name_card> *linehash;
LinkHash<name_card> *linkhash;

ifstream fin;

int hashfunc(name_card t, int n)
{
	unsigned int seed = 131;
	unsigned int hash = 0;
	string::iterator it = t.ID.begin();
	while (it != t.ID.end())
	{
		hash = hash * seed + *it;
		++it;
	}
	cout << "��" << t.ID << "��hash�����:" << hash%n<<endl;
	return hash % n;
}

void Line(int n)
{
	linehash = new LineHash<name_card>(n);
	LineHash<name_card> &linehash = *::linehash;
	linehash.setHashFunc(hashfunc);
	name_card nc;
	fin >> nc;
	while (!fin.eof())
	{
		if (linehash.add(nc) == -1) break;
		fin >> nc;
	}
	cin >> nc.ID;
	while (nc.ID != "0")
	{
		cout << *linehash.Find(nc)<<endl;
		cin >> nc.ID;
	}
}

void Link(int n)
{
	linkhash = new LinkHash<name_card>(n);
	LinkHash<name_card> &linkhash = *::linkhash;
	linkhash.setHashFunc(hashfunc);
	name_card nc;
	fin >> nc;
	while (!fin.eof())
	{
		if(linkhash.add(nc) == -1) break ;
		fin >> nc;
	}
	cin >> nc.ID;
	while (nc.ID != "0")
	{
		cout << *linkhash.Find(nc)<<endl;
		cin >> nc.ID;
	}
}


int main(void)
{
	fin.open("namecard.txt");
	char c;
	int n;
	cout << "������hash��Ĵ�С��";
	cin >> n;
	cout << "������ʹ�õĳ�ͻ�����ʽ��1. ����̽�� 2. ��ʽ����";
	cin >> c;
	switch (c)
	{
	case '1':
		Line(n);
		break;
	case '2':
		Link(n);
		break;
	default:
		break;
	}
	
}