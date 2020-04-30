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
	// Ĭ�Ϲ���
	Manager();

	// �вι���
	Manager(string name, string pwd);

	// ѡ��˵�
	void operMenu();

	// ����˺�
	void addPerson();

	// �鿴�˺�
	void showPerson();

	// �鿴������Ϣ
	void showComputer();

	// ���ԤԼ��¼
	void clearFile();

	// ��ʼ������
	void initVector();

	// ѧ���ظ����
	bool checkRepeat(int id, int type);




	// ѧ������
	vector<Student> vStu;

	// ��ʦ����
	vector<Teacher> vTea;

	// ��������
	vector<ComputerRoom> vCom;
};