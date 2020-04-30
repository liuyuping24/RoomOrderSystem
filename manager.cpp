#include <iostream>
#include "manager.h"
#include <string>
#include <fstream>	
#include "globalFile.h"
using namespace std;
#include "student.h"
#include "teacher.h"
#include <algorithm>

 //默认构造
Manager::Manager() {
	
}

// 有参构造
Manager::Manager(string name, string pwd) {
	this->m_Name = name;
	this->m_Pwd = pwd;

	this->initVector();

	ifstream ifs;
	ifs.open(COMPUTER_FILE, ios::in);
	ComputerRoom com;
	while (ifs >> com.m_ComId && ifs >> com.m_MaxNum)
		vCom.push_back(com);
	ifs.close();
}

// 选择菜单
void Manager::operMenu() {
	cout << "欢迎管理员：" << this->m_Name << "登录！" << endl;
	cout << "\t\t|-------------------------------------|\n";
	cout << "\t\t|                                     |\n";
	cout << "\t\t|             1、添加账号             |\n";
	cout << "\t\t|                                     |\n";
	cout << "\t\t|             2、查看账号             |\n";
	cout << "\t\t|                                     |\n";
	cout << "\t\t|             3、查看机房             |\n";
	cout << "\t\t|                                     |\n";
	cout << "\t\t|             4、清空预约             |\n";
	cout << "\t\t|                                     |\n";
	cout << "\t\t|             0、注销登录             |\n";
	cout << "\t\t|                                     |\n";
	cout << "\t\t|-------------------------------------|\n";

	cout << "请输入您的选择：" << endl;
}

// 添加账号
void Manager::addPerson() {
	cout << "1 - 添加学生" << endl;
	cout << "2 - 添加教师" << endl;

	// 操作文件名
	string fileName;
	//操作的文件名
	string tip;
	// 文件流
	ofstream ofs;

	// 操作文件对象
	int select = 0;
	// 错误提示
	string errorTip;

	cin >> select;


	if (select == 1) {
		//添加学生
		fileName = STUDENT_FILE; 
		cout << "请输入学号" << endl;
		errorTip = "学号重复，请重新输入";
	}
	else {
		// 添加教师
		fileName = TEACHER_FILE;
		cout << "请输入职工编号" << endl;
		errorTip = "职工号重复，请重新输入";
	}

	// 利用追加方式写文件
	ofs.open(fileName, ios::out | ios::app);

	int id;
	string name;
	string pwd;

	// 重复学号、职工号判断
	cout << tip << endl;
	while (true) {
		cin >> id;
		bool ret = this->checkRepeat(id, select);
		if (ret)
			cout << errorTip << endl;
		else
			break;
	}
	
	cout << "请输入姓名：" << endl;
	cin >> name;

	cout << "请输入登录密码" << endl;
	cin >> pwd;

	ofs << id << " " << name << " " << pwd << endl;
	cout << "添加成功" << endl;

	system("pause");
	system("cls");

	ofs.close();

	// 调用初始化容器接口，重新获取文件中的数据
	this->initVector();
}

void printStuden(Student& s) {
	cout << "学号：	" << s.m_StuID << "    " << "姓名： " << s.m_Name << endl;
}
void printTeacher(Teacher& t) {
	cout << "学号：	" << t.m_EmpId << "    "<< "姓名： " << t.m_Name << endl;
}
// 查看
void Manager::showPerson() {
	cout << "选择查看内容：" << endl;
	cout << "1、查看所有学生" << endl;
	cout << "2、查看所有老师" << endl;
	int select;
	cin >> select;
	if (select == 1) {
		cout << "所有学生的信息如下：" << endl;
		for_each(vStu.begin(), vStu.end(), printStuden);
	}
	else{
		cout << "所有教师的信息如下：" << endl;
		for_each(vTea.begin(), vTea.end(), printTeacher);
	}
	system("pause");
	system("cls");
}

// 查看机房信息
void Manager::showComputer() {
	cout << "机房信息如下：" << endl;
	for (vector<ComputerRoom>::iterator it = vCom.begin(); it != vCom.end(); ++it) {
		cout << "机房编号：" << it->m_ComId << " 机房最大容量： " << it->m_MaxNum << endl;
	}
	system("pause");
	system("cls");

}

// 清空预约记录
void Manager::clearFile() {
	ofstream ofs(ORDER_FILE, ios::trunc);
	ofs.close();

	cout << "清空成功！" << endl;
	system("pause");
	system("cls");
}

// 初始化文件
void Manager::initVector() {
	ifstream ifs;

	ifs.open(STUDENT_FILE, ios::in);
	if (!ifs.is_open()) {
		cout << "学生文件读取失败" << endl;
		//return;
	}
	else {
		// 清空容器时空的
		vStu.clear();

		// 读取学生信息
		Student s;
		while (ifs >> s.m_StuID && ifs >> s.m_Name && ifs >> s.m_Pwd) {
			vStu.push_back(s);
		}
		// 阶段性测试代码
		cout << "当前学生数量为：" << vStu.size() << endl;
		ifs.close();
	}

	ifs.open(TEACHER_FILE, ios::in);
	Teacher t;
	if (!ifs.is_open()) {
		cout << "教师文件读取失败" << endl;

	}
	else {
		vTea.clear();
		while (ifs >> t.m_EmpId && ifs >> t.m_Name && ifs >> t.m_Pwd) {
			vTea.push_back(t);
		}
		// 阶段性测试代码
		cout << "当前教师数量为：" << vTea.size() << endl;
		ifs.close();
	}
}


// 学号、职工号重复检测
bool Manager::checkRepeat(int id, int type) {
	// 检测学生学号重复
	if (type == 1) {
		for (vector<Student>::iterator it = vStu.begin(); it != vStu.end(); ++it) {
			if (id == it->m_StuID)
				return true;
		}
		return false;
	}
	else {
		for (vector<Teacher>::iterator it = vTea.begin(); it != vTea.end(); ++it) {
			if (id == it->m_EmpId)
				return true;
		}
		return false;
	}
}
