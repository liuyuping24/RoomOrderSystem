#include <iostream>
#include "Identity.h"
#include <fstream>
#include <string>
#include "globalFile.h"
#include "student.h"
#include "teacher.h"
#include "manager.h"
using namespace std;

// 进入管理员子菜单界面
void managerMenu(Identity*& manager) {
	while (true) {
		// 调用管理员子菜单  manager为父类指针
		manager->operMenu();

		// 将父类指针，转为子类指针，用于调用子类接口
		Manager* man = (Manager*)manager;

		int select = 0;
		cin >> select;
			
		if (select == 1) {	// 添加账号
			man->addPerson();
		}
		else if (select == 2) {	// 查看账号
			man->showPerson();
		}
		else if (select == 3) {	// 查看机房信息
			man->showComputer();
		}
		else if(select == 4) {	//清空预约
			man->clearFile();
		}
		else {
			delete manager;
			cout << "注销登录成功" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}

// 学生子菜单界面
void studentMenu(Identity*& student) {
	while (true) {
		// 调用学生子菜单
		student->operMenu();
		// 将父类指针强制转成子类指针。
		Student* stu = (Student*)student;
		int select = 0;
		cin >> select;
		if (select == 1) {
			//申请预约
			stu->applyOrder();
		}
		else if (select == 2) {
			// 查看自身预约
			stu->showMyOrder();
		}
		else if (select == 3) {
			// 查看所有人预约
			stu->showAllOrder();
		}
		else if (select == 4) {
			// 取消预约
			stu->cancelOrder();
		}
		else {
			// 注销登录
			delete student;
			cout << "注销成功！" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}

void TeacherMenu(Identity*& teacher) {
	while (true) {
		//教师子菜单
		teacher->operMenu();
		// 将父类指针强制转成子类指针。
		Teacher* tea = (Teacher*) teacher;

		int select = 0;
		cin >> select;

		if (select == 1) {
			tea->showAllOrder();
		}
		else if (select == 2) {
			tea->validOrder();
		}
		else {
			delete tea;
			cout << "注销成功" << endl;
			system("pause");
			system("cls");
			return;
		}
		
	}
}


void LoginIn(string filename, int type) {
	// 父类指针，用来指向子类对象
	Identity* person = NULL;
	 
	// 读文件
	ifstream ifs;
	ifs.open(filename, ios::in);

	// 判断文件是否存在
	if (!ifs.is_open()) {
		cout << "文件不存在。" << endl;
		ifs.close();
		return;
	}

	// 准备接收用户ID和身份信息
	int id = 0;
	string name;
	string pwd;

	// 判断身份
	if (type == 1) {
		cout << "请输入学号：" << endl;
		cin >> id;
	}
	else if(type == 2) {
		cout << "请输入职工号：" << endl;
		cin >> id;
	}

	cout << "请输入用户名：" << endl;
	cin >> name;

	cout << "请输入密码：" << endl;
	cin >> pwd;

	// 学生身份验证
	if (type == 1) {
		int fid;	//从文件中获取的ID
		string fname;	// 从文件中获取姓名
		string fpwd;	// 从文件中获取密码
		// 将文件中的数据按行读取
		while (ifs >> fid && ifs >> fname && ifs >> fpwd) {
			// 测试文件读取
			/*cout << fid << endl;
			cout << fname << endl;
			cout << fpwd << endl;
			cout << endl;*/
			if (fid == id && fname == name && fpwd == pwd) {
				cout << "学生登录验证成功" << endl;
				system("pause");
				system("cls");
				person = new Student(id, name, pwd);
				// 进入学生身份的子菜单
				studentMenu(person);
				return;
			}
		}
	}
	// 教师身份验证
	else if(type == 2){
		int fid;	//从文件中获取的ID
		string fname;	// 从文件中获取姓名
		string fpwd;	// 从文件中获取密码
		// 将文件中的数据按行读取
		while (ifs >> fid && ifs >> fname && ifs >> fpwd) {
			// 测试文件读取
			/*cout << fid << endl;
			cout << fname << endl;
			cout << fpwd << endl;
			cout << endl;*/
			if (fid == id && fname == name && fpwd == pwd) {
				cout << "教师登录验证成功" << endl;
				system("pause");
				system("cls");
				person = new Teacher(id, name, pwd);
				// 进入教师身份的子菜单
				TeacherMenu(person);
				return;
			}
		}
	}
	// 管理员身份验证
	else if(type == 3) {
		string fname;	// 从文件中获取姓名
		string fpwd;	// 从文件中获取密码
		// 将文件中的数据按行读取
		while (ifs >> fname && ifs >> fpwd) {
			// 测试文件读取
			/*cout << fname << endl;
			cout << fpwd << endl;
			cout << endl;*/
			if (fname == name && fpwd == pwd) {
				cout << "管理员登录验证成功" << endl;
				system("pause");
				system("cls");
				person = new Manager(name, pwd);
				// 进入教师身份的子菜单
				managerMenu(person);
				return;
			}
		}
	}
	else {
		cout << "验证登录失败" << endl;
		system("pause");
		system("cls");
		// return:		作用相当于break; 用于中断循环的作用;中断返回值为void类型的函数的执行
		// return 0:	是return的另一种用法，专用于返回值非void的函数返回其值
		return;
	}
}


int main() {

	// 角色选择标志
	int select = 0;
	while (true) {
		cout << endl;
		cout << "========================= 欢迎来到机房预约系统 ===========================" << endl;
		cout << endl << "请按身份登录" << endl;
		cout << "\t\t -------------------------------------\n";
		cout << "\t\t|                                    |\n";
		cout << "\t\t|             1、学生代表            |\n";
		cout << "\t\t|                                    |\n";
		cout << "\t\t|             2、老    师            |\n";
		cout << "\t\t|                                    |\n";
		cout << "\t\t|             3、管 理 员            |\n";
		cout << "\t\t|                                    |\n";
		cout << "\t\t|             0、退    出            |\n";
		cout << "\t\t|                                    |\n";
		cout << "\t\t -------------------------------------\n";
		cout << "请输入选择： ";

		cin >> select;
		switch (select)
		{
			// 学生管理员
		case 1:
			LoginIn(STUDENT_FILE, 1);
			break;

			// 教师
		case 2:
			LoginIn(TEACHER_FILE, 2);
			break;

			// 管理员
		case 3:
			LoginIn(ADMIN_FILE, 3);
			break;

			// 退出
		case 0:
			cout << endl;
			cout << "欢迎下一次使用机房预约系统" << endl;
			cout << endl;
			system("pause");
			return 0;
			break;

		default:
			cout << "输入有误，请重新选择！" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
	return 0;
}