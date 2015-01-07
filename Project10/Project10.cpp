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