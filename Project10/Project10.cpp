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
	cout << "���������ݣ��ַ���,����x�˳�����";
	cin >> buf;
	while (buf != "x")
	{
		tree.insert(buf);
		cout << "���������ݣ��ַ���,����x�˳�����";
		cin >> buf;
	}
}
void Find()
{
	system("cls");
	string buf;
	cout << "���������ݣ��ַ���,����x�˳�����";
	cin >> buf;
	while (buf != "x")
	{
		if (tree.find(buf)) cout << "���ҵ�" << endl;
		else cout << "δ�ҵ�" << endl;
		cout << "���������ݣ��ַ���,����x�˳�����";
		cin >> buf;
	}
}
void Delete()
{
	system("cls");
	string buf;
	cout << "���������ݣ��ַ���,����x�˳�����";
	cin >> buf;
	while (buf != "x")
	{
		tree.Delete(buf);
		cout << "���������ݣ��ַ���,����x�˳�����";
		cin >> buf;
	}
}
void ShowMenu()
{
	while (1)
	{
		system("cls");
		cout << "1.���Ԫ��" << endl;
		cout << "2.����Ԫ��" << endl;
		cout << "3.ɾ��Ԫ��" << endl;
		cout << "4.ȫ�����" << endl;
		cout << "0.�˳�" << endl;
		cout << "��ѡ��";
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