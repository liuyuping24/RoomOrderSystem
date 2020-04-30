#include <iostream>
#include "manager.h"
#include <string>
#include <fstream>	
#include "globalFile.h"
using namespace std;
#include "student.h"
#include "teacher.h"
#include <algorithm>

 //Ĭ�Ϲ���
Manager::Manager() {
	
}

// �вι���
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

// ѡ��˵�
void Manager::operMenu() {
	cout << "��ӭ����Ա��" << this->m_Name << "��¼��" << endl;
	cout << "\t\t|-------------------------------------|\n";
	cout << "\t\t|                                     |\n";
	cout << "\t\t|             1������˺�             |\n";
	cout << "\t\t|                                     |\n";
	cout << "\t\t|             2���鿴�˺�             |\n";
	cout << "\t\t|                                     |\n";
	cout << "\t\t|             3���鿴����             |\n";
	cout << "\t\t|                                     |\n";
	cout << "\t\t|             4�����ԤԼ             |\n";
	cout << "\t\t|                                     |\n";
	cout << "\t\t|             0��ע����¼             |\n";
	cout << "\t\t|                                     |\n";
	cout << "\t\t|-------------------------------------|\n";

	cout << "����������ѡ��" << endl;
}

// ����˺�
void Manager::addPerson() {
	cout << "1 - ���ѧ��" << endl;
	cout << "2 - ��ӽ�ʦ" << endl;

	// �����ļ���
	string fileName;
	//�������ļ���
	string tip;
	// �ļ���
	ofstream ofs;

	// �����ļ�����
	int select = 0;
	// ������ʾ
	string errorTip;

	cin >> select;


	if (select == 1) {
		//���ѧ��
		fileName = STUDENT_FILE; 
		cout << "������ѧ��" << endl;
		errorTip = "ѧ���ظ�������������";
	}
	else {
		// ��ӽ�ʦ
		fileName = TEACHER_FILE;
		cout << "������ְ�����" << endl;
		errorTip = "ְ�����ظ�������������";
	}

	// ����׷�ӷ�ʽд�ļ�
	ofs.open(fileName, ios::out | ios::app);

	int id;
	string name;
	string pwd;

	// �ظ�ѧ�š�ְ�����ж�
	cout << tip << endl;
	while (true) {
		cin >> id;
		bool ret = this->checkRepeat(id, select);
		if (ret)
			cout << errorTip << endl;
		else
			break;
	}
	
	cout << "������������" << endl;
	cin >> name;

	cout << "�������¼����" << endl;
	cin >> pwd;

	ofs << id << " " << name << " " << pwd << endl;
	cout << "��ӳɹ�" << endl;

	system("pause");
	system("cls");

	ofs.close();

	// ���ó�ʼ�������ӿڣ����»�ȡ�ļ��е�����
	this->initVector();
}

void printStuden(Student& s) {
	cout << "ѧ�ţ�	" << s.m_StuID << "    " << "������ " << s.m_Name << endl;
}
void printTeacher(Teacher& t) {
	cout << "ѧ�ţ�	" << t.m_EmpId << "    "<< "������ " << t.m_Name << endl;
}
// �鿴
void Manager::showPerson() {
	cout << "ѡ��鿴���ݣ�" << endl;
	cout << "1���鿴����ѧ��" << endl;
	cout << "2���鿴������ʦ" << endl;
	int select;
	cin >> select;
	if (select == 1) {
		cout << "����ѧ������Ϣ���£�" << endl;
		for_each(vStu.begin(), vStu.end(), printStuden);
	}
	else{
		cout << "���н�ʦ����Ϣ���£�" << endl;
		for_each(vTea.begin(), vTea.end(), printTeacher);
	}
	system("pause");
	system("cls");
}

// �鿴������Ϣ
void Manager::showComputer() {
	cout << "������Ϣ���£�" << endl;
	for (vector<ComputerRoom>::iterator it = vCom.begin(); it != vCom.end(); ++it) {
		cout << "������ţ�" << it->m_ComId << " ������������� " << it->m_MaxNum << endl;
	}
	system("pause");
	system("cls");

}

// ���ԤԼ��¼
void Manager::clearFile() {
	ofstream ofs(ORDER_FILE, ios::trunc);
	ofs.close();

	cout << "��ճɹ���" << endl;
	system("pause");
	system("cls");
}

// ��ʼ���ļ�
void Manager::initVector() {
	ifstream ifs;

	ifs.open(STUDENT_FILE, ios::in);
	if (!ifs.is_open()) {
		cout << "ѧ���ļ���ȡʧ��" << endl;
		//return;
	}
	else {
		// �������ʱ�յ�
		vStu.clear();

		// ��ȡѧ����Ϣ
		Student s;
		while (ifs >> s.m_StuID && ifs >> s.m_Name && ifs >> s.m_Pwd) {
			vStu.push_back(s);
		}
		// �׶��Բ��Դ���
		cout << "��ǰѧ������Ϊ��" << vStu.size() << endl;
		ifs.close();
	}

	ifs.open(TEACHER_FILE, ios::in);
	Teacher t;
	if (!ifs.is_open()) {
		cout << "��ʦ�ļ���ȡʧ��" << endl;

	}
	else {
		vTea.clear();
		while (ifs >> t.m_EmpId && ifs >> t.m_Name && ifs >> t.m_Pwd) {
			vTea.push_back(t);
		}
		// �׶��Բ��Դ���
		cout << "��ǰ��ʦ����Ϊ��" << vTea.size() << endl;
		ifs.close();
	}
}


// ѧ�š�ְ�����ظ����
bool Manager::checkRepeat(int id, int type) {
	// ���ѧ��ѧ���ظ�
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
