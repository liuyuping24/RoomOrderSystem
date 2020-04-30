#include <iostream>
#include "teacher.h"
using namespace std;
#include <string>
#include"globalFile.h"
#include<string>	
#include "orderFile.h"
#include <fstream>
#include <vector>

// Ĭ�Ϲ���
Teacher::Teacher() {

}

// �вι���
Teacher::Teacher(int empId, string name, string pwd) {
	this->m_EmpId = empId;
	this->m_Name = name;
	this->m_Pwd = pwd;
}

// �˵�����
void Teacher::operMenu() {
	cout << "��ӭ��ʦ��" << this->m_Name << "��¼��" << endl;
	cout << "\t\t|-------------------------------------|\n";
	cout << "\t\t|                                     |\n";
	cout << "\t\t|             1���鿴����ԤԼ��¼     |\n";
	cout << "\t\t|                                     |\n";
	cout << "\t\t|             2�����ԤԼ             |\n";
	cout << "\t\t|                                     |\n";
	cout << "\t\t|             0��ע����¼             |\n";
	cout << "\t\t|                                     |\n";
	cout << "\t\t|-------------------------------------|\n";

	cout << "����������ѡ��" << endl;
}

// �鿴����ԤԼ
void Teacher::showAllOrder() {
	OrderFile of;
	if (of.m_Size == 0) {
		cout << "��ԤԼ��¼" << endl;
		system("pause");
		system("cls");
		return;
	}
	else {
		for (int i = 0; i < of.m_Size; ++i) {
			cout << i + 1 << "��" << " ";
			cout << "ԤԼ���ڣ���" << of.m_OrderData[i]["data"] << "  ";
			cout << "ʱ��Σ�" << ((of.m_OrderData[i]["interval"] == "1") ? "����" : "����") << "  ";
			cout << "ѧ�ţ�" << of.m_OrderData[i]["stuId"] << "  ";
			cout << "ѧ����" << of.m_OrderData[i]["stuName"] << "  ";
			cout << "������ " << of.m_OrderData[i]["roomID"] << "  ";
			string status = "״̬��";
			if (of.m_OrderData[i]["status"] == "1") {
				status += "�����";
			}
			else if (of.m_OrderData[i]["status"] == "2") {
				status += "ԤԼ�ɹ�";
			}
			else if (of.m_OrderData[i]["status"] == "-1") {
				status += "ԤԼʧ�ܣ����δͨ��";
			}
			else {
				status += "ԤԼ��ȡ��";
			}
			cout << status << endl;
		}
		system("pause");
		system("cls");
	}
}

// ���ԤԼ
void Teacher::validOrder() {
	OrderFile of;
	if (of.m_Size == 0) {
		cout << "��ԤԼ��¼" << endl;
		system("pause");
		system("cls");
		return;
	}
	else {
		cout << "�����ԤԼ��¼���£�" << endl;
		int index = 1;
		vector<int> v; // �����������е��±���
		for (int i = 0; i < of.m_Size; ++i) {
			if (of.m_OrderData[i]["status"] == "1") {
				v.push_back(i);
				cout << index++ << "��";
				cout << "ԤԼ���ڣ���" << of.m_OrderData[i]["data"] << "  ";
				cout << "ʱ��Σ�" << ((of.m_OrderData[i]["interval"] == "1") ? "����" : "����") << " ";
				cout << "ѧ�ţ�" << of.m_OrderData[i]["stuId"] << "  ";
				cout << "ѧ����" << of.m_OrderData[i]["stuName"] << "  ";
				cout << "������ţ�" << of.m_OrderData[i]["roomID"] << "  ";
				string status = "״̬��";
				if (of.m_OrderData[i]["status"] == "1")
					status += "�����";
				cout << status << endl;
			}
		}
		cout << "���������˵ļ�¼����0������һ��" << endl;
		int select = 0;
		int ret = 0;
		while (true) {
			cin >> select;
			if (select >= 0 && select <= v.size()) {
				if (select == 0) {
					break;
				}
				else {
					cout << "��������˽��" << endl;
					cout << "1��ͨ��" << endl;
					cout << "2����ͨ��" << endl;
					cin >> ret;
					if (ret == 1) {
						of.m_OrderData[v[select - 1]]["status"] = "2";
					}
					else {
						of.m_OrderData[v[select - 1]]["status"] = "-1";
					}
					of.updateOrder();
					cout << "��˳ɹ�" << endl;
					break;
				}
			}
			else {
				cout << "������������������" << endl;
			}

		}

	}
	system("pause");
	system("cls");
}