#pragma once
#include<iostream>
#include"globalFile.h"
#include<string>
#include <map>
#include<fstream>
using namespace std;

class OrderFile {
public:
	//构造函数
	OrderFile();

	//更新预约记录
	void updateOrder();

	// 记录预约记录
	int m_Size;

	//记录所有预约信息的容器， key记录预约条数，value使用嵌套map容器记录键值对信息
	map<int, map<string, string>> m_OrderData;
	
};