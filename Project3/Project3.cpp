#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>
#include <algorithm>
#include <cstdio>
using namespace std;

struct TreeNode
{
	int Freq;
	unsigned char Chr;
	bool hasChr;
	struct TreeNode *LChild;
	struct TreeNode *RChild;
	bool operator < (struct TreeNode & rhs)
	{
		return(this->Freq < rhs.Freq);
	}
	bool operator > (struct TreeNode & rhs)
	{
		return(this->Freq > rhs.Freq);
	}
};
struct TreeNode Chars[256];

struct NodeComp
{
	bool operator () ( TreeNode*& left, TreeNode*& right) const
	{
		return left->Freq > right->Freq;
	}
};

priority_queue<struct TreeNode*, vector<struct TreeNode*>, NodeComp > q;

void InitChars()
{
	for (int i = 0; i < 256; ++i)
	{
		Chars[i].Chr = i;
		Chars[i].Freq = 0;
		Chars[i].hasChr = true;
		Chars[i].LChild = nullptr;
		Chars[i].RChild = nullptr;
	}
}

void CountChars(FILE *fp)
{
	unsigned char t;
	t = fgetc(fp);
	while (!feof(fp))
	{
		Chars[t].Freq++;
		t = fgetc(fp);
	}
}
void AddToQueue(priority_queue<struct TreeNode*, vector<struct TreeNode*>,NodeComp > &q)
{
	for (int i = 0; i < 256; i++)
		q.push(Chars+i);
}

struct TreeNode *MakeHuff(priority_queue<struct TreeNode*, vector<struct TreeNode*>, NodeComp  > &q)
{
	TreeNode * t1, *t2, *t;
	while (1)
	{
		t1 = q.top();
		q.pop();
		t2 = q.top();
		q.pop();
		t = new TreeNode;
		t->LChild = t1;
		t->RChild = t2;
		t->hasChr = false;
		t->Freq = t1->Freq + t2->Freq;
		t->Chr = 0;
		if (q.empty())
			break;
		q.push(t);
	}
	return t;
}

int main(void)
{
	InitChars();
	char buf[128];
	printf("请输入要编码的文件名：");
	scanf("%s",buf);
	FILE *fp = fopen(buf, "r");
	CountChars(fp);
	AddToQueue(q);
	TreeNode *root = MakeHuff(q);
	system("pause");
	return 0;
}