#include <iostream>
#include"student.h"
#include <string>
#include<vector>
#include"computerRoom.h"
#include<fstream>
#include"globalFile.h"
using namespace std;
#include "orderFile.h"

// 默认构造
Student::Student() {

}

// 有参构造
Student::Student(int id, string name, string pwd) {
	this->m_StuID = id;
	this->m_Name = name;
	this->m_Pwd = pwd;
	ifstream ifs;
	ifs.open(COMPUTER_FILE, ios::in);
	ComputerRoom com;
	// 读文件
	while (ifs >> com.m_ComId && ifs >> com.m_MaxNum) {
		vCom.push_back(com);
	}
	ifs.close();
}

// 菜单界面
void Student::operMenu() {
	cout << "欢迎管理员：" << this->m_Name << "登录！" << endl;
	cout << "\t\t|-------------------------------------|\n";
	cout << "\t\t|                                     |\n";
	cout << "\t\t|             1、申请预约             |\n";
	cout << "\t\t|                                     |\n";
	cout << "\t\t|             2、查看本人预约         |\n";
	cout << "\t\t|                                     |\n";
	cout << "\t\t|             3、查看所有人预约       |\n";
	cout << "\t\t|                                     |\n";
	cout << "\t\t|             4、取消预约             |\n";
	cout << "\t\t|                                     |\n";
	cout << "\t\t|             0、注销登录             |\n";
	cout << "\t\t|                                     |\n";
	cout << "\t\t|-------------------------------------|\n";

	cout << "请输入您的选择：" << endl;
}

// 申请预约
void Student::applyOrder() {
	cout << "机房开放时间为：周一至周五" << endl;
	cout << "请输入预约时间：" << endl;
	cout << "1、周一" << endl;
	cout << "1、周二" << endl;
	cout << "1、周三" << endl;
	cout << "1、周四" << endl;
	cout << "1、周五" << endl;
	//接收预约时间
	int data = 0;
	// 接收预约时间段上午or下午
	int interval = 0;
	// 预约机房号
	int room = 0;
	while (true) {
		cin >> data;
		if (data >= 1 && data <= 5) {
			break;
		}
		cout << "输入有误，请重新输入" << endl;
	}

	cout << "请输入预约时间段： " << endl;
	cout << "1、上午" << endl;
	cout << "2、下午" << endl;
	while (true) {
		cin >> interval;
		if (interval >= 1 && interval <= 2) {
			break;
		}
		cout << "输入有误，请重新输入" << endl;
	}

	cout << "请输入机房号" << endl;
	for (unsigned int i = 0; i < vCom.size(); ++i) {
		cout << vCom[i].m_ComId << "号机房容量为：" << vCom[i].m_MaxNum << endl;
	}
	while (true) {
		cin >> room;
		if (room >= 1 && room <= 3) {
			break;
		}
		cout << "输入有误，请重新输入" << endl;
	}
	
	
	cout << "预约成功，审核中" << endl;
	
	// 将预约信息写入
	ofstream ofs;
	ofs.open(ORDER_FILE, ios::app);
	ofs << "data:"<< data << " ";
	ofs << "interval:"<< interval << " ";
	ofs << "stuId:"<< this->m_StuID << " ";
	ofs << "stuName:"<< this->m_Name << " ";
	ofs << "roomID:" << room << " ";
	ofs << "status:"<<1 << endl;

	ofs.close();
	system("pause");
	system("cls");
}

// 查看我的预约
void Student::showMyOrder() {
	OrderFile of;
	if (of.m_Size == 0) {
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}
	else {
		for (int i = 0; i < of.m_Size; ++i) {
			// string转为int
			// string 利用 .c_str() 转成 const char *
			// 利用atoi（const char *） 转int
			if (atoi(of.m_OrderData[i]["stuId"].c_str()) == this->m_StuID) {
				cout << "预约日期：周" << of.m_OrderData[i]["data"] << "  ";
				cout << "时间段：" << ((of.m_OrderData[i]["interval"] == "1") ? "上午": "下午" )<< "  ";
				cout << "机房： " << of.m_OrderData[i]["roomID"]<< "  ";
				string status = "状态：";
				if (of.m_OrderData[i]["status"] == "1") {
					status += "审核中";
				}
				else if (of.m_OrderData[i]["status"] == "2") {
					status += "预约成功";
				}
				else if (of.m_OrderData[i]["status"] == "-1") {
					status += "预约失败";
				}
				else {
					status += "预约已取消";
				}
				cout << status << endl;
			}
		}
	}
	system("pause");
	system("cls");
}

// 查看所有预约
void Student::showAllOrder() {
	OrderFile of;
	if (of.m_Size == 0) {
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}
	else {
		for (int i = 0; i < of.m_Size; ++i) {
			cout << i + 1 << "、"<< " ";
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
				status += "预约失败";
			}
			else {
				status += "预约已取消";
			}
			cout << status << endl;
		}	
	}
	system("pause");
	system("cls");
}

// 取消预约
void Student::cancelOrder() {
	OrderFile of;
	if (of.m_Size == 0) {
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}
	else {
		cout << "审核中或预约成功的记录可以取消，请输入取消的记录" << endl;
		int index = 1;
		vector<int> v; // 存放最大容器中的下标编号
		for (int i = 0; i < of.m_Size; ++i) {
			// 先判断是否是自身学号
			if (this->m_StuID == atoi(of.m_OrderData[i]["stuId"].c_str()))
			{
				// 查找自身的状态  审核中或预约成功
				if (of.m_OrderData[i]["status"] == "1" || of.m_OrderData[i]["status"] == "2") {
					v.push_back(i);
					cout << index++ << "、";
					cout << "预约日期：周" << of.m_OrderData[i]["data"];
					cout << "时间段：" << ((of.m_OrderData[i]["interval"] == "1") ? "上午" : "下午") << " ";
					cout << "机房编号：" << of.m_OrderData[i]["roomID"];
					string status ="状态：";
					if (of.m_OrderData[i]["status"] == "1")
						status += "审核中";
					else if (of.m_OrderData[i]["status"] == "2")
						status += "预约成功";
					cout << status << endl;
				}
			}
		}
		cout << "请输入要取消的记录，按0返回上一步" << endl;
		int select = 0;
		while (true) {
			cin >> select;
			if (select >= 0 && select <= v.size()) {
				if (select == 0) {
					system("pause");
					system("cls");
					break;
				}
				else {
					of.m_OrderData[v[select - 1]]["status"] = "0";
					of.updateOrder();
					cout << "取消成功" << endl;
					system("pause");
					system("cls");
					break;
				}
			}
			else {
				cout << "输入有误，请重新输入" << endl;
			}
			
		}
		
	}
}