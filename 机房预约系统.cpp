#include <iostream>
#include "Identity.h"
#include <fstream>
#include <string>
#include "globalFile.h"
#include "student.h"
#include "teacher.h"
#include "manager.h"
using namespace std;

// �������Ա�Ӳ˵�����
void managerMenu(Identity*& manager) {
	while (true) {
		// ���ù���Ա�Ӳ˵�  managerΪ����ָ��
		manager->operMenu();

		// ������ָ�룬תΪ����ָ�룬���ڵ�������ӿ�
		Manager* man = (Manager*)manager;

		int select = 0;
		cin >> select;
			
		if (select == 1) {	// ����˺�
			man->addPerson();
		}
		else if (select == 2) {	// �鿴�˺�
			man->showPerson();
		}
		else if (select == 3) {	// �鿴������Ϣ
			man->showComputer();
		}
		else if(select == 4) {	//���ԤԼ
			man->clearFile();
		}
		else {
			delete manager;
			cout << "ע����¼�ɹ�" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}

// ѧ���Ӳ˵�����
void studentMenu(Identity*& student) {
	while (true) {
		// ����ѧ���Ӳ˵�
		student->operMenu();
		// ������ָ��ǿ��ת������ָ�롣
		Student* stu = (Student*)student;
		int select = 0;
		cin >> select;
		if (select == 1) {
			//����ԤԼ
			stu->applyOrder();
		}
		else if (select == 2) {
			// �鿴����ԤԼ
			stu->showMyOrder();
		}
		else if (select == 3) {
			// �鿴������ԤԼ
			stu->showAllOrder();
		}
		else if (select == 4) {
			// ȡ��ԤԼ
			stu->cancelOrder();
		}
		else {
			// ע����¼
			delete student;
			cout << "ע���ɹ���" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}

void TeacherMenu(Identity*& teacher) {
	while (true) {
		//��ʦ�Ӳ˵�
		teacher->operMenu();
		// ������ָ��ǿ��ת������ָ�롣
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
			cout << "ע���ɹ�" << endl;
			system("pause");
			system("cls");
			return;
		}
		
	}
}


void LoginIn(string filename, int type) {
	// ����ָ�룬����ָ���������
	Identity* person = NULL;
	 
	// ���ļ�
	ifstream ifs;
	ifs.open(filename, ios::in);

	// �ж��ļ��Ƿ����
	if (!ifs.is_open()) {
		cout << "�ļ������ڡ�" << endl;
		ifs.close();
		return;
	}

	// ׼�������û�ID�������Ϣ
	int id = 0;
	string name;
	string pwd;

	// �ж����
	if (type == 1) {
		cout << "������ѧ�ţ�" << endl;
		cin >> id;
	}
	else if(type == 2) {
		cout << "������ְ���ţ�" << endl;
		cin >> id;
	}

	cout << "�������û�����" << endl;
	cin >> name;

	cout << "���������룺" << endl;
	cin >> pwd;

	// ѧ�������֤
	if (type == 1) {
		int fid;	//���ļ��л�ȡ��ID
		string fname;	// ���ļ��л�ȡ����
		string fpwd;	// ���ļ��л�ȡ����
		// ���ļ��е����ݰ��ж�ȡ
		while (ifs >> fid && ifs >> fname && ifs >> fpwd) {
			// �����ļ���ȡ
			/*cout << fid << endl;
			cout << fname << endl;
			cout << fpwd << endl;
			cout << endl;*/
			if (fid == id && fname == name && fpwd == pwd) {
				cout << "ѧ����¼��֤�ɹ�" << endl;
				system("pause");
				system("cls");
				person = new Student(id, name, pwd);
				// ����ѧ����ݵ��Ӳ˵�
				studentMenu(person);
				return;
			}
		}
	}
	// ��ʦ�����֤
	else if(type == 2){
		int fid;	//���ļ��л�ȡ��ID
		string fname;	// ���ļ��л�ȡ����
		string fpwd;	// ���ļ��л�ȡ����
		// ���ļ��е����ݰ��ж�ȡ
		while (ifs >> fid && ifs >> fname && ifs >> fpwd) {
			// �����ļ���ȡ
			/*cout << fid << endl;
			cout << fname << endl;
			cout << fpwd << endl;
			cout << endl;*/
			if (fid == id && fname == name && fpwd == pwd) {
				cout << "��ʦ��¼��֤�ɹ�" << endl;
				system("pause");
				system("cls");
				person = new Teacher(id, name, pwd);
				// �����ʦ��ݵ��Ӳ˵�
				TeacherMenu(person);
				return;
			}
		}
	}
	// ����Ա�����֤
	else if(type == 3) {
		string fname;	// ���ļ��л�ȡ����
		string fpwd;	// ���ļ��л�ȡ����
		// ���ļ��е����ݰ��ж�ȡ
		while (ifs >> fname && ifs >> fpwd) {
			// �����ļ���ȡ
			/*cout << fname << endl;
			cout << fpwd << endl;
			cout << endl;*/
			if (fname == name && fpwd == pwd) {
				cout << "����Ա��¼��֤�ɹ�" << endl;
				system("pause");
				system("cls");
				person = new Manager(name, pwd);
				// �����ʦ��ݵ��Ӳ˵�
				managerMenu(person);
				return;
			}
		}
	}
	else {
		cout << "��֤��¼ʧ��" << endl;
		system("pause");
		system("cls");
		// return:		�����൱��break; �����ж�ѭ��������;�жϷ���ֵΪvoid���͵ĺ�����ִ��
		// return 0:	��return����һ���÷���ר���ڷ���ֵ��void�ĺ���������ֵ
		return;
	}
}


int main() {

	// ��ɫѡ���־
	int select = 0;
	while (true) {
		cout << endl;
		cout << "========================= ��ӭ��������ԤԼϵͳ ===========================" << endl;
		cout << endl << "�밴��ݵ�¼" << endl;
		cout << "\t\t -------------------------------------\n";
		cout << "\t\t|                                    |\n";
		cout << "\t\t|             1��ѧ������            |\n";
		cout << "\t\t|                                    |\n";
		cout << "\t\t|             2����    ʦ            |\n";
		cout << "\t\t|                                    |\n";
		cout << "\t\t|             3���� �� Ա            |\n";
		cout << "\t\t|                                    |\n";
		cout << "\t\t|             0����    ��            |\n";
		cout << "\t\t|                                    |\n";
		cout << "\t\t -------------------------------------\n";
		cout << "������ѡ�� ";

		cin >> select;
		switch (select)
		{
			// ѧ������Ա
		case 1:
			LoginIn(STUDENT_FILE, 1);
			break;

			// ��ʦ
		case 2:
			LoginIn(TEACHER_FILE, 2);
			break;

			// ����Ա
		case 3:
			LoginIn(ADMIN_FILE, 3);
			break;

			// �˳�
		case 0:
			cout << endl;
			cout << "��ӭ��һ��ʹ�û���ԤԼϵͳ" << endl;
			cout << endl;
			system("pause");
			return 0;
			break;

		default:
			cout << "��������������ѡ��" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
	return 0;
}