//#define _CRT_SECURE_NO_WARNINGS
//#include <cstdio>
//#include <cstdlib>
//#include <iostream>
//#include <stack>
//#define DISPO dispopt(opt, optt)
//#define DISPN dispnum(onum, onumt)
//
//using namespace std;
//
//double onum[100];
//int onumt = 0;
//char opt[100];
//int optt = 0;
//char buf[128];
//
//double Do(char *buf);
//int getI(char st);
//int checkOrd(char st, char nd);
//double calc(char o, double a, double b);
//void dispnum(double *t, int n);
//void dispopt(char *t, int n);
//
//int main(void)
//{
//	char buf[128];
//	while (1)
//	{
//		scanf("%s", buf);
//		if (!strcmp(buf, "##"))
//			break;
//		Do(buf);
//	}
//	return 0;
//}
//
//double Do(char *buf)
//{
//	int nums[20];
//	int numsp = 0;
//	char *p = buf;
//	double opn = 0;
//	bool opnIsset = false;
//	bool floatFlag = false;
//	while (*p != '#')
//		p++;
//	++p;
//	while (*p)
//	{
//		if (isdigit(*p))
//		{
//			if (!opnIsset)
//				opnIsset = true;
//			nums[numsp++] = *p - '0';
//		}
//		else
//		{
//			int exp = 1;
//			if (!floatFlag)
//			{
//				for (int i = 0; i < numsp - 1; i++)
//					exp *= 10;
//				for (int i = 0; i < numsp; i++)
//				{
//					opn += nums[i] * exp;
//					exp /= 10;
//				}
//				numsp = 0;
//			}
//			if (floatFlag)
//			{
//				exp = 10;
//				for (int i = 0; i < numsp; i++)
//				{
//					opn += (double)nums[i] / exp;
//					exp *= 10;
//				}
//				numsp = 0;
//			}
//			if (*p == '.')
//			{
//				if (!floatFlag)
//					floatFlag = true;
//				else return -1;
//			}
//			else
//			{
//				if (floatFlag)
//					floatFlag = false;
//				if (opnIsset)
//				{
//					onum[onumt++] = opn;
//					DISPO;
//					DISPN;
//					opnIsset = false;
//					opn = 0;
//				}
//				if (optt == 0)
//				{
//					opt[optt++] = *p;
//					DISPO;
//					DISPN;
//				}
//				else
//				{
//					char oo;
//					double d1, d2;
//					printf("未处理的字符串：%s\n", p);
//					switch (checkOrd(opt[optt - 1], *p))
//					{
//					case 1:
//						oo = opt[--optt];
//						DISPO;
//						DISPN;
//						d1 = onum[--onumt];
//						DISPO;
//						DISPN;
//						d2 = onum[--onumt];
//						DISPO;
//						DISPN;
//						onum[onumt++] = calc(oo, d2, d1);
//						DISPO;
//						DISPN;
//						while (opt[optt - 1] == '(')
//							opt[--optt];
//						else
//						{
//							opt[optt++] = *p;
//							DISPO;
//							DISPN;
//						}
//						break;
//					case 0:
//						oo=opt[--optt];
//						if (oo != '(')
//							return -1;
//						DISPO;
//						DISPN;
//						break;
//					case -1:
//						opt[optt++] = *p;
//						DISPO;
//						DISPN;
//						break;
//					}
//				}
//			}
//
//			
//		}
//		++p;
//	}
//	char oo;
//	double d1, d2;
//	--optt;
//	while (optt)
//	{
//		oo = opt[--optt];
//		DISPO;
//		DISPN;
//		d1 = onum[--onumt];
//		DISPO;
//		DISPN;
//		d2 = onum[--onumt];
//		DISPO;
//		DISPN;
//		onum[onumt++] = calc(oo, d2, d1);
//		DISPO;
//		DISPN;
//	}
//
//	printf("结果是：%lf", onum[--onumt]);
//	onumt = 0;
//}
//
//short Prior[7][7] = {  
//	1,	1,	-1,	-1,	-1,	1,	1,
//	1,	1,	-1,	-1,	-1,	1,	1,
//	1,	1,	1,	1,	-1,	1,	1,
//	1,	1,	1,	1,	-1,	1,	1,
//	-1,	-1,	-1,	-1, -1,	0,	99,
//	1,	1,	1, 1,	99, 1,	1,
//	-1,	-1,	-1, -1, -1, 99, 0
//};
//int checkOrd(char st, char nd)
//{
//	printf("正在比较的符号 %c %c\n", st, nd);
//	int ist = getI(st), ind = getI(nd);
//	return Prior[ist][ind];
//}
//
//int getI(char st)
//{
//	switch (st)
//	{
//	case '+':return 0;
//	case '-':return 1;
//	case '*':return 2;
//	case '/':return 3;
//	case '(':return 4;
//	case ')':return 5;
//	case '#':return 6;
//	}
//	return -1;
//}
//
//double calc(char o, double a, double b)
//{
//	printf("正在计算%lf%c%lf\n", a, o, b);
//	switch (o) {
//	case '+': return a + b;
//	case '-': return a - b;
//	case '*': return a*b;
//	case '/': return a / b;
//	default: return 0;
//	}
//	return 0;
//}
//
//void dispnum(double *t, int n)
//{
//	printf("数字栈的情况:");
//	for (int i = 0; i < n; i++)
//		printf("%lf ", t[i]);
//	printf("\n");
//}
//
//void dispopt(char *t, int n)
//{
//	printf("符号栈的情况:");
//	for (int i = 0; i < n; i++)
//		printf("%c ", t[i]);
//	printf("\n");
//}