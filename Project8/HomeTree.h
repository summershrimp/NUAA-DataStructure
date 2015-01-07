#ifndef _HOMETREE_H_
#define _HOMETREE_H_
#include <string>

struct Date
{
	int year, month, day;
	friend ostream operator << (ostream out, Date &rhs)
	{
		out << rhs.year << "��"<<rhs.month<<"��"<<rhs.day<<"��";
	}
};

struct TreeNode
{
	TreeNode *Sibling = nullptr;
	TreeNode *Son = nullptr;
	TreeNode *Father = nullptr;
	std::string Name;
	Date Birthday;
	bool Married = false;
	std::string Address;
	bool Isalive = true;
	Date Deadday;
	int Dai = 1;

	friend ostream operator << (ostream out, TreeNode &rhs)
	{
		out << "����:" << rhs.Name << std::endl;
		out << "�������ڣ�" << rhs.Birthday << std::endl;
		out << "���";
		out << rhs.Married ? "�ѻ�" : "δ��";
		out << std::endl;
		if (rhs.Isalive)
		{
			out << "����";

		}
		else
		{
			out << "ȥ��" << std::endl
				<< "ȥ�����ڣ�" << rhs.Deadday << std::endl;
		}
		out << rhs.Address;
	}
};


class HomeTree
{
private:
	TreeNode *root;
	int depth;
public:
	HomeTree():root(nullptr){}

};



#endif