#pragma once
#include "Identity.h"
#include <iostream>
using namespace std;
#include <string>
#include<vector>
#include "teacher.h"
#include "student.h"
#include "computerRoom.h"

class Manager : public Identity {
public:
	// 默认构造
	Manager();

	// 有参构造
	Manager(string name, string pwd);

	// 选择菜单
	void operMenu();

	// 添加账号
	void addPerson();

	// 查看账号
	void showPerson();

	// 查看机房信息
	void showComputer();

	// 清空预约记录
	void clearFile();

	// 初始化容器
	void initVector();

	// 学号重复检测
	bool checkRepeat(int id, int type);




	// 学生容器
	vector<Student> vStu;

	// 教师容器
	vector<Teacher> vTea;

	// 机房容量
	vector<ComputerRoom> vCom;
};