#include <iostream>
#include"student.h"
#include <string>
#include<vector>
#include"computerRoom.h"
#include<fstream>
#include"globalFile.h"
using namespace std;
#include "orderFile.h"

// Ĭ�Ϲ���
Student::Student() {

}

// �вι���
Student::Student(int id, string name, string pwd) {
	this->m_StuID = id;
	this->m_Name = name;
	this->m_Pwd = pwd;
	ifstream ifs;
	ifs.open(COMPUTER_FILE, ios::in);
	ComputerRoom com;
	// ���ļ�
	while (ifs >> com.m_ComId && ifs >> com.m_MaxNum) {
		vCom.push_back(com);
	}
	ifs.close();
}

// �˵�����
void Student::operMenu() {
	cout << "��ӭ����Ա��" << this->m_Name << "��¼��" << endl;
	cout << "\t\t|-------------------------------------|\n";
	cout << "\t\t|                                     |\n";
	cout << "\t\t|             1������ԤԼ             |\n";
	cout << "\t\t|                                     |\n";
	cout << "\t\t|             2���鿴����ԤԼ         |\n";
	cout << "\t\t|                                     |\n";
	cout << "\t\t|             3���鿴������ԤԼ       |\n";
	cout << "\t\t|                                     |\n";
	cout << "\t\t|             4��ȡ��ԤԼ             |\n";
	cout << "\t\t|                                     |\n";
	cout << "\t\t|             0��ע����¼             |\n";
	cout << "\t\t|                                     |\n";
	cout << "\t\t|-------------------------------------|\n";

	cout << "����������ѡ��" << endl;
}

// ����ԤԼ
void Student::applyOrder() {
	cout << "��������ʱ��Ϊ����һ������" << endl;
	cout << "������ԤԼʱ�䣺" << endl;
	cout << "1����һ" << endl;
	cout << "1���ܶ�" << endl;
	cout << "1������" << endl;
	cout << "1������" << endl;
	cout << "1������" << endl;
	//����ԤԼʱ��
	int data = 0;
	// ����ԤԼʱ�������or����
	int interval = 0;
	// ԤԼ������
	int room = 0;
	while (true) {
		cin >> data;
		if (data >= 1 && data <= 5) {
			break;
		}
		cout << "������������������" << endl;
	}

	cout << "������ԤԼʱ��Σ� " << endl;
	cout << "1������" << endl;
	cout << "2������" << endl;
	while (true) {
		cin >> interval;
		if (interval >= 1 && interval <= 2) {
			break;
		}
		cout << "������������������" << endl;
	}

	cout << "�����������" << endl;
	for (unsigned int i = 0; i < vCom.size(); ++i) {
		cout << vCom[i].m_ComId << "�Ż�������Ϊ��" << vCom[i].m_MaxNum << endl;
	}
	while (true) {
		cin >> room;
		if (room >= 1 && room <= 3) {
			break;
		}
		cout << "������������������" << endl;
	}
	
	
	cout << "ԤԼ�ɹ��������" << endl;
	
	// ��ԤԼ��Ϣд��
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

// �鿴�ҵ�ԤԼ
void Student::showMyOrder() {
	OrderFile of;
	if (of.m_Size == 0) {
		cout << "��ԤԼ��¼" << endl;
		system("pause");
		system("cls");
		return;
	}
	else {
		for (int i = 0; i < of.m_Size; ++i) {
			// stringתΪint
			// string ���� .c_str() ת�� const char *
			// ����atoi��const char *�� תint
			if (atoi(of.m_OrderData[i]["stuId"].c_str()) == this->m_StuID) {
				cout << "ԤԼ���ڣ���" << of.m_OrderData[i]["data"] << "  ";
				cout << "ʱ��Σ�" << ((of.m_OrderData[i]["interval"] == "1") ? "����": "����" )<< "  ";
				cout << "������ " << of.m_OrderData[i]["roomID"]<< "  ";
				string status = "״̬��";
				if (of.m_OrderData[i]["status"] == "1") {
					status += "�����";
				}
				else if (of.m_OrderData[i]["status"] == "2") {
					status += "ԤԼ�ɹ�";
				}
				else if (of.m_OrderData[i]["status"] == "-1") {
					status += "ԤԼʧ��";
				}
				else {
					status += "ԤԼ��ȡ��";
				}
				cout << status << endl;
			}
		}
	}
	system("pause");
	system("cls");
}

// �鿴����ԤԼ
void Student::showAllOrder() {
	OrderFile of;
	if (of.m_Size == 0) {
		cout << "��ԤԼ��¼" << endl;
		system("pause");
		system("cls");
		return;
	}
	else {
		for (int i = 0; i < of.m_Size; ++i) {
			cout << i + 1 << "��"<< " ";
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
				status += "ԤԼʧ��";
			}
			else {
				status += "ԤԼ��ȡ��";
			}
			cout << status << endl;
		}	
	}
	system("pause");
	system("cls");
}

// ȡ��ԤԼ
void Student::cancelOrder() {
	OrderFile of;
	if (of.m_Size == 0) {
		cout << "��ԤԼ��¼" << endl;
		system("pause");
		system("cls");
		return;
	}
	else {
		cout << "����л�ԤԼ�ɹ��ļ�¼����ȡ����������ȡ���ļ�¼" << endl;
		int index = 1;
		vector<int> v; // �����������е��±���
		for (int i = 0; i < of.m_Size; ++i) {
			// ���ж��Ƿ�������ѧ��
			if (this->m_StuID == atoi(of.m_OrderData[i]["stuId"].c_str()))
			{
				// ���������״̬  ����л�ԤԼ�ɹ�
				if (of.m_OrderData[i]["status"] == "1" || of.m_OrderData[i]["status"] == "2") {
					v.push_back(i);
					cout << index++ << "��";
					cout << "ԤԼ���ڣ���" << of.m_OrderData[i]["data"];
					cout << "ʱ��Σ�" << ((of.m_OrderData[i]["interval"] == "1") ? "����" : "����") << " ";
					cout << "������ţ�" << of.m_OrderData[i]["roomID"];
					string status ="״̬��";
					if (of.m_OrderData[i]["status"] == "1")
						status += "�����";
					else if (of.m_OrderData[i]["status"] == "2")
						status += "ԤԼ�ɹ�";
					cout << status << endl;
				}
			}
		}
		cout << "������Ҫȡ���ļ�¼����0������һ��" << endl;
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
					cout << "ȡ���ɹ�" << endl;
					system("pause");
					system("cls");
					break;
				}
			}
			else {
				cout << "������������������" << endl;
			}
			
		}
		
	}
}