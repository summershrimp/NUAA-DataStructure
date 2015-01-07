#ifndef _HOMETREE_H_
#define _HOMETREE_H_
#include <string>

struct Date
{
	int year, month, day;
	friend ostream operator << (ostream out, Date &rhs)
	{
		out << rhs.year << "年"<<rhs.month<<"月"<<rhs.day<<"日";
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
		out << "姓名:" << rhs.Name << std::endl;
		out << "出生日期：" << rhs.Birthday << std::endl;
		out << "婚否：";
		out << rhs.Married ? "已婚" : "未婚";
		out << std::endl;
		if (rhs.Isalive)
		{
			out << "健在";

		}
		else
		{
			out << "去世" << std::endl
				<< "去世日期：" << rhs.Deadday << std::endl;
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