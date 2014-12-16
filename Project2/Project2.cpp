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

