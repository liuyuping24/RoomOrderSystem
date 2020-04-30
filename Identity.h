#pragma once
#include <string>
using namespace std;
#include <string>

class Identity {
public:
	
	// 操作菜单
	// 父类虚函数，一定要有关键字virtual 和 = 0；
	// 子类继承父类的虚函数，可以不加关键字 virtual；
	// 子类不允许添加 = 0，因为子类是一个函数；
	virtual void operMenu() = 0;

	// user name;
	string m_Name;
	// user password
	string m_Pwd;
};
