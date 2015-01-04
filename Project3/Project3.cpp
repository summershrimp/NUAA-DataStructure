#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>
#include <algorithm>
#include <string>
#include <cstdio>
#include <bitset>
using namespace std;

struct TreeNode
{
	int Freq;
	char Chr;
	bool hasChr;
	string Word;
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
struct TreeNode Chars[128];

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
	for (int i = 0; i < 128; ++i)
	{
		Chars[i].Chr = i;
		Chars[i].Freq = 0;
		Chars[i].Word = "";
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
	for (int i = 0; i < 128; i++)
		q.push(Chars+i);
}

struct TreeNode *MakeHuff(priority_queue<struct TreeNode*, vector<struct TreeNode*>, NodeComp  > &q)
{
	TreeNode * t1, *t2, *t;
	while (1)
	{
		t1 = q.top();
		q.pop();
		while (!(t1->Freq > 0))
		{
			t1 = q.top();
			q.pop();
		};
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
int tt = 0;
void MakeDict(TreeNode *troot,string word,int deep)
{
	if (deep > tt)
		tt = deep;
	troot->Word = word;
	if(troot->LChild)
		MakeDict(troot->LChild,  word + "0",deep+1);
	if (troot->RChild)
		MakeDict(troot->RChild, word + "1" ,deep+1);
}
short dict[128];

void Compress()
{
	InitChars();
	char buf[128],buf2[128];
	printf("请输入要编码的文件名：");
	scanf("%s", buf);
	FILE *fp = fopen(buf, "r");
	CountChars(fp);
	fclose(fp);
	AddToQueue(q);
	TreeNode *root = MakeHuff(q);
	MakeDict(root, "", 0);

	printf("%d %d\n", tt, sizeof(short));
	fp = fopen(buf, "r");
	printf("请输入编码后的文件名：");
	scanf("%s", buf2);
	FILE *fw = fopen(buf2, "wb");
	char ch = fgetc(fp);
	int buff = 0;
	int cbuff = 0;
	while (!feof(fp))
	{
		string::iterator it = Chars[ch].Word.begin();
		while (it != Chars[ch].Word.end())
		{
			switch (*it)
			{
			case '0':
				buff = buff << 1;
				cbuff++;
				break;
			case '1':
				buff = (buff << 1) + 1;
				cbuff++;
				break;
			}
			if (cbuff == 32)
			{
				fwrite(&buff, sizeof(int), 1, fw);
				cbuff = 0;
			}
			it++;
		}
		ch = fgetc(fp);
	}
	if (cbuff != 0)
	{
		for (int i = cbuff; i <= 32; i++)
			buff = buff << 1;
		fwrite(&buff, sizeof(int), 1, fw);
	}
	fclose(fp);
	fclose(fw);
	fp = fopen(strcat(buf, ".dicdb"), "wb+");
	fwrite(Chars, sizeof(Chars), 1, fp);
	fclose(fp);

}
void Decompress()
{
	char fbuf[128];
	printf("请输入需要解密的文件名:");
	scanf("%s", fbuf);
	string fdic(fbuf);
	FILE *dic = fopen((fdic+".dicdb").c_str(), "rb");
	fread(Chars, sizeof(Chars), 1, dic);
	fclose(dic);
	FILE *fr = fopen(fbuf, "rb");
	printf("请输入存放解密后的文件名:");
	scanf("%s", fbuf);
	FILE *fw = fopen(fbuf, "w+");

	AddToQueue(q);
	TreeNode *root = MakeHuff(q);
	MakeDict(root, "", 0);


	int cs;
	fread(&cs, sizeof(short), 1, fr);
	while (!feof(fr))
	{
		for (int i = 0; i < 128; i++)
			if (dict[i] == cs)
				fputc(i, fw);
		fread(&cs, sizeof(short), 1, fr);
	}
	fclose(fr);
	fclose(fw);
}
int main(void)
{
	Compress();
	//Decompress();
	system("pause");
	return 0;
}