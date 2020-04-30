#pragma once
#include "Identity.h"
#include <iostream>
using namespace std;
#include <string>
#include"computerRoom.h"
#include<vector>

class Student : public Identity {
public:
	// Ĭ�Ϲ���
	Student();

	// �вι���
	Student(int id, string name, string pwd);
	
	// �˵�����
	virtual void operMenu();
	
	// ����ԤԼ
	void applyOrder();
	
	// �鿴�ҵ�ԤԼ
	void showMyOrder();
	
	// �鿴����ԤԼ
	void showAllOrder();

	// ȡ��ԤԼ
	void cancelOrder();

	
	//ѧ��ѧ��
	int m_StuID;

	// ��������
	vector<ComputerRoom> vCom;
}; 