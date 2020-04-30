#include <iostream>
#include "teacher.h"
using namespace std;
#include <string>
#include"globalFile.h"
#include<string>	
#include "orderFile.h"
#include <fstream>
#include <vector>

// 默认构造
Teacher::Teacher() {

}

// 有参构造
Teacher::Teacher(int empId, string name, string pwd) {
	this->m_EmpId = empId;
	this->m_Name = name;
	this->m_Pwd = pwd;
}

// 菜单界面
void Teacher::operMenu() {
	cout << "欢迎教师：" << this->m_Name << "登录！" << endl;
	cout << "\t\t|-------------------------------------|\n";
	cout << "\t\t|                                     |\n";
	cout << "\t\t|             1、查看所有预约记录     |\n";
	cout << "\t\t|                                     |\n";
	cout << "\t\t|             2、审核预约             |\n";
	cout << "\t\t|                                     |\n";
	cout << "\t\t|             0、注销登录             |\n";
	cout << "\t\t|                                     |\n";
	cout << "\t\t|-------------------------------------|\n";

	cout << "请输入您的选择：" << endl;
}

// 查看所有预约
void Teacher::showAllOrder() {
	OrderFile of;
	if (of.m_Size == 0) {
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}
	else {
		for (int i = 0; i < of.m_Size; ++i) {
			cout << i + 1 << "、" << " ";
			cout << "预约日期：周" << of.m_OrderData[i]["data"] << "  ";
			cout << "时间段：" << ((of.m_OrderData[i]["interval"] == "1") ? "上午" : "下午") << "  ";
			cout << "学号：" << of.m_OrderData[i]["stuId"] << "  ";
			cout << "学生：" << of.m_OrderData[i]["stuName"] << "  ";
			cout << "机房： " << of.m_OrderData[i]["roomID"] << "  ";
			string status = "状态：";
			if (of.m_OrderData[i]["status"] == "1") {
				status += "审核中";
			}
			else if (of.m_OrderData[i]["status"] == "2") {
				status += "预约成功";
			}
			else if (of.m_OrderData[i]["status"] == "-1") {
				status += "预约失败，审核未通过";
			}
			else {
				status += "预约已取消";
			}
			cout << status << endl;
		}
		system("pause");
		system("cls");
	}
}

// 审核预约
void Teacher::validOrder() {
	OrderFile of;
	if (of.m_Size == 0) {
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}
	else {
		cout << "待审核预约记录如下：" << endl;
		int index = 1;
		vector<int> v; // 存放最大容器中的下标编号
		for (int i = 0; i < of.m_Size; ++i) {
			if (of.m_OrderData[i]["status"] == "1") {
				v.push_back(i);
				cout << index++ << "、";
				cout << "预约日期：周" << of.m_OrderData[i]["data"] << "  ";
				cout << "时间段：" << ((of.m_OrderData[i]["interval"] == "1") ? "上午" : "下午") << " ";
				cout << "学号：" << of.m_OrderData[i]["stuId"] << "  ";
				cout << "学生：" << of.m_OrderData[i]["stuName"] << "  ";
				cout << "机房编号：" << of.m_OrderData[i]["roomID"] << "  ";
				string status = "状态：";
				if (of.m_OrderData[i]["status"] == "1")
					status += "审核中";
				cout << status << endl;
			}
		}
		cout << "请输入待审核的记录，按0返回上一步" << endl;
		int select = 0;
		int ret = 0;
		while (true) {
			cin >> select;
			if (select >= 0 && select <= v.size()) {
				if (select == 0) {
					break;
				}
				else {
					cout << "请输入审核结果" << endl;
					cout << "1、通过" << endl;
					cout << "2、不通过" << endl;
					cin >> ret;
					if (ret == 1) {
						of.m_OrderData[v[select - 1]]["status"] = "2";
					}
					else {
						of.m_OrderData[v[select - 1]]["status"] = "-1";
					}
					of.updateOrder();
					cout << "审核成功" << endl;
					break;
				}
			}
			else {
				cout << "输入有误，请重新输入" << endl;
			}

		}

	}
	system("pause");
	system("cls");
}