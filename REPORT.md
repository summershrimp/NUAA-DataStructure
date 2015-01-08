#数据结构课程设计报告

- 班级：1613204
- 学号：161320224
- 姓名：张一白
- 成绩：
- 指导教师：秦小麟

##1. 日程计划管理系统
###数据结构
线性表(链表)
###算法设计思想
使用三个线性表分别储存未进行，进行中和已结束的任务。线性表中的元素按照开始时间的先后顺序排列。初始时所有元素均在未进行任务列表中。程序中主线程处理事务的添加删除等操作，另有一个独立的线程检测未完成列表和进行中列表中是否有新任务开始或有进行中任务结束。并调用相应的函数完成元素的移动。
###源程序：
```C++
//Project1.cpp
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <windows.h>
#include <time.h>
#include "Calendar.h"

using namespace std;

Calendar income, run, past;
HANDLE hCheck;

void showMenu(int n);
void addPlan();
void showPast();
void showRun();
void showIncome();
void showIncomeByDay();
void showIncomeByWeek();
void showIncomeByMonth();
void writeToFile();
void readFromFile();
DWORD WINAPI CheckCalendar(LPVOID lp);

int main(void)
{
	printf("%d", sizeof(item));
	struct paramThread tp;
	tp.income = &income;
	tp.past = &past;
	tp.run = &run;
	hCheck = CreateThread(NULL, 0, CheckCalendar, &tp, 0, NULL);
	int input;
	readFromFile();
	while (1)
	{
		system("cls");
		showMenu(0);
		scanf("%d", &input);
		switch (input)
		{
		case 1:
			addPlan();
			system("pause");
			break;
		case 2:
			showPast();
			system("pause");
			break;
		case 3:
			showRun();
			system("pause");
			break;
		case 4:
			showIncome();
			break;
		case 99:
			writeToFile();
			return 0;
		}
	}
	return 0;
}

void writeToFile()
{
	FILE *fp = fopen("plans.db", "wb+");
	if (!fp)
		return;
	item *p = income;
	while (p)
	{
		fwrite(p, sizeof(item), 1, fp);
		p = p->next;
	}
	p = run;
	while (p)
	{
		fwrite(p, sizeof(item), 1, fp);
		p = p->next;
	}
	p = past;
	while (p)
	{
		fwrite(p, sizeof(item), 1, fp);
		p = p->next;
	}
	fclose(fp);
}

void readFromFile()
{
	FILE *fp = fopen("plans.db", "rb");
	if (!fp)
		return;
	item i;
	fread(&i, sizeof(item), 1, fp);
	while (!feof(fp))
	{
		addItem(&income, i);
		fread(&i, sizeof(item), 1, fp);
	}
	fclose(fp);
	checkRemender(income, run, past);
}

DWORD WINAPI CheckCalendar(LPVOID lp)
{
	struct paramThread *p = (struct paramThread *)lp;
	while (1)
	{
		checkItem(p->income, p->run, p->past);
		checkRemender(*(p->income), *(p->run), *(p->past));
		Sleep(1000);
	}
	return 0;
}

void addPlan()
{
	system("cls");
	item i;
	struct tm t;
	int year, mon, day, hh, mm, ss;
	system("cls");
	printf("请输入计划ID:");
	scanf("%d", &(i.ID));
	printf("请输入开始时间，格式为 年-月-日 时:分:秒 \n");
	scanf("%d-%d-%d %d:%d:%d", &year, &mon, &day, &hh, &mm, &ss);
	t.tm_year = year - 1900;
	t.tm_mon = mon - 1;
	t.tm_mday = day;
	t.tm_hour = hh;
	t.tm_min = mm;
	t.tm_sec = ss;
	i.startTime = mktime(&t);
	printf("请输入结束时间，格式为 年-月-日 时:分:秒 \n");
	scanf("%d-%d-%d %d:%d:%d", &year, &mon, &day, &hh, &mm, &ss);
	t.tm_year = year - 1900;
	t.tm_mon = mon - 1;
	t.tm_mday = day;
	t.tm_hour = hh;
	t.tm_min = mm;
	t.tm_sec = ss;
	i.endTime = mktime(&t);
	printf("请输入提醒时间，格式为 年-月-日 时:分:秒 \n");
	scanf("%d-%d-%d %d:%d:%d", &year, &mon, &day, &hh, &mm, &ss);
	t.tm_year = year - 1900;
	t.tm_mon = mon - 1;
	t.tm_mday = day;
	t.tm_hour = hh;
	t.tm_min = mm;
	t.tm_sec = ss;
	i.remenderTime = mktime(&t);
	printf("请输入计划名称：");
	scanf("%s", i.name);
	printf("请输入同行人员：");
	scanf("%s", i.people);
	printf("请输入去往地点：");
	scanf("%s", i.location);
	i.alreadyReminded = false;
	addItem(&income,i);
	printf("添加成功！");
}
void showPast()
{
	system("cls");
	Calendar t = past;
	while (t)
	{
		printf("名称：\t%s\n开始时间：\t%s结束时间：\t%s事件名：\t%s\n同行人员：\t%s\n地点：\t%s\n提醒时间：\t%s",
			t->name, ctime(&t->startTime), ctime(&t->endTime), t->name, t->people, t->location, ctime(&t->remenderTime));
		t = t->next;
	}
}
void showRun()
{
	system("cls");
	Calendar t = run;
	while (t)
	{
		printf("名称：\t%s\n开始时间：\t%s结束时间：\t%s事件名：\t%s\n同行人员：\t%s\n地点：\t%s\n提醒时间：\t%s",
			t->name, ctime(&t->startTime), ctime(&t->endTime), t->name, t->people, t->location, ctime(&t->remenderTime));
		t = t->next;
	}
}
void showIncome()
{
	system("cls");
	showMenu(4);
	int choice;
	scanf("%d",&choice);
	switch (choice)
	{
	case 1:
		showIncomeByDay();
		system("pause");
		break;
	case 2:
		showIncomeByWeek();
		system("pause");
		break;
	case 3:
		showIncomeByMonth();
		system("pause");
		break;
	default:
		break;
	}
}
void showIncomeByDay()
{
	system("cls");
	Calendar t = income;
	time_t tt = time(nullptr);
	struct tm *tn = localtime(&tt);
	struct tm *ti;
	while (t)
	{
		ti = localtime(&(t->startTime));
		if (tn->tm_year == ti->tm_year && ti->tm_mon == tn->tm_mon && ti->tm_mday == tn->tm_mday)
		{
			printf("名称：\t%s\n开始时间：\t%s结束时间：\t%s事件名：\t%s\n同行人员：\t%s\n地点：\t%s\n提醒时间：\t%s",
				t->name, ctime(&t->startTime), ctime(&t->endTime), t->name, t->people, t->location, ctime(&t->remenderTime));
		}
		t = t->next;
	}
}
void showIncomeByWeek()
{
	system("cls");
	Calendar t = income;
	time_t tt = time(nullptr);
	struct tm *tn = localtime(&tt);
	struct tm *ti;
	while (t)
	{
		ti = localtime(&(t->startTime));
		if (tn->tm_year == ti->tm_year && ti->tm_mon == tn->tm_mon && (ti->tm_mday - ti->tm_wday )<=( tn->tm_mday - tn->tm_wday + 7))
		{
			printf("名称：\t%s\n开始时间：\t%s结束时间：\t%s事件名：\t%s\n同行人员：\t%s\n地点：\t%s\n提醒时间：\t%s",
				t->name, ctime(&t->startTime), ctime(&t->endTime), t->name, t->people, t->location, ctime(&t->remenderTime));
		}
		t = t->next;
	}
}
void showIncomeByMonth()
{
	system("cls");
	Calendar t = income;
	time_t tt = time(nullptr);
	struct tm *tn = localtime(&tt);
	struct tm *ti;
	while (t)
	{
		ti = localtime(&(t->startTime));
		if (tn->tm_year == ti->tm_year && ti->tm_mon == tn->tm_mon)
		{
			printf("名称：\t%s\n开始时间：\t%s结束时间：\t%s事件名：\t%s\n同行人员：\t%s\n地点：\t%s\n提醒时间：\t%s",
				t->name, ctime(&t->startTime), ctime(&t->endTime), t->name, t->people, t->location, ctime(&t->remenderTime));
		}
		t = t->next;
		free(ti);
	}
}
void showMenu(int n)
{
	system("cls");
	switch (n)
	{
	case 4:
		printf("未开始计划查询\n");
		printf("1. 当天\n");
		printf("2. 本周\n");
		printf("3. 本月\n");
		printf("99.返回\n");
		printf("请输入您的选择：");
		break;
	default:
		printf("日历管理系统\n");
		printf("1. 添加计划\n");
		printf("2. 查看已结束计划\n");
		printf("3. 查看正在进行计划\n");
		printf("4. 查询未开始计划\n");
		printf("99.退出\n");
		printf("请输入您的选择：");
		break;
	}
}

//Calendar.h
#ifndef _CALENDAR_H_
#define _CALENDAR_H_
#include <time.h>
typedef struct item_int item, *Calendar;

struct paramThread
{
	Calendar *income, *run, *past;
};

struct item_int
{
	int ID;
	time_t startTime;
	time_t endTime;
	char name[64];
	char people[64];
	char location[64];
	time_t remenderTime;
	bool alreadyReminded = false;
	item *next;
	item *prev;
};
void initCalendar(Calendar * c);
void addItem(Calendar *c, item it);
void checkItem(Calendar *income, Calendar *run, Calendar *past);
void checkRemender(Calendar income, Calendar run, Calendar past);
void moveItem(Calendar *ci, item *i, Calendar * c);
#endif
//Calendar.cpp
#define _CRT_SECURE_NO_WARNINGS
#include "Calendar.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
void initCalendar(Calendar * c)
{
	*c = nullptr;
}
void addItem(Calendar *c, item it)
{
	item *t = (item *)malloc(sizeof(item));
	memcpy(t, &it, sizeof(item));
	if ((*c) == nullptr)
	{
		(*c) = t;
		(*c)->next = nullptr;
		(*c)->prev = nullptr;
		return;
	}
	Calendar cc = *c;
	while (cc->next != nullptr)
	{
		if (cc->startTime > t->startTime)
			break;
		cc = cc->next;
	}
	if (cc->next != nullptr)
	{
		t->next = cc;
		t->prev = cc->prev;
		cc->prev = t;
	}
	else
	{
		if (cc->startTime < t->startTime)
		{
			t->next = NULL;
			t->prev = cc;
			cc->next = t;
		}
		else
		{
			t->next = cc;
			t->prev = cc->prev;
			cc->prev = t;
		}
	}
	while ((*c)->prev)
		(*c) = (*c)->prev;
}
void moveItem(Calendar *ci ,item *i, Calendar * c)
{
	if (i->prev)
		i->prev->next = i->next;
	if (i->next)
		i->next->prev = i->prev;
	if (i == *ci)
		(*ci) = i->next;
	if ((*c) == nullptr)
	{
		(*c) = i;
		(*c)->next = nullptr;
		(*c)->prev = nullptr;
		return;
	}
	Calendar cc = *c;
	while (cc->next != nullptr)
	{
		if (cc->startTime > i->startTime)
			break;
		cc = cc->next;
	}
	if (cc->next != nullptr)
	{
		i->next = cc;
		i->prev = cc->prev;
		cc->prev = i;
	}
	else
	{
		if (cc->startTime <= i->startTime)
		{
			i->next = NULL;
			i->prev = cc;
			cc->next = i;
		}
		else
		{
			i->next = cc;
			i->prev = cc->prev;
			cc->prev = i;
		}
	}
	while ((*c)->prev)
		(*c) = (*c)->prev;
}
void checkItem(Calendar *income, Calendar *run, Calendar *past)
{
	time_t timeNow = time(nullptr);
	item *p = *income;
	while (p)
	{
		if (p->startTime <= timeNow)
		{
			printf("有新事件开始了！\n名称：\t%s\n开始时间：\t%s结束时间：\t%s事件名：\t%s\n同行人员：\t%s\n地点：\t%s\n提醒时间：\t%s",
				p->name, ctime(&p->startTime), ctime(&p->endTime), p->name, p->people, p->location,ctime(&p->remenderTime) );
			moveItem(income,p,run);
		}
		p = p->next;
	}
	p = *run;
	while (p)
	{
		if (p->endTime <= timeNow)
		{
			printf("有新事件结束了！\n名称：\t%s\n开始时间：\t%s结束时间：\t%s事件名：\t%s\n同行人员：\t%s\n地点：\t%s\n提醒时间：\t%s",
				p->name, ctime(&p->startTime), ctime(&p->endTime), p->name, p->people, p->location, ctime(&p->remenderTime));
			moveItem(run, p, past);
		}
		p = p->next;
	}
}

void checkRemender(Calendar income, Calendar run, Calendar past)
{
	time_t timeNow = time(nullptr);
	while (income)
	{
		if (income->remenderTime <= timeNow && !income->alreadyReminded)
		{
			income->alreadyReminded = true;
			printf("有新事件提醒！\n名称：\t%s\n开始时间：\t%s结束时间：\t%s事件名：\t%s\n同行人员：\t%s\n地点：\t%s\n提醒时间：\t%s",
				income->name, ctime(&income->startTime), ctime(&income->endTime), income->name, income->people, income->location, ctime(&income->remenderTime));
		}
		income = income->next;
	}
	while (run)
	{
		if (run->remenderTime <= timeNow && !run->alreadyReminded)
		{
			run->alreadyReminded = true;
			printf("有新事件提醒！\n名称：\t%s\n开始时间：\t%s结束时间：\t%s事件名：\t%s\n同行人员：\t%s\n地点：\t%s\n提醒时间：\t%s",
				run->name, ctime(&run->startTime), ctime(&run->endTime), run->name, run->people, run->location, ctime(&run->remenderTime));
		}
		run = run->next;
	}
	while (past)
	{
		if (past->remenderTime <= timeNow && !past->alreadyReminded)
		{
			past->alreadyReminded = true;
			printf("有新事件提醒！\n名称：\t%s\n开始时间：\t%s结束时间：\t%s事件名：\t%s\n同行人员：\t%s\n地点：\t%s\n提醒时间：\t%s",
				past->name, ctime(&past->startTime), ctime(&past->endTime), past->name, past->people, past->location, ctime(&past->remenderTime));
		}
		past = past->next;
	}
}
```

###测试数据和结果：
![](http://lairenla.qiniudn.com/dspicimage1.png)
![](http://lairenla.qiniudn.com/dspicimage2.png)
 
###时间复杂度：O(n)
 
##2. 算术表达式求值
###数据结构：串和栈
###算法设计思想：
####先将中缀表达式转换为后缀表达式再对后缀表达式求值
1. 初始化一个空堆栈，将结果字符串变量置空。
2. 从左到右读入中缀表达式，每次一个字符。
3. 如果字符是操作数，将它添加到结果字符串。
4. 如果字符是个操作符，弹出（pop）操作符，直至遇见开括号（opening parenthesis）、优先级较低的操作符或者同一优先级的右结合符号。把这个操作符压入（push）堆栈。
5. 如果字符是个开括号，把它压入堆栈。
6. 如果字符是个闭括号（closing parenthesis），在遇见开括号前，弹出所有操作符，然后把它们添加到结果字符串。
7. 如果到达输入字符串的末尾，弹出所有操作符并添加到结果字符串。
####后缀表达式求值
对后缀表达式求值比直接对中缀表达式求值简单。在后缀表达式中，不需要括号，而且操作符的优先级也不再起作用了。您可以用如下算法对后缀表达式求值：
1. 初始化一个空堆栈
2. 从左到右读入后缀表达式
3. 如果字符是一个操作数，把它压入堆栈。
4. 如果字符是个操作符，弹出两个操作数，执行恰当操作，然后把结果压入堆栈。如果您不能够弹出两个操作数，后缀表达式的语法就不正确。
5. 到后缀表达式末尾，从堆栈中弹出结果。若后缀表达式格式正确，那么堆栈应该为空。

###源程序：

```
#include<iostream>
using namespace std;

int compvalue(char expr[], double *n);
int tran(char str[], char expr[]);

int main()
{
	char str[100];
	char expr[100];
	double n;
	cout << "输入算术表达式:" << endl;
	cin >> str;
	while (strcmp(str, "##"))
	{
		char *p = str;
		while (*p != '#') p++;
		p++;
		char *p2 = p + 1;
		while (*p2 != '#') p2++;
		*p2 = 0;
		if (tran(p, expr) == 0)
			cout << "原算术表达式不正确!" << endl;
		else
		{
			if (compvalue(expr, &n) == 1)
				cout << "表达式求值:" << endl << n << endl;
			else
				cout << "计算错误!" << endl;
		}
		//cout << expr << endl;
		cin >> str;
	}
	return 0;
}

int tran(char str[], char expr[])
{
	int st[100];
	char ch;
	int i = 0, exindex = 0, stindex = -1;
	while ((ch = str[i++]) != '\0')
	{
		if (ch >= '0' && ch <= '9' || ch == '.')
		{
			expr[exindex] = ch;
			exindex++;
			while ((ch = str[i++]) != '\0' && (ch >= '0' && ch <= '9' || ch == '.'))
			{
				expr[exindex] = ch;
				exindex++;
			}
			i--;
			expr[exindex] = '#';
			exindex++;
		}
		else if (ch == '(')
		{
			stindex++;
			st[stindex] = ch;
		}
		else if (ch == ')')
		{
			while (st[stindex] != '(')
			{
				expr[exindex] = st[stindex];
				stindex--;
				exindex++;
			}
			stindex--;
		}
		else if (ch == '+' || ch == '-')
		{
			while (stindex >= 0 && st[stindex] != '(')
			{
				expr[exindex] = st[stindex];
				stindex--;
				exindex++;
			}
			stindex++;
			st[stindex] = ch;
		}
		else if (ch == '*' || ch == '/')
		{
			while (st[stindex] == '*' || st[stindex] == '/')
			{
				expr[exindex] = st[stindex];
				stindex--;
				exindex++;
			}
			stindex++;
			st[stindex] = ch;
		}
	}
	while (stindex >= 0)
	{
		expr[exindex] = st[stindex];
		exindex++;
		stindex--;
	}
	expr[exindex] = '\0';
	return 1;
}

int compvalue(char expr[], double *n)
{
	double st[100];
	double d;
	char ch;
	int exindex = 0, stindex = -1;
	while ((ch = expr[exindex++]) != '\0')
	{
		if (ch >= '0'&&ch <= '9' || ch == '.')
		{
			d = 0.0;
			do
			{
				d = 10.0 * d + ch - '0';
				ch = expr[exindex++];
			} while ((ch != '#') && ch != '.');
			if (ch == '.')
			{
				int exp = 10;
				while ((ch = expr[exindex++]) != '#')
				{
					d += (ch - '0') / (double)exp;
					exp *= 10;
				}
			}
			stindex++;
			st[stindex] = d;
		}
		else
		{
			switch (ch)
			{
			case'+':st[stindex - 1] = st[stindex - 1] + st[stindex];
				break;
			case'-':st[stindex - 1] = st[stindex - 1] - st[stindex];
				break;
			case'*':st[stindex - 1] = st[stindex - 1] * st[stindex];
				break;
			case'/':
				if (st[stindex] != 0)
				{
					st[stindex - 1] = st[stindex - 1] / st[stindex];
				}
				else return 0;
				break;
			}
			stindex--;
		}
	}
	(*n) = st[stindex];
	return 1;
}
```

###测试数据和结果：
![](http://lairenla.qiniudn.com/dspicimage3.png)
###时间复杂度：O(n)

 
##3. Huffman编码与解码
###数据结构
二叉树
###算法设计思想

1. 对给定的n个权值{W1,W2,W3,...,Wi,...,Wn}构成n棵二叉树的初始集合F= {T1,T2,T3,...,Ti,...,Tn}，其中每棵二叉树Ti中只有一个权值为Wi的根结点，它的左右子树均为空。（为方便在计算机上实现算 法，一般还要求以Ti的权值Wi的升序排列。）
2. 在F中选取两棵根结点权值最小的树作为新构造的二叉树的左右子树，新二叉树的根结点的权值为其左右子树的根结点的权值之和。
3. 从F中删除这两棵树，并把这棵新的二叉树同样以升序排列加入到集合F中。
4. 重复二和三两步，直到集合F中只有一棵二叉树为止。
 
###源程序：
```
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
	unsigned char ch = fgetc(fp);
	int buff = 0;
	int cbuff = 0;
	int allbuff = 0;
	while (!feof(fp))
	{
		putchar(ch);
		cout <<' '<< Chars[ch].Word<<endl;
		string::iterator it = Chars[ch].Word.begin();
		while (it != Chars[ch].Word.end())
		{
			switch (*it)
			{
			case '0':
				buff = buff << 1;
				cbuff++;
				allbuff++;
				break;
			case '1':
				buff = (buff << 1) + 1;
				cbuff++;
				allbuff++;
				break;
			}
			if (cbuff == 32)
			{
				fwrite(&buff, sizeof(int), 1, fw);
				fflush(fw);
				cbuff = 0;
				buff = 0;
			}
			it++;
		}
		ch = fgetc(fp);
	}
	if (cbuff != 0)
	{
		for (int i = cbuff; i < 32; i++)
			buff = buff << 1;
		fwrite(&buff, sizeof(int), 1, fw);
	}
	fclose(fp);
	fclose(fw);
	fp = fopen(strcat(buf2, ".dicdb"), "wb+");
	fwrite(Chars, sizeof(Chars), 1, fp);
	fwrite(&allbuff, sizeof(int), 1, fp);
	fclose(fp);

}
void Decompress()
{
	char fbuf[128];
	int allbuff;
	printf("请输入需要解密的文件名:");
	scanf("%s", fbuf);
	string fdic(fbuf);
	FILE *dic = fopen((fdic+".dicdb").c_str(), "rb");
	cout <<"dic read count:"<<fread(Chars, sizeof(TreeNode), 256, dic)<<endl;
	fread(&allbuff, sizeof(int), 1, dic);
	fclose(dic);
	FILE *fr = fopen(fbuf, "rb");
	printf("请输入存放解密后的文件名:");
	scanf("%s", fbuf);
	FILE *fw = fopen(fbuf, "w+");

	AddToQueue(q);
	TreeNode *root = MakeHuff(q);
	MakeDict(root, "", 0);

	TreeNode *tn = root;
	unsigned int cs;
	fread(&cs, sizeof(unsigned int), 1, fr);
	while (!feof(fr))
	{
		int t;
		bool endflag = false;
		for (int i = 31; i >= 0; --i)
		{
			if (i == 31)
				t = cs >> 31;
			else
				t = (cs >> i) - ((cs >> (i + 1)) << 1);
			switch (t)
			{
			case 0:
				if(tn->LChild)
					tn = tn->LChild;
				break;
			case 1:
				if(tn->RChild)
					tn = tn->RChild;
				break;
			}
			if (tn->hasChr)
			{
				fputc(tn->Chr, fw);
				fflush(fw);
				tn = root;
			}
			allbuff--;
			if (allbuff == 0)
			{
				endflag = true;
				break;
			}
		}
		if (endflag) break;
		fread(&cs, sizeof(unsigned int ), 1, fr);
	}
	fclose(fr);
	fclose(fw);
}
int main(void)
{
	printf("请选择压缩或解压(c/压缩，d/解压):");
	char c;
	scanf("%c",&c);
	switch (c)
	{
	case 'c':
		Compress();
		break;
	case 'd':
		Decompress();
		break;
	}

	system("pause");
	return 0;
}
```

###测试数据和结果：
![](http://lairenla.qiniudn.com/dspicimage4.png)
![](http://lairenla.qiniudn.com/dspicimage5.png)
 
###时间复杂度：
压缩：O(nlogn + n) 解压：O(nlogn)
 
##4.关键路径问题
###数据结构
图
###算法设计思想
通过宽度优先搜索找到两点间的最长路
###源程序：
```
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

//Graph.h
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
```

###测试数据和结果：
![](http://lairenla.qiniudn.com/dspicimage6.png)
![](http://lairenla.qiniudn.com/dspicimage7.png)

###时间复杂度：
O(n+m)
 
##5. Hash表应用
###数据结构
Hash表
###算法设计思想
根据关键码值(Key value)而直接进行访问的数据结构。也就是说，它通过把关键码值映射到表中一个位置来访问记录，以加快查找的速度。这个映射函数叫做散列函数，存放记录的数组叫做散列表。

###源程序：
```
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
	cout << "对" << t.ID << "的hash结果是:" << hash%n<<endl;
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
	cout << "请输入hash表的大小：";
	cin >> n;
	cout << "请输入使用的冲突解决方式（1. 线性探查 2. 链式）：";
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

//LineHash.h
#ifndef _LINEHASH_H_
#define _LINEHASH_H_

#include <iostream>
#include <vector>

	template <class T >
	class LineHash
	{
	private:
		std::vector<T> hashtab;
		std::vector<bool> inuse;
		int(*HashFunc)(T t,int n);
		int size;
	public:
		LineHash(int n) :size(n), hashtab(n), inuse(n, false), HashFunc(nullptr){};
		void setHashFunc(int(*hashfunc)(T t,int n))
		{
			HashFunc = hashfunc;
		}
		int add(T e)
		{
			if (HashFunc == nullptr)
				return -1;
			int h = HashFunc(e,size);
			int count = 0;
			int th = h;
			do
			{
				if (inuse[h])
				{
					++h; ++count;
					if (h == size)
						h %= size;
				}
				else break;
			} while (th != h);

			if (h == size)
			{
				std::cout << "表满！失败" << endl;
				return -1;
			}
			hashtab[h] = e;
			inuse[h] = true;
			if (count>0)std::cout << "冲突!位移：" << count << endl;
			return h;
		}
		T *Find(T e)
		{
			if (HashFunc == nullptr)
				return NULL;
			int h = HashFunc(e,size);
			int th = h;
			do
			{
				if (hashtab[h] == e)
					return &(hashtab[h]);
				h++;
				if (h == size)
					h %= size;
			} while (th!=h);
			return NULL;
		}
		T &operator[](int n)
		{
			return hashtab[n];
		}
	};

#endif
//LinkHash.h
#ifndef _LINKHASH_H_
#define _LINKHASH_H_
#include <iostream>
#include <vector>
	template <class T>
	struct hash_node
	{
		T e;
		hash_node *next = nullptr;
	};

	template <class T >
	class LinkHash
	{
	private:
		std::vector<hash_node<T>*> hashtab;
		int(*HashFunc)(T t,int n);
		int size;
	public:
		LinkHash(int n) :size(n), hashtab(n, nullptr), HashFunc(nullptr){};
		void setHashFunc(int(*hashfunc)(T t,int n))
		{
			HashFunc = hashfunc;
		}
		int add(T e)
		{
			if (HashFunc == nullptr)
				return -1;
			int h = HashFunc(e,size);
			int count = 0;
			hash_node<T> *no = new hash_node<T>;
			if (hashtab[h]!=nullptr)
				std::cout << "冲突!插入" << h << endl;
			no->next = hashtab[h];
			hashtab[h] = no;
			no->e = e;
			return h;
		}
		T *Find(T e)
		{
			if (HashFunc == nullptr)
				return NULL;
			int h = HashFunc(e,size);
			hash_node<T> *p = hashtab[h];
			while (p)
			{
				if (p->e == e)
					return &(p->e);
				p = p->next;
			}
			return NULL;
		}
		T &operator[](int n)
		{
			return hashtab[n];
		}
	};


#endif
```
###测试数据和结果：
![](http://lairenla.qiniudn.com/dspicimage8.png)
![](http://lairenla.qiniudn.com/dspicimage9.png)
![](http://lairenla.qiniudn.com/dspicimage10.png)


###时间复杂度：
O(1)特殊情况会退化到O(n)
 
##6. 排序算法比较

###数据结构
线性表
###算法设计思想

####1.选择排序
每一趟从待排序的数据元素中选出最小（或最大）的一个元素，顺序放在已排好序的数列的最后，直到全部待排序的数据元素排完。

####2.直接插入排序
每次将一个待排序的记录，按其关键字大小插入到前面已经排好序的子文件中的适当位置，直到全部记录插入完成为止。

####3.冒泡排序
依次比较相邻的两个数，将小数放在前面，大数放在后面。即在第一趟：首先比较第1个和第2个数，将小数放前，大数放后。然后比较第2个数和第3个数，将小 数放前，大数放后，如此继续，直至比较最后两个数，将小数放前，大数放后。至此第一趟结束，将最大的数放到了最后。在第二趟：仍从第一对数开始比较（因为 可能由于第2个数和第3个数的交换，使得第1个数不再小于第2个数），将小数放前，大数放后，一直比较到倒数第二个数（倒数第一的位置上已经是最大的）， 第二趟结束，在倒数第二的位置上得到一个新的最大数（其实在整个数列中是第二大的数）。如此下去，重复以上过程，直至最终完成排序。由于在排序过程中总是小数往前放，大数往后放，相当于气泡往上升，所以称作冒泡排序。

####4.Shell排序
先取一个小于n的整数d1作为第一个增量，把文件的全部记录分成d1个组。所有距离为dl的倍数的记录放在同一个组中。先在各组内进行直接插人排序；然后，取第二个增量d2<d1重复上述的分组和排序，直至所取的增量dt=1(dt<dt-l<…<d2<d1)，即所有记录放在同一组中进行直接插入排序为止。该方法实质上是一种分组插入方法。

####5.堆排序
1. 先将初始文件R[1..n]建成一个大根堆,此堆为初始的无序区 　　
2. 再将关键字最大的记录R[1] (即堆顶)和无序区的最后一个记录R[n]交换，由此得到新的无序区R[1..n-1]和有序区R[n]，且满足R[1..n-1].keys≤R[n].key 　　
3. 由于交换后新的根R[1]可能违反堆性质，故应将当前无序区R[1..n-1]调整为堆。然 后再次将R[1..n-1]中关键字最大的记录R[1]和该区间的最后一个记录R[n-1]交换，由此得到新的无序区R[1..n-2]和有序区R[n- 1..n]，且仍满足关系R[1..n-2].keys≤R[n-1..n].keys，同样要将R[1..n-2]调整为堆。
4. 直到无序区只有一个元素为止。

####6.快速排序
通过一趟排序将要排序的数据分割成独立的两部分，其中一部分的所有数据都比另外一部分的所有数据都要小，然后再按此方法对这两部分数据分别进行快速排序，整个排序过程可以递归进行，以此达到整个数据变成有序序列。
####7.归并排序
归并排序是建立在归并操作上的一种有效的排序算法。该算法是采用分治法（Divide and Conquer）的一个非常典型的应用。将已有序的子序列合并，得到完全有序的序列；即先使每个子序列有序，再使子序列段间有序。若将两个有序表合并成一个有序表，称为2-路归并。
归并操作的工作原理如下：
申请空间，使其大小为两个已经排序序列之和，该空间用来存放合并后的序列
设定两个指针，最初位置分别为两个已经排序序列的起始位置
比较两个指针所指向的元素，选择相对小的元素放入到合并空间，并移动指针到下一位置
重复步骤3直到某一指针达到序列尾
将另一序列剩下的所有元素直接复制到合并序列尾
源程序：
```
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include "Sort.h"
int a[30000], b[30000];


void copy(int n) {
	for (int i = 0; i < n; ++i) b[i] = a[i];
}

int main() {
	srand(time(0));
	printf("%5s%10s%10s%10s%10s%10s%10s%10s%10s\n", "Num", "Insert", "HalfIns", "Shell", "Bubble", "Qsort", "Select", "Heap", "Merge");
	for (int n = 500; n <= 30000; n += 500) {
		for (int i = 0; i < n; ++i) a[i] = rand();
		printf("%5d", n);
		copy(n);
		printf("%10d", insert(n,b));
		copy(n);
		printf("%10d", halfIns(n,b));
		copy(n);
		printf("%10d", shell(n,b));
		copy(n);
		printf("%10d", bubble(n,b));
		copy(n);
		printf("%10d", qsort(0, n - 1,b));
		copy(n);
		printf("%10d", select(n,b));
		// heap sort requires array starts from 1
		for (int i = 0; i < n; ++i) b[i + 1] = a[i];
		printf("%10d", heap(n,b));
		copy(n);
		printf("%10d", merge(0, n - 1,b));
		printf("\n");
	}
	return 0;
}

//Sort.h
#ifndef _SORT_H_
#define _SORT_H_
int insert(int n, int *b) {
	int t, i, j, count = 0;
	for (i = 0; i < n; ++i) {
		t = b[i];
		for (j = i - 1; j >= 0 && t > b[j]; --j) {
			b[j + 1] = b[j];
			++count;
		}
		b[j + 1] = t;
	}
	return count;
}
int halfIns(int n, int *b) {
	int t, count = 0;
	for (int i = 0; i < n; ++i) {
		t = b[i];
		int l = 1, r = i - 1;
		while (l <= r) {
			int m = (l + r) / 2;
			if (t < b[m]) r = m - 1;
			else l = m + 1;
			++count;
		}
		for (int j = i - 1; j >= l; --j) b[j + 1] = b[j];
		b[r + 1] = t;
	}
	return count;
}
int shell(int n, int *b) {
	int d, count = 0;
	for (d = 3; d > 0; --d) {
		for (int i = 0; i < d; ++i) {
			for (int j = i + d; j < n; j += d) {
				++count;
				if (b[j] < b[j - d]) {
					int t = b[j];
					int k = j - d;
					while (k >= 0 && b[k] > t) {
						++count;
						b[k + d] = b[k];
						k -= d;
					}
					b[k + d] = t;
				}
			}
		}
	}
	return count;
}
int bubble(int n, int *b) {
	int count = 0;
	for (int i = 1; i < n; ++i)
	for (int j = 0; j < n - i; ++j) {
		++count;
		if (b[j] > b[j + 1]) {
			int t = b[j];
			b[j] = b[j + 1];
			b[j + 1] = t;
		}
	}
	return count;
}
int qsort(int l, int r, int *b) {
	int i = l, j = r, x = b[(l + r) / 2], count = 0;
	do {
		while (b[i] < x) ++i, ++count;
		while (b[j] > x) --j, ++count;
		if (i <= j) {
			int t = b[i];
			b[i] = b[j];
			b[j] = t;
			++i, --j;
		}
	} while (i <= j);
	if (l < j) count += qsort(l, j, b);
	if (i < r) count += qsort(i, r, b);
	return count;
}
int select(int n, int *b) {
	int count = 0;
	for (int i = 0; i < n; ++i) {
		int k = i;
		for (int j = i + 1; j < n; ++j) {
			++count;
			if (b[j] < b[k]) k = j;
		}
		int t = b[k];
		b[k] = b[i];
		b[i] = t;
	}
	return count;
}
void heap_shift(int n, int x, int &count, int *b) {
	while (x <= n / 2) {
		int t = x * 2;
		if (t < n && b[t] > b[t + 1]) {
			++t;
			++count;
		}
		++count;
		if (b[x] > b[t]) {
			int temp = b[x];
			b[x] = b[t];
			b[t] = temp;
			x = t;
		}
		else break;
	}
}
int heap(int n, int *b) {
	int count = 0;
	for (int i = n / 2; i >= 1; --i)
		heap_shift(n, i, count, b);
	while (n > 0) {
		b[1] = b[n--];
		heap_shift(n, 1, count, b);
	}
	return count;
}
int tmp[30000];
void domerge(int p, int q, int r, int &count, int *b) {
	int t = p, i = p, j = q + 1;
	while (t <= r) {
		++count;
		if (i <= q && (j > r || b[i] <= b[j]))
			tmp[t] = b[i++];
		else
			tmp[t] = b[j++];
		++t;
	}
	for (i = p; i <= r; ++i) b[i] = tmp[i];
}
int merge(int l, int r, int *b) {
	int count = 0;
	if (l != r) {
		int m = (l + r - 1) / 2;
		count += merge(l, m, b);
		count += merge(m + 1, r, b);
		domerge(l, m, r, count, b);
	}
	return count;
}

#endif
```

###测试数据和结果：
![](http://lairenla.qiniudn.com/dspicimage11.png)

###时间复杂度：
直接插入排序O(n^2)
折半插入排序O(n^2)
起泡排序O(n^2)
快速排序O(nlogn)
选择排序O(n^2)
堆排序O(nlogn)
基数排序O(nlogn)
 
##7.迷宫问题
###数据结构
线性表(链表)
###算法设计思想
####地图生成
并查集是一中用于判断元素是否属于同一集合的数据结构，主要的操作有查找和合并。并查集实际上是一个森林，每一个集合是一棵树。
在并查集中，默认每个元素的父元素指向自己，在执行合并操作的时候只需要将自己的父元素指向要合并的节点，即可完成合并。在执行查找的时候，只需要一直寻找父元素，直到父元素指向父元素本身。
但是当合并次数增多以后，可能会出现树的深度过大，导致每次回溯父节点耗时过长。这里有一种路径压缩的办法。在执行find的时候，将每个节点的父节点都改为最远处的父节点。在递归执行查找的时候只需要很小的改动即可。
还有一种按秩合并的算法可以优化并查集。但是远没有路径压缩简单易懂，在小规模数据时无需使用。
随机选择一堵墙，并把墙打通，隔开的两个格子在并查集中合并。直到原点和终点在同一个集合中。
####路径选择
深度优先搜索
###源程序：
```
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

//UnionSet.h
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
```
###测试数据和结果：
![](http://lairenla.qiniudn.com/dspicimage12.png)
![](http://lairenla.qiniudn.com/dspicimage13.png)
![](http://lairenla.qiniudn.com/dspicimage14.png)

###时间复杂度：
O(n^2)
 
##10.平衡树
###数据结构
平衡树
###算法设计思想
在构造二叉排序树的过程中，每当插入一个结点时，首先检查是否因插入而破坏了树的平衡性，如果是因插入结点而破坏了树的平衡性，则找出其中最小不平衡子树，在保持排序树特性的前提下，调整最小不平衡子树中各结点之间的连接关系，以达到新的平衡。通常将这样得到的平衡二叉排序树简称为AVL树。
###源程序：
```
#include <iostream>
#include <string>
#include "AVLTree.h"

using namespace std;

AVLTree<string> tree;
void ShowMenu();

int main(void)
{
	ShowMenu();
	return 0;
}

void Add()
{
	system("cls");
	string buf;
	cout << "请输入数据（字符串,输入x退出）：";
	cin >> buf;
	while (buf != "x")
	{
		tree.insert(buf);
		cout << "请输入数据（字符串,输入x退出）：";
		cin >> buf;
	}
}
void Find()
{
	system("cls");
	string buf;
	cout << "请输入数据（字符串,输入x退出）：";
	cin >> buf;
	while (buf != "x")
	{
		if (tree.find(buf)) cout << "已找到" << endl;
		else cout << "未找到" << endl;
		cout << "请输入数据（字符串,输入x退出）：";
		cin >> buf;
	}
}
void Delete()
{
	system("cls");
	string buf;
	cout << "请输入数据（字符串,输入x退出）：";
	cin >> buf;
	while (buf != "x")
	{
		tree.Delete(buf);
		cout << "请输入数据（字符串,输入x退出）：";
		cin >> buf;
	}
}
void ShowMenu()
{
	while (1)
	{
		system("cls");
		cout << "1.添加元素" << endl;
		cout << "2.查找元素" << endl;
		cout << "3.删除元素" << endl;
		cout << "4.全部输出" << endl;
		cout << "0.退出" << endl;
		cout << "请选择：";
		int n;
		cin >> n;
		switch (n)
		{
		case 1:
			Add();
			break;
		case 2:
			Find();
			break;
		case 3:
			Delete();
			break;
		case 4:
			tree.traversal();
			system("Pause");
			break;
		default:
			return;
			break;
		}
	}
}

//AVLTree.h
#ifndef _AVLTREE_H_
#define _AVLTREE_H_
//AVL树节点信息
template<class T>
class TreeNode
{
public:
	TreeNode() :lson(NULL), rson(NULL), freq(1), hgt(0){}
	T data;//值
	int hgt;//以此节点为根的树的高度
	unsigned int freq;//频率
	TreeNode* lson;//指向左儿子的地址
	TreeNode* rson;//指向右儿子的地址
};

//AVL树类的属性和方法声明
template<class T>
class AVLTree
{
private:
	TreeNode<T>* root;//根节点
	void insertpri(TreeNode<T>* &node, T x);//插入
	TreeNode<T>* findpri(TreeNode<T>* node, T x);//查找
	void insubtree(TreeNode<T>* node);//中序遍历
	void Deletepri(TreeNode<T>* &node, T x);//删除
	int height(TreeNode<T>* node);//求树的高度
	void SingRotateLeft(TreeNode<T>* &k2);//左左情况下的旋转
	void SingRotateRight(TreeNode<T>* &k2);//右右情况下的旋转
	void DoubleRotateLR(TreeNode<T>* &k3);//左右情况下的旋转
	void DoubleRotateRL(TreeNode<T>* &k3);//右左情况下的旋转
	int Max(int cmpa, int cmpb);//求最大值

public:
	AVLTree() :root(NULL){}
	void insert(T x);//插入接口
	TreeNode<T>* find(T x);//查找接口
	void Delete(T x);//删除接口
	void traversal();//遍历接口

};

// 计算以节点为根的树的高度
template<class T>
int AVLTree<T>::height(TreeNode<T>* node)
{
	if (node != NULL)
		return node->hgt;
	return -1;
}
//求最大值
template<class T>
int AVLTree<T>::Max(int cmpa, int cmpb)
{
	return cmpa>cmpb ? cmpa : cmpb;
}
// 左左情况下的旋转
template<class T>
void AVLTree<T>::SingRotateLeft(TreeNode<T>* &k2)
{
	TreeNode<T>* k1;
	k1 = k2->lson;
	k2->lson = k1->rson;
	k1->rson = k2;

	k2->hgt = Max(height(k2->lson), height(k2->rson)) + 1;
	k1->hgt = Max(height(k1->lson), k2->hgt) + 1;
}
//右右情况下的旋转
template<class T>
void AVLTree<T>::SingRotateRight(TreeNode<T>* &k2)
{
	TreeNode<T>* k1;
	k1 = k2->rson;
	k2->rson = k1->lson;
	k1->lson = k2;

	k2->hgt = Max(height(k2->lson), height(k2->rson)) + 1;
	k1->hgt = Max(height(k1->rson), k2->hgt) + 1;
}

//左右情况的旋转
template<class T>
void AVLTree<T>::DoubleRotateLR(TreeNode<T>* &k3)
{
	SingRotateRight(k3->lson);
	SingRotateLeft(k3);
}
//右左情况的旋转
template<class T>
void AVLTree<T>::DoubleRotateRL(TreeNode<T>* &k3)
{
	SingRotateLeft(k3->rson);
	SingRotateRight(k3);
}

//插入
template<class T>
void AVLTree<T>::insertpri(TreeNode<T>* &node, T x)
{
	if (node == NULL)//如果节点为空,就在此节点处加入x信息
	{
		node = new TreeNode<T>();
		node->data = x;
		return;
	}
	if (node->data>x)//如果x小于节点的值,就继续在节点的左子树中插入x
	{
		insertpri(node->lson, x);
		if (2 == height(node->lson) - height(node->rson))
		if (x<node->lson->data)
			SingRotateLeft(node);
		else
			DoubleRotateLR(node);
	}
	else if (node->data<x)//如果x大于节点的值,就继续在节点的右子树中插入x
	{
		insertpri(node->rson, x);
		if (2 == height(node->rson) - height(node->lson))//如果高度之差为2的话就失去了平衡,需要旋转
		if (x>node->rson->data)
			SingRotateRight(node);
		else
			DoubleRotateRL(node);
	}
	else ++(node->freq);//如果相等,就把频率加1
	node->hgt = Max(height(node->lson), height(node->rson));
}
//插入接口
template<class T>
void AVLTree<T>::insert(T x)
{
	insertpri(root, x);
}

//查找
template<class T>
TreeNode<T>* AVLTree<T>::findpri(TreeNode<T>* node, T x)
{
	if (node == NULL)//如果节点为空说明没找到,返回NULL
	{
		return NULL;
	}
	if (node->data>x)//如果x小于节点的值,就继续在节点的左子树中查找x
	{
		return findpri(node->lson, x);
	}
	else if (node->data<x)//如果x大于节点的值,就继续在节点的左子树中查找x
	{
		return findpri(node->rson, x);
	}
	else return node;//如果相等,就找到了此节点
}
//查找接口
template<class T>
TreeNode<T>* AVLTree<T>::find(T x)
{
	return findpri(root, x);
}

//删除
template<class T>
void AVLTree<T>::Deletepri(TreeNode<T>* &node, T x)
{
	if (node == NULL) return;//没有找到值是x的节点
	if (x < node->data)
	{
		Deletepri(node->lson, x);//如果x小于节点的值,就继续在节点的左子树中删除x
		if (2 == height(node->rson) - height(node->lson))
		if (node->rson->lson != NULL && (height(node->rson->lson)>height(node->rson->rson)))
			DoubleRotateRL(node);
		else
			SingRotateRight(node);
	}

	else if (x > node->data)
	{
		Deletepri(node->rson, x);//如果x大于节点的值,就继续在节点的右子树中删除x
		if (2 == height(node->lson) - height(node->rson))
		if (node->lson->rson != NULL && (height(node->lson->rson)>height(node->lson->lson)))
			DoubleRotateLR(node);
		else
			SingRotateLeft(node);
	}

	else//如果相等,此节点就是要删除的节点
	{
		if (node->lson&&node->rson)//此节点有两个儿子
		{
			TreeNode<T>* temp = node->rson;//temp指向节点的右儿子
			while (temp->lson != NULL) temp = temp->lson;//找到右子树中值最小的节点
			//把右子树中最小节点的值赋值给本节点
			node->data = temp->data;
			node->freq = temp->freq;
			Deletepri(node->rson, temp->data);//删除右子树中最小值的节点
			if (2 == height(node->lson) - height(node->rson))
			{
				if (node->lson->rson != NULL && (height(node->lson->rson)>height(node->lson->lson)))
					DoubleRotateLR(node);
				else
					SingRotateLeft(node);
			}
		}
		else//此节点有1个或0个儿子
		{
			TreeNode<T>* temp = node;
			if (node->lson == NULL)//有右儿子或者没有儿子
				node = node->rson;
			else if (node->rson == NULL)//有左儿子
				node = node->lson;
			delete(temp);
			temp = NULL;
		}
	}
	if (node == NULL) return;
	node->hgt = Max(height(node->lson), height(node->rson)) + 1;
	return;
}
//删除接口
template<class T>
void AVLTree<T>::Delete(T x)
{
	Deletepri(root, x);
}

//中序遍历函数
template<class T>
void AVLTree<T>::insubtree(TreeNode<T>* node)
{
	if (node == NULL) return;
	insubtree(node->lson);//先遍历左子树
	cout << node->data << " ";//输出根节点
	insubtree(node->rson);//再遍历右子树
}
//中序遍历接口
template<class T>
void AVLTree<T>::traversal()
{
	insubtree(root);
}
#endif
```
###测试数据和结果
![](http://lairenla.qiniudn.com/dspicimage15.png)
###时间复杂度
O(logn)

